//
//  Player.cpp
//  StickHero
//
//  Created by Ryan Li on 7/21/15.
//
//

#include "Player.h"

Sprite* Player::getSprite()
{
    return _player;
}

void Player::init()
{
    _player = Sprite::create("image/anim1/stay1.png");
    _player->setAnchorPoint(Vec2(0.5,0));

    Vector<SpriteFrame*> frameVector;
    for (int i = 1; i <= 5; i++)    {
        char pngName[260] = {0};
        sprintf(pngName, "image/anim1/stay%d.png", i);
        frameVector.pushBack(SpriteFrame::create(pngName, Rect(0,0,54,58)));
    }
    stay_animation = Animation::createWithSpriteFrames(frameVector, 0.1);
    stay_animation->setRestoreOriginalFrame(false);
    stay_animation->setLoops(10000);
    stay_animate = Animate::create(stay_animation);

    frameVector.clear();
    for (int i = 1; i <= 5; i++)
    {
        char pngName[260] = {0};
        sprintf(pngName, "image/anim1/walk%d.png", i);
        frameVector.pushBack(SpriteFrame::create(pngName, Rect(0,0,54,58)));
    }
    walk_animation = Animation::createWithSpriteFrames(frameVector, 0.1);
    walk_animation->setRestoreOriginalFrame(false);
    walk_animation->setLoops(10000);
    walk_animate = Animate::create(walk_animation);
}

void Player::setPosition(Vec2 _pos)
{
    _player->setPosition(_pos);
}

void Player::stay()
{
    _player->runAction(stay_animate);
}

void Player::stop()
{
    _player->stopAllActions();
}

void Player::walk(Vec2 _dec)
{
    MoveTo* move = MoveTo::create(1.5f, _dec);
    _player->runAction(move);
}

void Player::start(Vec2 _dec)
{
    MoveTo* move = MoveTo::create(0.2f, _dec);
    _player->runAction(move);
}
