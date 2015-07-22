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

    stick = Sprite::create("image/stick1.png");
    stick->setAnchorPoint(Vec2(0.5, 0));
    stick->setPosition(-stick->getContentSize().width, -stick->getContentSize().height);
    this->addChild(stick, 5);
    return true;
}

void BackgroundLayer::start(Ref* pSender)
{
    this->removeChild(menu);
    this->removeChild(game_name);
    MoveTo* stage_move = MoveTo::create(0.2, Vec2(100, spriteSizeAt(0).height/2));
    stage_sprite[0]->runAction(stage_move);
    MoveTo* hero_move = MoveTo::create(0.2, hero_point());
    my_player.getSprite()->runAction(hero_move);
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
    now_stage = (stage_number + 2) % 3;
    last_stage = (now_stage + 2) % 3;
//    int next_stage = (now_stage + 1) % 3;
    MoveTo* now_stage_move = MoveTo::create(0.2, Vec2(100, spriteSizeAt(now_stage).height/2));
    stage_sprite[now_stage]->runAction(now_stage_move);
    MoveTo* last_stage_move = MoveTo::create(0.2, Vec2(-realSpriteWidthAt(last_stage), spriteSizeAt(last_stage).height/2));
    stage_sprite[last_stage]->runAction(last_stage_move);
    addStage();
}

bool BackgroundLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (started) {
        addStick();
    }
    return true;
}

void BackgroundLayer::onTouchMoved(Touch* pTouch, Event* pEvent)
{
}

void BackgroundLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    stopStick();
}

float BackgroundLayer::randomFloat(float x)
{
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/x));
}

void BackgroundLayer::addStick()
{
    stick->setPosition(stick_point());
    this->schedule(schedule_selector(BackgroundLayer::stickLength));
}

void BackgroundLayer::stickLength(float length)
{
    stick->setScaleY(stick->getScaleY()+1);
}

void BackgroundLayer::stopStick()
{
    touch_length = stick->getContentSize().height * stick->getScaleY();
    this->unschedule(schedule_selector(BackgroundLayer::stickLength));
    rotate_stick_and_go();
}

Vec2 BackgroundLayer::stick_point()
{
    return Vec2(100 + realSpriteWidthAt(last_stage)/2, spriteSizeAt(last_stage).height);
}

Vec2 BackgroundLayer::hero_point()
{
    return Vec2(100 + realSpriteWidthAt(last_stage)/2-10-my_player.getSprite()->getContentSize().width/2, spriteSizeAt(last_stage).height);
}

void BackgroundLayer::rotate_stick_and_go()
{
    float dest_length_min = fabsf(stage_sprite[last_stage]->getPositionX() - stage_sprite[now_stage]->getPositionX()) - realSpriteWidthAt(last_stage)/2 - realSpriteWidthAt(now_stage)/2;
    float dest_length_max = dest_length_min + realSpriteWidthAt(now_stage);
    RotateTo* ro_stick = RotateTo::create(1,90);
    RotateTo* ro_down_stick = RotateTo::create(1,180);
    if (touch_length < dest_length_min || touch_length > dest_length_max) {
        stick->runAction(ro_down_stick);
    } else {
        stick->runAction(ro_stick);
    }
}