#include "ClientScene.h"

USING_NS_CC;

Scene* ClientScene::createScene() {
	auto scene = Scene::create();
	auto layer = ClientScene::create();
	scene->addChild(layer);
	return scene;
}

bool ClientScene::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto u_client = cooloi::udp::Client::create();
	cooloi::Json json;
	std::string msg;
	std::string ip;
	std::string port;
	msg = u_client->UdpRecv();
	ip = json.ReadIP(msg);
	port = json.ReadPort(msg);
	int newport = atoi(port.c_str());
	client_ = new cooloi::sockets::Client(ip, newport);

	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(ClientScene::menuCloseCallback, this));
	closeItem->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, (char*) NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto sendmsg = MenuItemImage::create("send.png", "send.png",
			CC_CALLBACK_1(ClientScene::SendMenu,this));
	sendmsg->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- sendmsg->getContentSize().width / 2,
					origin.y + visibleSize.height / 2));
	auto sendmsgMenu = Menu::create(sendmsg, (char*) NULL);
	sendmsgMenu->setPosition(Vec2::ZERO);
	this->addChild(sendmsgMenu, 1);

	auto returnscene = MenuItemFont::create("Return", this,
			menu_selector(ClientScene::ReturnScene));
	returnscene->setPosition(
			Vec2(origin.x + returnscene->getContentSize().width / 2,
					origin.y + visibleSize.height
							- returnscene->getContentSize().height / 2));
	menu->addChild(returnscene);

	auto sprite = Sprite::create("client.jpg",CCRectMake(0,0,visibleSize.width,visibleSize.height));
	sprite->setPosition(
			Vec2(visibleSize.width / 2 + origin.x,
					visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	TestEdit = TextFieldTTF::textFieldWithPlaceHolder("Please put in", "Arial",
			24);
	TestEdit->setColor(Color3B::ORANGE);
	TestEdit->setPosition(
			ccp(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height * 2 / 3));
	addChild(TestEdit);

	recvEdit = TextFieldTTF::textFieldWithPlaceHolder("Receive message",
			"Arial", 24);
	recvEdit->setColor(Color3B::MAGENTA);
	recvEdit->setPosition(
			ccp(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height / 3));
	addChild(recvEdit);

	timeEdit = TextFieldTTF::textFieldWithPlaceHolder("time", "Arial", 24);
	timeEdit->setColor(Color3B::GREEN);
	timeEdit->setPosition(
			Vec2(
					origin.x + visibleSize.width
							- timeEdit->getContentSize().width,
					origin.y + visibleSize.height
							- timeEdit->getContentSize().height / 2));
	addChild(timeEdit);

	breakEdit = TextFieldTTF::textFieldWithPlaceHolder("", "Arial", 24);
	breakEdit->setColor(Color3B::BLACK);
	breakEdit->setPosition(
			ccp(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height / 2));
	addChild(breakEdit);

	std::thread time(&ClientScene::Time, this);
	time.detach();

	std::thread t(&ClientScene::RecvMsg, this);
	t.detach();

	setTouchMode(kCCTouchesOneByOne);
	setTouchEnabled(true);

	return true;
}

bool ClientScene::onTouchBegan(Touch* pTouch, Event* pEvent) {
	bool isClicked = TestEdit->boundingBox().containsPoint(
			pTouch->getLocation());

	if (isClicked) {
		TestEdit->attachWithIME();
		TestEdit->setString("");
	} else {
		TestEdit->detachWithIME();
	}
	return true;
}

void ClientScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void ClientScene::SendMenu(Ref* pSender) {
	std::string SendMsg;
	SendMsg = TestEdit->getString();
	client_->Send(SendMsg);
	TestEdit->setString("");
	TestEdit->detachWithIME();
}

void ClientScene::RecvMsg() {
	while (true) {
		sleep(1);
		std::string msg;
		msg = client_->Recv();
		if (msg == "") {
			breakEdit->setString("连接中断，手机将在5秒后爆炸");
			sleep(1);
			for (int i = 5; i >= 0; i--) {
				sleep(1);
				std::string b = std::to_string(i);
				breakEdit->setString(b);
			}
			breakEdit->setString("BOOM!!!");
			sleep(1);
			breakEdit->setString("哈哈哈，骗你的");
			sleep(1);
			Director::getInstance()->end();
		} else {
			recvEdit->setString(msg);
		}
	}

}

void ClientScene::Time() {
	for (int i = 1;; i++) {
		sleep(1);
		//std::string b = std::to_string(i);
		std::string b = client_->GetTime();
		timeEdit->setString(b);
	}
}

void ClientScene::ReturnScene(cocos2d::Ref* pSender) {
	Director::getInstance()->popScene();
}
