#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, (char*) NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto client = MenuItemFont::create("Client", this,
			menu_selector(HelloWorld::Client));
	client->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));
	menu->addChild(client);
	auto server = MenuItemFont::create("Server", this,
			menu_selector(HelloWorld::Server));
	server->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3));
	menu->addChild(server);

	auto sprite = Sprite::create("background.jpeg");

	// position the sprite on the center of the screen
	sprite->setPosition(
			Vec2(visibleSize.width / 2 + origin.x,
					visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	return true;
}

void HelloWorld::Client(CCObject* pSender) {
	auto scene = ClientScene::createScene();
	auto transitions = TransitionSplitCols::create(0.5, scene);
	Director::getInstance()->pushScene(transitions);
}

void HelloWorld::Server(CCObject* pSender) {
	auto scene = ServerScene::createScene();
	auto transitions = TransitionSplitCols::create(0.5, scene);
	Director::getInstance()->pushScene(transitions);
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
