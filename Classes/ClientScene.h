#ifndef __Client_Scene_H__
#define __Client_Scene_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "cooloi_socket_client.h"
#include "cooloi_udp_client.h"
#include "cooloi_json.h"
#include <thread>

class ClientScene: public cocos2d::Layer, public cocos2d::TextFieldDelegate {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	void RecvMsg();
	void Time();
	void SendMenu(cocos2d::Ref* pSender);
	void ReturnScene(cocos2d::Ref* pSender);

	cocos2d::TextFieldTTF* TestEdit;
	cocos2d::TextFieldTTF* recvEdit;
	cocos2d::TextFieldTTF* timeEdit;
	cocos2d::TextFieldTTF* breakEdit;

	cooloi::sockets::Client* client_;

	CREATE_FUNC(ClientScene);
};

#endif // __HELLOWORLD_SCENE_H__
