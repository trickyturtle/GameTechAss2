
#include "GUI.h"
 
 using namespace Ogre;
//-------------------------------------------------------------------------------------
GUI::GUI(Ogre::RenderWindow* mWindow)
{
    //menuState = "MAIN";

        //this.mRoot = mRoot;
    CEGUI::OgreRenderer& GUIRenderer = CEGUI::OgreRenderer::bootstrapSystem(*mWindow);


    // Load in resources
    loadResources();



    // CEGUI::FontManager &fmg = CEGUI::FontManager::getSingleton();
    // CEGUI::Font &font = fmg.createFreeTypeFont("arial", 20, true, "arial.ttf");
    //CEGUI::Font &font = fmg.createFreeTypeFont("futhark adapted", 20, true, "FutharkAdapted.ttf");
    
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    sheet = wmgr.createWindow("DefaultWindow", "GameUI");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);


    quitButton = wmgr.createWindow("AlfiskoSkin/Button", "QuitButton");
    quitButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.0f, 0), CEGUI::UDim(0.0f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.1f, 0), CEGUI::UDim(0.05f, 0))));
    quitButton->setText("ESC = quit");

    
    singlePlayerButton = wmgr.createWindow("AlfiskoSkin/Button", "SinglePlayerButton");
    singlePlayerButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.35f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.4f, 0))));
    singlePlayerButton->setText("Single Player");

    hostGameButton = wmgr.createWindow("AlfiskoSkin/Button", "HostGameButton");
    hostGameButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.4f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.45f, 0))));
    hostGameButton->setText("Host Game");

    joinGameButton = wmgr.createWindow("AlfiskoSkin/Button", "JoinGameButton");
    joinGameButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.5f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.55f, 0))));
    joinGameButton->setText("Join Game");

    score = wmgr.createWindow("AlfiskoSkin/Label", "Score");
    score->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.0f, 0), CEGUI::UDim(0.92f, 0)),
    CEGUI::UVector2(CEGUI::UDim(0.2f, 0), CEGUI::UDim(1, 0))));
    score->setText("Score: 0");

    // winBoard = wmgr.createWindow("AlfiskoSkin/Editbox", "WinBoard");
    // winBoard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.42f, 0), CEGUI::UDim(0.33f, 0)),
    //     CEGUI::UVector2(CEGUI::UDim(0.58f, 0), CEGUI::UDim(0.4f, 0))));
    // winBoard->setText("     You Win!");
    // //winBoard->setDisabled(true);
    // winBoard->setMouseCursor("AlfiskoSkin/MouseArrow");
    //winBoard->hide();

    // loseBoard = wmgr.createWindow("AlfiskoSkin/Editbox", "LoseBoard");
    // loseBoard->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.42f, 0), CEGUI::UDim(0.33f, 0)),
    //     CEGUI::UVector2(CEGUI::UDim(0.58f, 0), CEGUI::UDim(0.4f, 0))));
    // loseBoard->setText("    You Lose!");
    // loseBoard->setDisabled(true);
    // loseBoard->setMouseCursor("AlfiskoSkin/MouseArrow");
    // loseBoard->hide();


    replayButton = wmgr.createWindow("AlfiskoSkin/Button", "ReplayButton");
    replayButton->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.4f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.45f, 0))));
    replayButton->setText("Replay");


    ipAddressText = wmgr.createWindow("AlfiskoSkin/Label", "Ip Address Text");
    ipAddressText->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.525f, 0), CEGUI::UDim(0.45f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.725f, 0), CEGUI::UDim(0.5f, 0))));
    ipAddressText->setText("IP Address");

    ipBox = wmgr.createWindow("AlfiskoSkin/Editbox", "Ip Box");
    ipBox->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.3f, 0), CEGUI::UDim(0.45f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.5f, 0))));

    currentIPLabel = wmgr.createWindow("AlfiskoSkin/Label", "Current IP");
    currentIPLabel->setArea(CEGUI::URect(CEGUI::UVector2(CEGUI::UDim(0.7f, 0), CEGUI::UDim(0.92f, 0)),
        CEGUI::UVector2(CEGUI::UDim(0.92f, 0), CEGUI::UDim(1, 0))));
    //currentIPLabel->setText(netManager->getIPstring());
    currentIPLabel->setText("ip: ");



    sheet->addChild(ipBox);
    sheet->addChild(ipAddressText);
    sheet->addChild(currentIPLabel);


    sheet->addChild(score);
    sheet->addChild(replayButton);
    // sheet->addChild(howToButton);
    // sheet->addChild(howToText);

    replayButton->hide();

    sheet->addChild(singlePlayerButton);
    sheet->addChild(hostGameButton);
    sheet->addChild(joinGameButton);

    sheet->addChild(quitButton);

    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);
    fullyLoaded = false;

}
//-------------------------------------------------------------------------------------
GUI::~GUI(void)
{
}
//-------------------------------------------------------------------------------------

