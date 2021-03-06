cmake_minimum_required(VERSION 2.8)
project(GameEngine)
set(CMAKE_DEBUG_POSTFIX "_d")

## Macros ##

# Sets variables module_name_SOURCES and HEADERS to include as source in a target.
# Will also configure_file any *.h.in and *.hpp.in to the binary directory.
macro(add_project_module module_name module_path)
	file(GLOB MODULE_${module_name}_SOURCES
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.c
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.cpp
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.mm
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.h
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.hpp
	)
	file(GLOB MODULE_${module_name}_CONFIGURE_HEADERS
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.h.in
		${PROJECT_SOURCE_DIR}/Source/${module_path}/*.hpp.in
	)

	foreach(__f ${MODULE_${module_name}_CONFIGURE_HEADERS})
		string(REPLACE ".in" "" __f_name ${__f})
		string(REPLACE "${PROJECT_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" __f_name ${__f_name})
		configure_file(${__f} ${__f_name})
		list(APPEND MODULE_${module_name}_CONFIGURED_HEADERS ${__f_name})
		message(STATUS "Configured ${__f_name}")
	endforeach()

	list(APPEND PROJECT_MODULE_SOURCES ${MODULE_${module_name}_SOURCES} ${MODULE_${module_name}_CONFIGURED_HEADERS})
	list(APPEND PROJECT_MODULE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/Source/${module_path} ${CMAKE_BINARY_DIR}/Source/${module_path})
	source_group(${module_name} FILES ${MODULE_${module_name}_SOURCES} ${MODULE_${module_name}_CONFIGURE_HEADERS} ${MODULE_${module_name}_CONFIGURED_HEADERS})
	set_source_files_properties(${MODULE_${module_name}_CONFIGURED_HEADERS} PROPERTIES GENERATED ON)

	message(STATUS "Module added: ${module_name} at ${module_path}")
endmacro()

## End Macros ##

# We assume that the user is on a linux lab machine
set(OGRE_HOME "/lusr/opt/ogre-1.9" CACHE PATH "Path to Ogre SDK")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(OGRE_CMAKE_PATH "${OGRE_HOME}/lib/OGRE/cmake" CACHE PATH "Path to Ogre's CMake scripts")
else() # other, including Windows
	set(OGRE_CMAKE_PATH "${OGRE_HOME}/CMake" CACHE PATH "Path to Ogre's CMake scripts")
endif()

message(STATUS "OGRE_HOME is ${OGRE_HOME}")
message(STATUS "OGRE_CMAKE_PATH is ${OGRE_CMAKE_PATH}")
message(STATUS "If the above two variables are wrong, edit CMakeCache.txt and set them correctly.")

set(CMAKE_MODULE_PATH "${OGRE_CMAKE_PATH}" ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/CMake)

# Using C++11 so let's ensure that's set on compilers that don't implicitly use it
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++11")
endif()

# Application Interface setup
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(INTERFACE "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(INTERFACE "Linux")
else() # Unknown
	message(WARNING "Unknown platform, not sure what INTERFACE to use!")
	set(INTERFACE "Linux")
endif()
message(STATUS "Application Interface: ${INTERFACE}")

# Module List
add_project_module(Application		Application/${INTERFACE})
add_project_module(Config			Config)
add_project_module(Core				Core)
add_project_module(Renderer			Renderer)
add_project_module(SceneController	SceneController)
add_project_module(Audio			Audio)
add_project_module(GameLogic		GameLogic)
add_project_module(GUI				GUI)
add_project_module(Physics			Physics)
add_project_module(InputManager		InputManager)
add_project_module(NetManager		NetManager)
# End module list

add_executable(${PROJECT_NAME} WIN32 ${PROJECT_MODULE_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_MODULE_INCLUDE_DIRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Binaries
	PDB_OUTPUT_DIRECTORY     ${CMAKE_BINARY_DIR}/Binaries
)

##
# ADD INCLUDE DIRECTORIES, AND LINK TO LIBRARIES
##

##OGRE
find_package(OGRE REQUIRED COMPONENTS Overlay RenderSystem_GL)
target_include_directories(${PROJECT_NAME} PRIVATE
	${OGRE_INCLUDE_DIRS}
	${OGRE_Overlay_INCLUDE_DIRS}
	${OGRE_RenderSystem_GL_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
	${OGRE_LIBRARIES}
	${OGRE_Overlay_LIBRARIES}
	${OGRE_RenderSystem_GL_LIBRARIES}
)

##OIS
find_package(OIS REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
	${OIS_LIBRARIES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${OIS_INCLUDE_DIR}
)
message(STATUS "*******************************************************************")
message(STATUS "OIS_LIBRARIES: ${OIS_LIBRARIES}")
message(STATUS "OIS_INCLUDE_DIR: ${OIS_INCLUDE_DIR}")
message(STATUS "*******************************************************************")


##CEGUI
set(CEGUI_HOME "/lusr/opt/cegui-0.8.4" CACHE PATH "Path to CEGUI")

set(CEGUI_LIBRARIES "${CEGUI_HOME}/lib/libCEGUIBase-0.so" CACHE PATH "Path to CEGUI Libraries")
set(CEGUI_INCLUDE_DIR "${CEGUI_HOME}/include/cegui-0" CACHE PATH "Path to CEGUI Include_dir")
set(CEGUI_OgreRenderer_LIBRARIES "${CEGUI_HOME}/lib/libCEGUIOgreRenderer-0.so" CACHE PATH "Path to CEGUI OgreRenderer Libraries")
# set(CEGUI_OgreRenderer_INCLUDE_DIR "${CEGUI_HOME}/include/cegui-0/CEGUI/RendererModules/Ogre" CACHE PATH "Path to CEGUI OgreRenderer Include_dir")

# find_package(CEGUI 0.8.4 EXACT REQUIRED COMPONENTS OgreRenderer)
# if(NOT CEGUI_FOUND)
#   message(SEND_ERROR "Failed to find CEGUI.")
# endif()

# message(STATUS "*******************************************************************")
# message(STATUS "CEGUI_LIBRARIES: ${CEGUI_LIBRARIES}")
# message(STATUS "CEGUI_INCLUDE_DIR: ${CEGUI_INCLUDE_DIR}")
# message(STATUS "CEGUI_OgreRenderer_LIBRARIES: ${CEGUI_OgreRenderer_LIBRARIES}")
# message(STATUS "CEGUI_OgreRenderer_INCLUDE_DIR: ${CEGUI_OgreRenderer_INCLUDE_DIR}")
# message(STATUS "*******************************************************************")

target_link_libraries(${PROJECT_NAME} PRIVATE
	${CEGUI_LIBRARIES}
	${CEGUI_OgreRenderer_LIBRARIES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${CEGUI_INCLUDE_DIR}
	${CEGUI_OgreRenderer_INCLUDE_DIR}
)

##SDL
find_package(SDL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
	${SDL_LIBRARY}
	SDL_mixer
	SDL_net
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${SDL_INCLUDE_DIR}
)

##BULLET
set(BULLET_HOME "/lusr/opt/bullet-2.79" CACHE PATH "Path to Bullet")
set(BULLET_LIBRARIES "${BULLET_HOME}/lib/libBulletDynamics.so;${BULLET_HOME}/lib/libBulletCollision.so;${BULLET_HOME}/lib/libLinearMath.so;${BULLET_HOME}/lib/libBulletSoftBody.so" CACHE PATH "Path to Bullet Libraries")
set(BULLET_INCLUDE_DIRS "${BULLET_HOME}/include/bullet" CACHE PATH "Path to Bullet Include_dir")
target_link_libraries(${PROJECT_NAME} PRIVATE
	${BULLET_LIBRARIES}
)
target_include_directories(${PROJECT_NAME} PRIVATE
	${BULLET_INCLUDE_DIRS}
)

# Copy the media directory to the binaries folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Media $<TARGET_FILE_DIR:${PROJECT_NAME}>/Media)

# On Windows, copy DLLs to bin path.
# If you link more libraries or plugins, make sure to add commands here.
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Release>:${OGRE_BINARY_REL}> $<$<NOT:$<CONFIG:Release>>:${OGRE_BINARY_DBG}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Release>:${OGRE_RenderSystem_GL_REL}> $<$<NOT:$<CONFIG:Release>>:${OGRE_RenderSystem_GL_DBG}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMENT "Copying Ogre DLLs to build directory for debugging."
	)
endif()
