#include "AppDelegate.h"
#include "MainScene.h"

#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE

#    include "audio/AudioEngine.h"

#endif

USING_NS_AX;

static ax::Size designResolutionSize = ax::Size(720, 1280);
static ax::Size smallResolutionSize = ax::Size(320, 480);
static ax::Size mediumResolutionSize = ax::Size(768, 1024);
static ax::Size largeResolutionSize = ax::Size(1536, 2048);

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

    // turn on display FPS
    director->setStatsDisplay(true);

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
    }
        // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height) {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height,
                                            mediumResolutionSize.width / designResolutionSize.width));
    }
        // if the frame's height is smaller than the height of medium size.
    else {
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height,
                                            smallResolutionSize.width / designResolutionSize.width));
    }

    // create a scene. it's an autorelease object
    auto scene = utils::createInstance<MainScene>();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#endif
}