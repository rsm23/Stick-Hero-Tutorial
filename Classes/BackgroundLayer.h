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
#include "Player.h"

USING_NS_CC;

class BackgroundLayer : public Layer
{
public:
//    BackgroundLayer();
//    ~BackgroundLayer();
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    void bgiMove(float);
    void start(Ref*);
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void addStick();
    void stickLength(float);
    void stopStick();
    void rotate_stick_and_go();
private:
    Sprite* image_one;
    Sprite* image_two;
    MenuItemSprite* start_btn;
    Menu* menu;
    Sprite* game_name;
    Sprite* stage_sprite[3];
    int stage_number = 1;
    void addStage();
    void stageMove();
    EventListenerTouchOneByOne* touch_listener;
    bool started = false;
    Player my_player;
    Sprite* stick;
    float touch_length;
    int now_stage = 1;
    int last_stage = 0;
    // Helper
    Size spriteSizeAt(int);
    float realSpriteWidthAt(int);
    float randomFloat(float x);
    Vec2 stick_point();
    Vec2 hero_point();
};

#endif /* defined(__StickHero__BackgroundLayer__) */
