#include "AppDelegate.h"
#include "MainScene.h"

#include "audio/AudioEngine.h"

USING_NS_AX;


// Use 16:9
// Reference Link: https://zh.wikipedia.org/zh-cn/%E6%98%BE%E7%A4%BA%E5%88%86%E8%BE%A8%E7%8E%87%E5%88%97%E8%A1%A8
// TODO Wait Increase colum pixel
static ax::Size designResolutionSize = ax::Size(960, 540);
static ax::Size smallResolutionSize = ax::Size(640, 360);
static ax::Size mediumResolutionSize = ax::Size(1024, 768);
static ax::Size largeResolutionSize = ax::Size(1920, 1080);

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glView = director->getGLView();
    if (!glView) {
#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) || \
    (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
        glView = GLViewImpl::createWithRect(
                "LabelMediaPlayer", ax::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glView = GLViewImpl::create("LabelMediaPlayer");
#endif
        director->setGLView(glView);
    }

    // FPS Display Option
    director->setStatsDisplay(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height,
                                    ResolutionPolicy::SHOW_ALL);
    auto frameSize = glView->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height) {
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height,
                                            largeResolutionSize.width / designResolutionSize.width));
    } else if (frameSize.height > smallResolutionSize.height) {
        // if the frame's height is larger than the height of small size.
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height,
                                            mediumResolutionSize.width / designResolutionSize.width));
    } else {
        // if the frame's height is smaller than the height of medium size.
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height,
                                            smallResolutionSize.width / designResolutionSize.width));
    }

    // create a scene. it's an autorelease object
    // First Scene Launched Here
    auto scene = utils::createInstance<MainScene>();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    AudioEngine::resumeAll();
}
