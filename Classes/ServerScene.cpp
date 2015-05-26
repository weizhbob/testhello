#include "ServerScene.h"

USING_NS_CC;

Scene* ServerScene::createScene() {
	auto scene = Scene::create();
	auto layer = ServerScene::create();
	scene->addChild(layer);
	return scene;
}

bool ServerScene::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(ServerScene::menuCloseCallback, this));
	closeItem->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, (char*) NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sprite = Sprite::create("server.jpg");
	sprite->setPosition(
			Vec2(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height / 2));
	this->addChild(sprite, 0);

	text = TextFieldTTF::textFieldWithPlaceHolder("Recv...", "Arial", 24);
	text->setColor(Color3B::RED);
	text->setPosition(
			ccp(visibleSize.width / 2 + origin.x,
					visibleSize.height / 2 + origin.y));
	addChild(text);

	auto server = MenuItemFont::create("Server", this,
			menu_selector(ServerScene::run));
	server->setPosition(
			Vec2(visibleSize.width / 2,
					visibleSize.height - server->getContentSize().height * 2));
	menu->addChild(server);
	auto send = MenuItemFont::create("Send", this,
			menu_selector(ServerScene::send));
	send->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	menu->addChild(send);

	auto returnscene = MenuItemFont::create("Return", this,
			menu_selector(ServerScene::returnScene));
	returnscene->setPosition(
			Vec2(origin.x + returnscene->getContentSize().width / 2,
					origin.y + visibleSize.height
							- returnscene->getContentSize().height / 2));
	menu->addChild(returnscene);

	std::thread t(&ServerScene::recv, this);
	t.detach();

	return true;
}

void ServerScene::run(CCObject* pSender) {
	server.Run();
}

void ServerScene::send(CCObject* pSender) {
	server.Send();
}

void ServerScene::recv() {
	while (true) {
		std::string msg;
		msg = server.Recv();
		text->setString(msg);
	}
}

void ServerScene::returnScene(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}

void ServerScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