void GUI::createGameUI(void)
{
    //BaseApplication::createFrameListener();
}

void GUI::update()
{   
    if(!fullyLoaded){
        printf("***************LOAD STUFF*****************************\n");
        getCore()->getModule<InputManager>()->addKeyListener( this, "GUIKeyListener" );
        getCore()->getModule<InputManager>()->addMouseListener( this, "GUIMouseListener" );
        fullyLoaded = true;
    }
}

void GUI::setMenuState(bool isMain)
{
    // menuState = state;
    // switch(state)
    // {
    //     case "MAIN":
    //         setupMainMenu();
    //         break;
    //     case "GAMEUI":
    //         setupGameUI();
    //         break;
    // }
    if(isMain){
        setupMainMenu();
    }
    else{
        setupGameUI();
    }
}

void GUI::scorePoint()
{
    mScore += 1;
    score->setText("Score: " + std::to_string(mScore));
}

void GUI::lose()
{
    score->setText("DANG! Your score was " + std::to_string(mScore));
}

void GUI::loadResources()
{
        // Load in resources
    ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/imagesets", "FileSystem", "Imagesets");
    ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/fonts", "FileSystem", "Fonts");
    ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/schemes", "FileSystem", "Schemes");
    ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/looknfeel", "FileSystem", "LookNFeel");
    ResourceGroupManager::getSingleton().addResourceLocation("/lusr/opt/cegui-0.8.4/share/cegui-0/layouts", "FileSystem", "Layouts");

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("HUDDemo.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
}

//-------------------------------------------------------------------------------------
// bool GUI::frameRenderingQueued(const Ogre::FrameEvent& evt)
// {
//     return BaseApplication::frameRenderingQueued(evt);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::keyPressed( const OIS::KeyEvent &arg )
// {
//     return BaseApplication::keyPressed(arg);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::keyReleased( const OIS::KeyEvent &arg )
// {
//     return BaseApplication::keyReleased(arg);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::mouseMoved( const OIS::MouseEvent &arg )
// {
//     return BaseApplication::mouseMoved(arg);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
// {
//     return BaseApplication::mousePressed(arg, id);
// }
// //-------------------------------------------------------------------------------------
// bool GUI::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
// {
//     return BaseApplication::mouseReleased(arg, id);
// }
//-------------------------------------------------------------------------------------
bool GUI::quit(const CEGUI::EventArgs &e)
{
    return true;
}

void GUI::setupMainMenu()
{
    printf("IN SETUP MAIN MENU");
    score->hide();
    singlePlayerButton->show();
    hostGameButton->show();
    joinGameButton->show();
    ipBox->show();
    ipAddressText->show();
    currentIPLabel->show();
    //howToButton->show();

    mSceneController = getCore()->getSceneController();


    singlePlayerButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SceneController::StartSinglePlayer, mSceneController));
    hostGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SceneController::HostServer, mSceneController));
    joinGameButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SceneController::JoinServer, mSceneController));

}

void GUI::setupGameUI()
{
    singlePlayerButton->hide();
    hostGameButton->hide();
    joinGameButton->hide();
    ipBox->hide();
    ipAddressText->hide();
    currentIPLabel->hide();
    score->show();


    //replayButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Application::Replay, this));
}

bool GUI::keyPressed(const OIS::KeyEvent& ke)
{
    switch (ke.key)
    {
        case OIS::KC_ESCAPE:
            getCore()->getRenderer()->mRunning = false;
            break;
        default:
            break;

    }
    return true;
}

bool GUI::keyReleased( const OIS::KeyEvent &e ) {
    return true;

    // if(cameraMan) cameraMan->injectKeyUp(e);
    // return true;
}



 
bool GUI::mouseMoved( const OIS::MouseEvent &e ) {
    // itMouseListener    = mMouseListeners.begin();
    // itMouseListenerEnd = mMouseListeners.end();
    // for(; itMouseListener != itMouseListenerEnd; ++itMouseListener ) {
    //     if(!itMouseListener->second->mouseMoved( e ))
    //         break;
    // }
 
    // return true;

    //if(cameraMan) cameraMan->injectMouseMove(e);

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
 
bool GUI::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {

    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
 
    return true;

    // CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id));
    // if(cameraMan) cameraMan->injectMouseDown(e, id);
    // return true;
}
 
bool GUI::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {

    CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    return true;

    // CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id));
    // if(cameraMan) cameraMan->injectMouseUp(e, id);
    // return true;
}

CEGUI::MouseButton GUI::convertButton(OIS::MouseButtonID buttonID) {
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