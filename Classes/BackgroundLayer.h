//
//  BackgroundLayer.h
//  StickHero
//
//  Created by Ryan Li on 7/21/15.
//
//

#ifndef __StickHero__BackgroundLayer__
#define __StickHero__BackgroundLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
//    BackgroundLayer();
//    ~BackgroundLayer();
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    void bgiMove(float);
private:
    Sprite* image_one;
    Sprite* image_two;
};

#endif /* defined(__StickHero__BackgroundLayer__) */
