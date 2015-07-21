//
//  WelcomeScene.cpp
//  StickHero
//
//  Created by Ryan Li on 7/21/15.
//
//

#include "WelcomeScene.h"

bool WelcomeScene::init(){
    if (!Scene::init())
    {
        return false;
    }
    BackgroundLayer* bgi_layer = BackgroundLayer::create();
    this->addChild(bgi_layer, 1, 1);
    return true;
}