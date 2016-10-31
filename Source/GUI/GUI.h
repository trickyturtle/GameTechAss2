#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h> //from 0.8 it's just Ogre/Renderer.h
#include "Renderer.h"

#include "CoreConfig.h"

#include "Module.h"
#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>
#include "SceneController.h"
#include "Core.h"
 
class GUI : public Module
{
    public:
        GUI(Ogre::RenderWindow* mWindow);
        virtual ~GUI(void);


        // enum MenuState{MAIN, GAMEUI};
        // MenuState menuState;
        bool main;

        void update();
        void scorePoint();
        void lose();
        void setupMainMenu();
        void setupGameUI();
        //TODO: Change this to state based
        void setMenuState(bool isMain);



    private:
        //Ogre::Root* mRoot;

     
    protected:
        CEGUI::OgreRenderer* GUIRenderer;
        SceneController* mSceneController = nullptr;

        int mScore = 0;

        CEGUI::Window* sheet;

        CEGUI::Window* score;

        CEGUI::Window* winBoard;
        CEGUI::Window* loseBoard;
        CEGUI::Window* replayButton;
        CEGUI::Window* howToButton;
        CEGUI::Window* howToText;
        CEGUI::Window* quitButton;

        CEGUI::Window* singlePlayerButton;
        CEGUI::Window* hostGameButton;
        CEGUI::Window* joinGameButton;

        CEGUI::Window* ipBox;
        CEGUI::Window* ipAddressText;
        CEGUI::Window* currentIPLabel;

        
     
        // virtual void createFrameListener(void);
     
        // // Ogre::FrameListener
        // //virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
     
        // // OIS::KeyListener
        // virtual bool keyPressed( const OIS::KeyEvent &arg );
        // virtual bool keyReleased( const OIS::KeyEvent &arg );
        // // OIS::MouseListener
        // virtual bool mouseMoved( const OIS::MouseEvent &arg );
        // virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
        // virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
     
        bool quit(const CEGUI::EventArgs &e);
        void createGameUI();
        void loadResources();
};