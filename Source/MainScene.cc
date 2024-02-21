#include "MainScene.h"

#include "ui/axmol-ui.h"

#include "FileDialog.h"

#include <iostream>

USING_NS_AX;

using namespace ax::ui;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf(
            "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
            "MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    if (_mediaPlayer == nullptr) {
        _mediaPlayer = MediaPlayer::create();
        _mediaPlayer->setContentSize(visibleSize);

        float x = safeOrigin.x + safeArea.size.width - _mediaPlayer->getContentSize().width / 2;
        float y = safeOrigin.y + _mediaPlayer->getContentSize().height / 2;
        _mediaPlayer->setPosition({x, y});
    }

    if (FileDialog::getInstance().init()) {
        if (FileDialog::getInstance().show()) {
            auto res = FileDialog::getInstance().getSelectedResult();
            if (!res.empty()) {
                _mediaPlayer->setFileName(res[0]);
                std::cout << "Success Set FileName" << std::endl;
            }
            FileDialog::getInstance().clear();
        } else {
            std::cout << "FileDialog::show() Error" << std::endl;

        }
    } else {
        std::cout << "FileDialog::init() Error" << std::endl;
    }


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0) {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    this->addChild(_mediaPlayer, 1);


    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = AX_CALLBACK_2(MainScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(MainScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    //auto mouseListener           = EventListenerMouse::create();
    //mouseListener->onMouseMove   = AX_CALLBACK_1(MainScene::onMouseMove, this);
    //mouseListener->onMouseUp     = AX_CALLBACK_1(MainScene::onMouseUp, this);
    //mouseListener->onMouseDown   = AX_CALLBACK_1(MainScene::onMouseDown, this);
    //mouseListener->onMouseScroll = AX_CALLBACK_1(MainScene::onMouseScroll, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = AX_CALLBACK_2(MainScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = AX_CALLBACK_2(MainScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 11);

//    auto mediaPlayer = MediaPlayer::create();


    // Audio Stop Callback

    // add a label shows "Hello World"
    // create and initialize a label

//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    if (label == nullptr) {
//        problemLoading("'fonts/Marker Felt.ttf'");
//    } else {
//        // position the label on the center of the screen
//        label->setPosition(
//                Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
//
//        // add the label as a child to this layer
//        this->addChild(label, 1);
//    }
    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png"sv);
//    if (sprite == nullptr) {
//        problemLoading("'HelloWorld.png'");
//    } else {
//        // position the sprite on the center of the screen
//        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
//
//        // add the sprite as a child to this layer
//        this->addChild(sprite, 0);
//        auto drawNode = DrawNode::create();
//        drawNode->setPosition(Vec2(0, 0));
//        addChild(drawNode);
//
//        drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);
//    }

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesMoved(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch *> &touches, ax::Event *event) {
    for (auto &&t: touches) {
        AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onMouseDown(Event *event) {
    EventMouse *e = static_cast<EventMouse *>(event);
    AXLOG("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseUp(Event *event) {
    EventMouse *e = static_cast<EventMouse *>(event);
    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseMove(Event *event) {
    EventMouse *e = static_cast<EventMouse *>(event);
    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());
}

void MainScene::onMouseScroll(Event *event) {
    EventMouse *e = static_cast<EventMouse *>(event);
    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event *event) {
    AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event *event) {
    AXLOG("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::update(float delta) {
    switch (_gameState) {
        case GameState::init: {
            _gameState = GameState::update;
            _mediaPlayer->play();
            break;
        }

        case GameState::update: {
            /////////////////////////////
            // Add your codes below...like....
            //
            // UpdateJoyStick();
            // UpdatePlayer();
            // UpdatePhysics();
            // ...
            break;
        }

        case GameState::pause: {
            /////////////////////////////
            // Add your codes below...like....
            //
            // anyPauseStuff()

            break;
        }

        case GameState::menu1: {    /////////////////////////////
            // Add your codes below...like....
            //
            // UpdateMenu1();
            break;
        }

        case GameState::menu2: {    /////////////////////////////
            // Add your codes below...like....
            //
            // UpdateMenu2();
            break;
        }

        case GameState::end: {    /////////////////////////////
            // Add your codes below...like....
            //
            // CleanUpMyCrap();
            menuCloseCallback(this);
            break;
        }

    } //switch
}

void MainScene::menuCloseCallback(Ref *sender) {
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

    // EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
