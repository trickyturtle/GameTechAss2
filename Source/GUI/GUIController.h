#pragma once

#include "Core.h"
#include "Component.h"
#include "Module.h"
#include "Entity.h"
#include "InputManager.h"
#include "AudioPlayer.h"

#include <OgreSceneManager.h>
#include <OISKeyboard.h>
#include <OISInputManager.h>




class GUIController : public Component, public OIS::KeyListener, public OIS::MouseListener
{
public:
	GUIController();
	~GUIController(){};

	//void update() override;
	void update();
	

	AudioPlayer* ap = nullptr;
	Ogre::Camera* mCamera = nullptr;
	bool keyPressed(const OIS::KeyEvent& ke);
	bool keyReleased(const OIS::KeyEvent& ke);

    bool mouseMoved( const OIS::MouseEvent &e );
    bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);


protected:
	void postLoad() override;

private:

	Ogre::Vector3 mDirection;
	Ogre::Quaternion mRotate;

	float mTilt = 1;
	float mMove = .25;

    int mouseXAxis;
    int mouseYAxis;

};
