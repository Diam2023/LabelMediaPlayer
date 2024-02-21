#pragma once

#include "axmol.h"
#include "ui/axmol-ui.h"

class MainScene : public ax::Scene {
    enum class GameState {
        init = 0,
        update,
        pause,
        end,
        menu1,
        menu2,
    };

public:
    bool init() override;

    void update(float delta) override;

    // touch
    void onTouchesBegan(const std::vector<ax::Touch *> &touches, ax::Event *event);

    void onTouchesMoved(const std::vector<ax::Touch *> &touches, ax::Event *event);

    void onTouchesEnded(const std::vector<ax::Touch *> &touches, ax::Event *event);

    // mouse
    void onMouseDown(ax::Event *event);

    void onMouseUp(ax::Event *event);

    void onMouseMove(ax::Event *event);

    void onMouseScroll(ax::Event *event);

    // Keyboard
    void onKeyPressed(ax::EventKeyboard::KeyCode code, ax::Event *event);

    void onKeyReleased(ax::EventKeyboard::KeyCode code, ax::Event *event);

    // a selector callback
    void menuCloseCallback(Ref *sender);

    void selectMediaSource();

private:
    GameState _gameState = GameState::init;

    ax::ui::MediaPlayer *_mediaPlayer = nullptr;
};
