#include "SceneController.h"

#include <cstdlib>
#include <string>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreMeshManager.h>
#include <OgreMath.h>
#include <OgrePlane.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <OgreParticleSystem.h>

#include "Core.h"
#include "Entity.h"
#include "Scene.h"
#include "Renderer.h"
#include "BoundMovement.h"
#include "WatchThis.h"
#include "Transform.h"
#include "AudioPlayer.h"
#include "Physics.h"
#include "PaddleController.h"
#include "NetManager.h"

using Ogre::Vector3;
using Ogre::Quaternion;

static std::string sIP;

namespace wellGame
{
	Ogre::SceneManager* mSceneMgr = nullptr;

	void constructWall(Core* core, bool createRigidbody, const Vector3& size, const Vector3& rigidbodySize, const Vector3& position, const Quaternion& rotation)
	{
		Entity* ground = core->createEntity(kCube, "BumpyMetal", false, size, position, rotation);
		if (createRigidbody)
			ground->getTransform()->attachRigidbody(kCube, rigidbodySize, 0, .9);
	}

	void createWellLevel (Core* core, bool createRigidbody, bool server, bool client)
	{
		Renderer* renderer = core->getRenderer();
		Physics* physics = core->getPhysics();
		mSceneMgr = renderer->getSceneManager();

		// Set up scene lighting
		mSceneMgr->setAmbientLight(Ogre::ColourValue(.2, .2, .3));
		mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
		Ogre::Light* spotLight = mSceneMgr->createLight("SpotLight");
		spotLight->setDiffuseColour(1, 0, 0);
		spotLight->setSpecularColour(1, 0, 0);
		spotLight->setType(Ogre::Light::LT_POINT);
		spotLight->setDirection(0, 0, 0);
		spotLight->setPosition(Vector3(0, 250, 0));

		Ogre::Light* spotLight2 = mSceneMgr->createLight("SpotLight2");
		spotLight2->setDiffuseColour(0, 0, .5);
		spotLight2->setSpecularColour(0, 0, .5);
		spotLight2->setType(Ogre::Light::LT_POINT);
		spotLight2->setDirection(0, 0, 0);
		spotLight2->setPosition(Vector3(0, 300, 0));

		// Set up Sphere
		constexpr float kScale = .1;
		Entity* sphere = core->createEntity(kSphere, "Chrome", true, Vector3(kScale, kScale, kScale), Vector3(0, 200, 0));
		if (createRigidbody)
			sphere->getTransform()->attachRigidbody(kSphere, Vector3(kScale * 50, 0, 0), 1, 1, true);
		
		sphere->isBall = true;
		AudioPlayer* ap = sphere->createComponent<AudioPlayer>();

		Ogre::ParticleSystem* mParticle = mSceneMgr->createParticleSystem("Sun", "Examples/Fireworks");
		sphere->getTransform()->getSceneNode()->attachObject(mParticle);
		mParticle->setEmitting(false);

		// Set up paddle 1
		Entity* paddle = core->createEntity(kCube, "Rockwall", true, Vector3(kScale, kScale, kScale), Vector3(0, 20, 0));
		if (createRigidbody)
			paddle->getTransform()->attachRigidbody(kCube, Vector3(kScale * 50, kScale * 50, kScale * 50), 0, 1);
		paddle->isPaddle = true;

		Ogre::Camera* paddleCam = core->getRenderer()->getSceneManager()->createCamera("Main Camera");
		paddleCam->setPosition(0, 400, 0);
		paddleCam->lookAt(Vector3(0, 1, .1));
		paddleCam->setNearClipDistance(5);
		renderer->switchCamera(paddleCam);
		if (!client)
		{
			PaddleController* pt = paddle->createComponent<PaddleController>();
			pt->mCamera = paddleCam;
			pt->ap = ap;
			if (server)
				paddle->isServerPaddle = true;
		}
		
		// Set up paddle 2
		Entity* paddle2 = nullptr;
		if(server || client)
		{
			paddle2 = core->createEntity(kCube, "RockwallBlue", true, Vector3(kScale, kScale, kScale), Vector3(0, 20, 0));
			if (createRigidbody)
				paddle2->getTransform()->attachRigidbody(kCube, Vector3(kScale * 50, kScale * 50, kScale * 50), 0, 1);
			paddle2->isPaddle = true;
			if (client)
			{
				PaddleController* pt = paddle2->createComponent<PaddleController>();
				pt->mCamera = paddleCam;
				pt->ap = ap;
				paddle2->isClientPaddle = true;
			}
		}

		// Set up ground
		Entity* ground = core->createEntity(kCube, "SpaceSkyPlane", false, Vector3(1, .01, 1), Vector3::ZERO, Quaternion(Ogre::Degree(180), Vector3(1, 0, 0)));
		if (createRigidbody)
			ground->getTransform()->attachRigidbody(kCube, Vector3(50, 1, 50), 0, 0);
		ground->isGround = true;

		// Set up the ceiling
		Entity* ceiling = core->createEntity(kCube, "SpaceSkyPlaneTransparent", false, Vector3(1, .01, 1), Vector3(0, 300, 0), Quaternion(Ogre::Degree(180), Vector3(1, 0, 0)));
		ceiling->isCeiling = true;
		if (createRigidbody)
			ceiling->getTransform()->attachRigidbody(kCube, Vector3(50, 1, 50), 0, 1);

		// Set up walls
		constructWall(core, createRigidbody, Vector3(1, 0, 3), Vector3(50, 1, 150), Vector3(0, 150, 50), Quaternion(Ogre::Degree(-90), Vector3(1, 0, 0)));
		constructWall(core, createRigidbody, Vector3(1, 0, 3), Vector3(50, 1, 150), Vector3(0, 150, -50), Quaternion(Ogre::Degree(90), Vector3(1, 0, 0)));

		constructWall(core, createRigidbody, Vector3(3, 0, 1), Vector3(150, 1, 50), Vector3(-50, 150, 0), Quaternion(Ogre::Degree(-90), Vector3(0, 0, 1)));
		constructWall(core, createRigidbody, Vector3(3, 0, 1), Vector3(150, 1, 50), Vector3(50, 150, 0), Quaternion(Ogre::Degree(90), Vector3(0, 0, 1)));

		if (server)
		{
			NetManager* netMgr = core->getNetManager();
			netMgr->startGameServer({paddle2->getTransform()}, {sphere->getTransform(), paddle->getTransform()});
		}
		else if (client)
		{
			NetManager* netMgr = core->getNetManager();
			netMgr->startGameClient("128.83.130.38", {sphere->getTransform(), paddle->getTransform()}, {paddle2->getTransform()});
		}
	}

	void loadSingleplayer (Core* core)
	{
		createWellLevel(core, true, false, false);
	}

	void loadGameServer (Core* core)
	{
		createWellLevel(core, true, true, false);
	}

	void loadGameClient (Core* core)
	{
		createWellLevel(core, false, false, true);
	}
}

void SceneController::initSingleplayer ()
{
	Scene scene(wellGame::loadSingleplayer);
	addScene(scene);

	loadInitialScene();
}

void SceneController::initServer ()
{
	Scene scene(wellGame::loadGameServer);
	addScene(scene);
	getCore()->singlePlayer = false;
	getCore()->server = true;

	loadInitialScene();
}

void SceneController::initClient ()
{
	Scene scene(wellGame::loadGameClient);
	addScene(scene);
	sIP = getIP();
	getCore()->singlePlayer = false;
	getCore()->server = false;

	loadInitialScene();
}

void SceneController::initScenes ()
{
	// Scene scene1(wellGame::loadSingleplayer);
	// Scene scene1(wellGame::loadGameServer);
	// Scene scene1(wellGame::loadGameClient);
	// addScene(scene1);
}