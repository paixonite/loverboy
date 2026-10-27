#ifndef FLAPPYGAME_H
#define FLAPPYGAME_H

#include "Game.h"

class FlappyGame : public Game {
public:
    FlappyGame(TFT_eSPI* tft_display, SoundManager* sound_manager, InputManager* input_manager);

protected:
    // Only mandatory base class implementations
    void resetGame() override;
    void updatePlaying() override;
    void drawPlaying() override;
    void handleInputPlaying() override;
    void onResume() override;
    void drawTutorialContent() override;

private:
    struct Pipe {
        float x;
        float x_prev; 
        int gap_y;
        bool scored;
    };

    void checkCollisions();
    void drawHUD();

    // Flappy-specific properties
    float player_y;
    float player_y_prev;
    float player_vel_y;
    Pipe pipes[3];
    bool fullRedrawRequired;
    bool gameStarted;
};

#endif // FLAPPYGAME_H