//
//  WelcomeScene.h
//  StickHero
//
//  Created by Ryan Li on 7/21/15.
//
//

#ifndef __StickHero__WelcomeScene__
#define __StickHero__WelcomeScene__

#include <stdio.h>
#include "cocos2d.h"
#include "BackgroundLayer.h"

USING_NS_CC;

class WelcomeScene : public Scene
{
public:
//    WelcomeScene();
//    ~WelcomeScene();
    CREATE_FUNC(WelcomeScene);
    virtual bool init();
};

#endif /* defined(__StickHero__WelcomeScene__) */
