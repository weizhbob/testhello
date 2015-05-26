#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ServerScene.h"
#include "ClientScene.h"
#include <iostream>
#include <string>
#include <thread>

USING_NS_CC;

class HelloWorld: public cocos2d::Layer, public cocos2d::TextFieldDelegate {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void Client(CCObject* pSender);
	void Server(CCObject* pSender);

	CREATE_FUNC(HelloWorld);

};
#endif
