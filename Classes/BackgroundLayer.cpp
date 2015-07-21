//
//  BackgroundLayer.cpp
//  StickHero
//
//  Created by Ryan Li on 7/21/15.
//
//

#include "BackgroundLayer.h"

bool BackgroundLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size visible_size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int bgi_number = random(1, 5);
    image_one = Sprite::create("bg" + std::to_string(bgi_number) + ".jpg");
    image_two = Sprite::create("bg" + std::to_string(bgi_number) + ".jpg");

    image_one->setPosition(visible_size.width/2, visible_size.height/2);
    image_two->setPosition(visible_size.width/2 + image_two->getContentSize().width, visible_size.height/2);
    this->addChild(image_one, 1);
    this->addChild(image_two, 1);

    game_name = Sprite::create("uires_1.png");
    game_name->setPosition(visible_size.width/2, visible_size.height/5 * 4);
    this->addChild(game_name, 2);

    start_btn = MenuItemSprite::create(Sprite::create("uires_2.png"), Sprite::create("uires_2.png"), NULL, this, menu_selector(BackgroundLayer::start));
    start_btn->setPosition(visible_size.width/2, visible_size.height/2 + 8);
    MoveTo* start_btn_move_down = MoveTo::create(2, Vec2(visible_size.width/2, visible_size.height/2-8));
    MoveTo* start_btn_move_up = MoveTo::create(2, Vec2(visible_size.width/2, visible_size.height/2+5));
    Sequence* start_move_seq = Sequence::create(start_btn_move_down, start_btn_move_up, NULL);
    RepeatForever* start_move_repeat = RepeatForever::create(start_move_seq);
    start_btn->runAction(start_move_repeat);
    menu = Menu::create(start_btn, NULL);
    menu->setPosition(0,0);
    this->addChild(menu, 2);

    for (int i = 0; i<3; i++) {
        stage_sprite[i] = Sprite::create("stage1.png");
    }
    stage_sprite[0]->setScaleX(30);
    for (int i = 0; i<3; i++) {
        stage_sprite[i]->setPosition(visible_size.width + realSpriteWidthAt(i), spriteSizeAt(i).height/2);
    }
    stage_sprite[0]->setPosition(visible_size.width/2, spriteSizeAt(0).height/4);
    for (int i = 0; i<3; i++) {
        this->addChild(stage_sprite[i],3);
    }

    touch_listener = EventListenerTouchOneByOne::create();
    touch_listener->setSwallowTouches(false);
    touch_listener->onTouchBegan = CC_CALLBACK_2(BackgroundLayer::onTouchBegan, this);
    touch_listener->onTouchMoved = CC_CALLBACK_2(BackgroundLayer::onTouchMoved, this);
    touch_listener->onTouchEnded = CC_CALLBACK_2(BackgroundLayer::onTouchEnded, this);
    touch_listener->onTouchCancelled = CC_CALLBACK_2(BackgroundLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);

    my_player.init();
    my_player.setPosition(Vec2(visible_size.width/2, spriteSizeAt(0).height/4*3));
    this->addChild(my_player.getSprite(), 5);
    my_player.stay();
    return true;
}

void BackgroundLayer::start(Ref* pSender)
{
    this->removeChild(menu);
    this->removeChild(game_name);
    MoveTo* stage_move = MoveTo::create(0.2, Vec2(100, spriteSizeAt(0).height/2));
    stage_sprite[0]->runAction(stage_move);
    addStage();
    started = true;
}

void BackgroundLayer::addStage()
{
    Size visible_size = Director::getInstance()->getVisibleSize();
    stage_sprite[stage_number]->setScaleX(10+random(0, 40));
    stage_sprite[stage_number]->setPosition(visible_size.width + realSpriteWidthAt(stage_number), spriteSizeAt(stage_number).height/2);
    MoveTo* stageMove = MoveTo::create(0.2, Vec2(visible_size.width/2 + randomFloat(visible_size.width/3), spriteSizeAt(stage_number).height/2));
    stage_sprite[stage_number]->runAction(stageMove);
    stage_number = (stage_number + 1) % 3;
}

Size BackgroundLayer::spriteSizeAt(int index)
{
    return stage_sprite[index]->getContentSize();
}

float BackgroundLayer::realSpriteWidthAt(int index)
{
    return stage_sprite[index]->getScaleX()*spriteSizeAt(index).width;
}

void BackgroundLayer::stageMove()
{
    int now_stage = (stage_number + 2) % 3;
    int last_stage = (now_stage + 2) % 3;
//    int next_stage = (now_stage + 1) % 3;
    MoveTo* now_stage_move = MoveTo::create(0.2, Vec2(100, spriteSizeAt(0).height/2));
    stage_sprite[now_stage]->runAction(now_stage_move);
    MoveTo* last_stage_move = MoveTo::create(0.2, Vec2(-realSpriteWidthAt(last_stage), spriteSizeAt(0).height/2));
    stage_sprite[last_stage]->runAction(last_stage_move);
    addStage();
}

bool BackgroundLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (started) {
        stageMove();
    }
    return true;
}

void BackgroundLayer::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

void BackgroundLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
}

float BackgroundLayer::randomFloat(float x)
{
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/x));
}

