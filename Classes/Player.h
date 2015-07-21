//
//  Player.h
//  StickHero
//
//  Created by Ryan Li on 7/21/15.
//
//

#ifndef __StickHero__Player__
#define __StickHero__Player__

#include <stdio.h>
USING_NS_CC;

class Player
{
public:
//    Player();
//    ~Player();
    void init();
    void setPosition(Vec2);
    void walk(Vec2);
    void stay();
    void stop();
    void start(Vec2);
    Sprite* getSprite();
private:
    Sprite* _player;
    Animation* walk_animation;
    Animation* stay_animation;
    Animate* walk_animate;
    Animate* stay_animate;
};

#endif /* defined(__StickHero__Player__) */
