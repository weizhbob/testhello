#ifndef __SERVER_SCENE_H__
#define __SERVER_SCENE_H__

#include "cocos2d.h"
#include "cooloi_socket_server.h"
#include "HelloWorldScene.h"
#include <iostream>
#include <string>
#include <thread>

USING_NS_CC;

class ServerScene: public cocos2d::Layer, public cocos2d::TextFieldDelegate {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);
	void recv();
	void send(CCObject* pSender);
	void run(CCObject* pSender);
	void returnScene(cocos2d::Ref* pSender);

	cocos2d::TextFieldTTF* text;
	cooloi::sockets::Server server;
	CREATE_FUNC(ServerScene);
};
#endif
