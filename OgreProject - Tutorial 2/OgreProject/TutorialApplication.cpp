/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------
 
This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
 
#include "TutorialApplication.h"
 
//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication()
  : mRotate(.13),
    mMove(250),
    mNode(0),
    mDirection(Ogre::Vector3::ZERO)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
void TutorialApplication::createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,10,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
 
	// camera man? Look into using this. This is obviously with base application.
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
//-------------------------------------------------------------------------------------
void TutorialApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));    
}
//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	
	//------------------------------------------------------------------
	// Lighting
    Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.25, .25, 0));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25, .25, 0));
 
    directionalLight->setDirection(Ogre::Vector3( 0, -1, 1 )); 
 
    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(1, 1, 1.0);
    spotLight->setSpecularColour(1, 1, 1.0);
 
    spotLight->setDirection(-1, -1, 0);
    spotLight->setPosition(Ogre::Vector3(300, 300, 0));
 
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
	//------------------------------------------------------------------
	//------------------------------------------------------------------
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0,5, 0.5));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
    Ogre::Entity* entNinja = mSceneMgr->createEntity("Zach", "rdmobj00.mesh");
    entNinja->setCastShadows(true);

	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
	node->attachObject(entNinja);

    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
 
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);
 
    /*
	Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(0, 150, 250));
 
    pointLight->setDiffuseColour(1.0, 0.0, 0.0);
    pointLight->setSpecularColour(1.0, 0.0, 0.0);
	*/


	//Active Node
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("mNode1", Ogre::Vector3(1200, -370, 0));
	node->yaw(Ogre::Degree(90));
	mNode = node;

	node->attachObject(mCamera);
}
 bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  bool ret = BaseApplication::frameRenderingQueued(fe);
 
  mNode->translate(mDirection * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
 
  return ret;
}
 
bool TutorialApplication::keyPressed(const OIS::KeyEvent& ke)
{
  switch (ke.key)
  {
  case OIS::KC_ESCAPE:
    mShutDown = true;
    break;
 
  case OIS::KC_1:
    mCamera->getParentSceneNode()->detachObject(mCamera);
    mNode = mSceneMgr->getSceneNode("mNode1");
    mNode->attachObject(mCamera);
    break;
 
  case OIS::KC_2:
    mCamera->getParentSceneNode()->detachObject(mCamera);
    mNode = mSceneMgr->getSceneNode("NinjaNode");
    mNode->attachObject(mCamera);
    break;
 
  case OIS::KC_UP:
  case OIS::KC_W:
    mDirection.z = -mMove;
    break;
 
  case OIS::KC_DOWN:
  case OIS::KC_S:
    mDirection.z = mMove;
    break;
 
  case OIS::KC_LEFT:
  case OIS::KC_A:
    mDirection.x = -mMove;
    break;
 
  case OIS::KC_RIGHT:
  case OIS::KC_D:
    mDirection.x = mMove;
    break;
 
  case OIS::KC_PGDOWN:
  case OIS::KC_E:
    mDirection.y = -mMove;
    break;
 
  case OIS::KC_PGUP:
  case OIS::KC_Q:
    mDirection.y = mMove;
    break;
 
  default:
    break;
  }
 
  return true;
}
 
bool TutorialApplication::keyReleased(const OIS::KeyEvent& ke)
{
  switch (ke.key)
  {
  case OIS::KC_UP:
  case OIS::KC_W:
    mDirection.z = 0;
    break;
 
  case OIS::KC_DOWN:
  case OIS::KC_S:
    mDirection.z = 0;
    break;
 
  case OIS::KC_LEFT:
  case OIS::KC_A:
    mDirection.x = 0;
    break;
 
  case OIS::KC_RIGHT:
  case OIS::KC_D:
    mDirection.x = 0;
    break;
 
  case OIS::KC_PGDOWN:
  case OIS::KC_E:
    mDirection.y = 0;
    break;
 
  case OIS::KC_PGUP:
  case OIS::KC_Q:
    mDirection.y = 0;
    break;
 
  default:
    break;
  }
 
  return true;
}
 
bool TutorialApplication::mouseMoved(const OIS::MouseEvent& me)
{
  if (me.state.buttonDown(OIS::MB_Right))
  {
    mNode->yaw(Ogre::Degree(-mRotate * me.state.X.rel), Ogre::Node::TS_WORLD);
    mNode->pitch(Ogre::Degree(-mRotate * me.state.Y.rel), Ogre::Node::TS_LOCAL);
  }
 
  return true;
}
 

bool TutorialApplication::mousePressed(
  const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
  Ogre::Light* light = mSceneMgr->getLight("directionalLight");
 
  switch (id)
  {
  case OIS::MB_Left:
    light->setVisible(!light->isVisible());
    break;
  default:
    break;
  }
 
  return true;
}
 
bool TutorialApplication::mouseReleased(
  const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
  return true;
}

 
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C"
{
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
  INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
  int main(int argc, char *argv[])
#endif
  {
    TutorialApplication app;
 
    try
    {
      app.go();
    }
    catch(Ogre::Exception& e)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox(
	NULL,
	e.getFullDescription().c_str(),
	"An exception has occured!",
	MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occured: " <<
	e.getFullDescription().c_str() << std::endl;
#endif
    }
 
    return 0;
  }
#ifdef __cplusplus
}
#endif