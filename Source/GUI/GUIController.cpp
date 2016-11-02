#include "GUIController.h"

// #include <cstdlib>
#include <OgreCamera.h>
// #include <OgreEntity.h>
// #include <OgreSceneNode.h>

using Ogre::Vector3;

GUIController::GUIController(){
  mDirection = Ogre::Vector3(0, 0, 0);
  mRotate = Ogre::Quaternion(1, 1, 1, 1);
}

void GUIController::postLoad(){

  getEntity()->getCore()->getModule<InputManager>()->addKeyListener( this, "GUIKeyListener" );
  getEntity()->getCore()->getModule<InputManager>()->addKeyListener( this, "GUIMouseListener" );

}

void GUIController::update(){
  Transform* transform = getEntity()->getComponent<Transform>();
  transform->translate(mDirection);
  mCamera->move(mDirection);
  transform->rotate(mRotate);
}

bool GUIController::keyPressed(const OIS::KeyEvent& ke)
{
  switch (ke.key)
  {
  case OIS::KC_ESCAPE:
    getEntity()->getCore()->getRenderer()->mRunning = false;
    break;
 

  case OIS::KC_A:
    mDirection.x = mMove;
    break;
 
  case OIS::KC_D:
    mDirection.x = -mMove;
    break;

  case OIS::KC_W:
    mDirection.z = mMove;
    break;

  case OIS::KC_S:
    mDirection.z = -mMove;
    break;


  case OIS::KC_UP:
    mRotate.z = -mTilt;
    break;

  case OIS::KC_DOWN:
    mRotate.z = mTilt;
    break;
 
  case OIS::KC_LEFT:
    mRotate.x = -mTilt;
    break;

  case OIS::KC_RIGHT:
    mRotate.x = mTilt;
    break;

  case OIS::KC_P:
    ap->muteBackgroundMusic();
    break;
 
  // case OIS::KC_PGDOWN:
  // case OIS::KC_E:
  //   mDirection.y = -mMove;
  //   break;
 
  // case OIS::KC_PGUP:
  // case OIS::KC_Q:
  //   mDirection.y = mMove;
  //   break;
 
  default:
    break;
  }
 
  return true;
}
 
bool GUIController::keyReleased(const OIS::KeyEvent& ke)
{
  switch (ke.key)
  {


  case OIS::KC_A:
    mDirection.x = 0;
    break;

  case OIS::KC_D:
    mDirection.x = 0;
    break;

  case OIS::KC_W:
    mDirection.z = 0;
    break;

  case OIS::KC_S:
    mDirection.z = 0;
    break;
 

  case OIS::KC_UP:
    mRotate.z = 0;
    break;

  case OIS::KC_DOWN:
    mRotate.z = 0;
    break;

  case OIS::KC_LEFT:
    mRotate.x = 0;
 
  case OIS::KC_RIGHT:
    mRotate.x = 0;
    break;


 
  // case OIS::KC_PGDOWN:
  //  //tilt
  //   break;

  // case OIS::KC_E:
  //   mDirection.y = 0;
  //   break;
 
  // case OIS::KC_PGUP:
  //  //tilt
  //   break;

  // case OIS::KC_Q:
  //   mDirection.y = 0;
  //   break;
 
  default:
    break;
  }
 
  return true;
}

// bool GUI::keyPressed(const OIS::KeyEvent& ke)
// {
//     switch (ke.key)
//     {
//         case OIS::KC_ESCAPE:
//             getCore()->getRenderer()->mRunning = false;
//             break;
//         default:
//             break;

//     }
//     return true;
// }

// bool GUI::keyReleased( const OIS::KeyEvent &e ) {
//     return true;

//     // if(mCamera) mCamera->injectKeyUp(e);
//     // return true;
// }



 
bool GUIController::mouseMoved( const OIS::MouseEvent &e ) {
    // itMouseListener    = mMouseListeners.begin();
    // itMouseListenerEnd = mMouseListeners.end();
    // for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
    //     if(!itMouseListener->second->mouseMoved( e ))
    //         break;
    // }
 
    // return true;

    //if(mCamera) mCamera->injectMouseMove(e);

    // From -width/2 to +width/2
    mouseXAxis = (e.state.X.abs) - e.state.width/2;
    mouseYAxis = (e.state.Y.abs) - e.state.height/2;

    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.getDefaultGUIContext().injectMousePosition(e.state.X.abs, e.state.Y.abs);
    // Scroll wheel.
    if (e.state.Z.rel)
        sys.getDefaultGUIContext().injectMouseWheelChange(e.state.Z.rel / 120.0f);

    return true;
}
 
bool GUIController::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {

    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    //if(mCamera) mCamera->injectMouseDown(e, id);
    return true;
}
 
bool GUIController::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {

    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    //if(mCamera) mCamera->injectMouseUp(e, id);
    return true;
}

CEGUI::MouseButton GUIController::convertButton(OIS::MouseButtonID buttonID) {
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}