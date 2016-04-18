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
    vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
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
 
	Ogre::Entity* entZack = mSceneMgr->createEntity("Zack", "rdmobj00.mesh");
    entZack->setCastShadows(true);

	Ogre::SceneNode* node2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("ZackNode");
	node2->attachObject(entZack);

    Ogre::Entity* entNinja = mSceneMgr->createEntity("Ninja", "ninja.mesh");
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

	//----------------------------------------------------------------------
	//------------------------------------------------------------------------
	//Jamming in all the animation stuff
	// Setup animation defaults
	Ogre::Animation::setDefaultInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::Animation::setDefaultRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);
 
		// Create entity (Loads mesh and associated animations, if it is first reference to mesh)
		Ogre::Entity *ent = mSceneMgr->createEntity("jaiquaent", "jaiqua.mesh");
 
		// Create a scene node and add the entity to it
		Ogre::SceneNode *mCharSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mCharSceneNode->attachObject(ent);
		//mCharSceneNode->pitch(Ogre::Degree(90));
		//mCharSceneNode->yaw(Ogre::Degree(-128));
		//mCharSceneNode->setPosition(-152, 38, 33);
		mCharSceneNode->setScale(5,5,5);
 
		// Gets an animation state for the animation "sneak" for the created entity, and sets it up
                // (mCharAnimState must be accessible in the frame listener
		mCharAnimState = ent->getAnimationState("Sneak");
		mCharAnimState->setEnabled(true);
		mCharAnimState->setLoop(true);

 

	// Ogre Tutorial 4: Animation in Ogre http://paginas.fe.up.pt/-----------

	//In the CreateScene method
	//Create a Light
	
	 Ogre::Light * alight = mSceneMgr->createLight("AnimLight");
 
		alight->setType(Ogre::Light::LT_SPOTLIGHT);
		alight->setDiffuseColour(Ogre::ColourValue(0.25f,0.25f,0.0f));
		alight->setSpecularColour(Ogre::ColourValue(0.25f,0.25f,0.0f));
		alight->setAttenuation(8000,1,0.0005,0);
		alight->setSpotlightRange(Ogre::Degree(60), Ogre::Degree(70));
		alight->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

		//Create a geometry to represent the light (in this case a Billboard, for a simple and nice effect)
		Ogre::BillboardSet* lightbillboardset = mSceneMgr->createBillboardSet("lightbbs", 1); //whats the number do?
		lightbillboardset->setMaterialName("Examples/Flare");
		Ogre::Billboard* lightbillboard = lightbillboardset->createBillboard(0,0,0,Ogre::ColourValue(0.5,0.3,0.0f));

		//Create a SceneNode that will be holding the light and its representation
		Ogre::SceneNode* lightNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("AnimLightNode");
 
		lightNode->attachObject(alight);
		lightNode->attachObject(lightbillboardset);
 
		Ogre::Real x = 20, y = 20, z = 100;
 
		lightNode->setPosition(x,y,z);
		Ogre::Real s = 0.50f; //.05f and originally.
		lightNode->setScale(s,s,s);

		//Create an Animation associated to the scene node, with spline interpolation, and add a NodeAnimationTrack to it
		Ogre::Real duration=4.0;
		Ogre::Real step=duration/4.0;
		Ogre::Animation* animation = mSceneMgr->createAnimation("LightAnim",duration);
		animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
		Ogre:: NodeAnimationTrack* track = animation->createNodeTrack(0,lightNode);

		//Add five KeyFrame's to the track, corresponding to the cardinal points plus the repetition of the first
		Ogre::TransformKeyFrame* key;
 
		key = track->createNodeKeyFrame(0.0f);
		key->setTranslate(Ogre::Vector3(-x, -y,z));
		key->setScale(Ogre::Vector3(s,s,s));
 
		key = track->createNodeKeyFrame(step);
		key->setTranslate(Ogre::Vector3( -x, y,z));
		key->setScale(Ogre::Vector3(s,s,s));
 
		key = track->createNodeKeyFrame(2.0*step);
		key ->setTranslate(Ogre::Vector3( x, y, z));
		key->setScale(Ogre::Vector3(s,s,s));
 
		key = track->createNodeKeyFrame(3.0*step);
		key->setTranslate(Ogre::Vector3(x, -y, z));
		key->setScale(Ogre::Vector3(s,s,s));
 
		key = track->createNodeKeyFrame(4.0*step);
		key->setTranslate(Ogre::Vector3(-x, -y,z));
		key->setScale(Ogre::Vector3(s,s,s));
		
		//Still in CreateScene, create an AnimationState (it should be accessible by a frame listener that will update it)
		// Declare it so that it is accessible in a frame listener (e.g. as an object you pass to the frame listener)
		//Ogre::AnimationState * mLightAnimationState;
		// ...
		mLightAnimationState = mSceneMgr->createAnimationState("LightAnim");
		mLightAnimationState->setEnabled(true);
		mLightAnimationState->setLoop(true);
		


}

//In a frame listener
//Update the animation state in the frameStarted method
bool TutorialApplication::frameStarted(const Ogre::FrameEvent& evt)
    {
		mCharAnimState->addTime(evt.timeSinceLastFrame);
		mLightAnimationState->addTime(evt.timeSinceLastFrame);
		
      return true;
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
	case OIS::KC_3:
    mCamera->getParentSceneNode()->detachObject(mCamera);
    mNode = mSceneMgr->getSceneNode("ZackNode");
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