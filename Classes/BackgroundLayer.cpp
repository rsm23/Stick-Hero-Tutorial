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

    Sprite* game_name = Sprite::create("uires_1.png");
    game_name->setPosition(visible_size.width/2, visible_size.height/5 * 4);
    this->addChild(game_name, 2);
    return true;
}