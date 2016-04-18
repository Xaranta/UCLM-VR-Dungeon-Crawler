/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/
 
#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_
 
#include "BaseApplication.h"
 
class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void);
	virtual ~TutorialApplication(void);
 
protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	bool frameStarted(const Ogre::FrameEvent& evt);
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//Buffered Input
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	//------------------------------------------------------------------
	//------------------------------------------------------------------
	//Buffered input variables?
	Ogre::Real mRotate;
	Ogre::Real mMove;
	Ogre::SceneNode* mNode;
	Ogre::Vector3 mDirection;
	Ogre::AnimationState * mLightAnimationState;
	Ogre::AnimationState * mCharAnimState;
};
 
#endif // #ifndef __TutorialApplication_h_
