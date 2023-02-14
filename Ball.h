#pragma once
#include "stdafx.h"
#include "Constants.h"

class Ball {
private:
    RectangleShape ballObject;
    Vector2f ballPosition;

    //Tengo que poder hacer que me cargue el audio
    SoundBuffer buffer;
    Sound hit;

public:
   
    RectangleShape getBallObject() {
        return ballObject;
    }

    Ball(double x, double y) {
        ballPosition.x = x;
        ballPosition.y = y;
        ballObject.setSize(sf::Vector2f(10, 10));

        ballObject.setPosition(ballPosition);

        ballObject.setFillColor(sf::Color::White);

        buffer.loadFromFile("Audios/PongHit2.wav");
        hit.setBuffer(buffer);
    }

    FloatRect getBallFloatRect() {
        return ballObject.getGlobalBounds();
    }

    void reboundSides() {
        if (ballPosition.y > windowHeight) {
            ballVelocityY *= -1;
        }
        else if (ballPosition.y < 0) {
            ballVelocityY *= -1;
        }

        hit.play();
    }

    void passLeft() {
        if (ballPosition.x < 0) {
            aiBatScore++;
            ballPosition.x = windowWidth / 2;
            ballPosition.y = windowHeight / 2;

            if (rand() % 2 == 1) {
                ballVelocityY *= -1;
            }
            else if (rand() % 2 == 2) {
                ballVelocityX *= -1;
            }
        }
    }

    Vector2f getBallPosition;

    void passRight() {
        if (ballPosition.x > windowWidth) {
            batScore++;
            
            ballPosition.x = windowWidth / 2;
            ballPosition.y = windowHeight / 2;

            if (rand() % 2 == 1) {
                ballVelocityY *= -1;
            }
            else if (rand() % 2 == 2) {
                ballVelocityX *= -1;
            }
        }
    }

    void reboundBatorAI() {
        ballPosition.x -= (ballVelocityX * 30);
        ballVelocityX *= -1;
    }

    void update() {
        ballPosition.x += ballVelocityX;
        ballPosition.y += ballVelocityY;

        ballObject.setPosition(ballPosition);
    }

    double ballVelocityX = 0.5f;
    double ballVelocityY = 0.5f;

    void stop() {
        ballVelocityY = 0;
        ballVelocityX = 0;
    }

    void resetVelocity() {
        ballVelocityY = 0.5f;
        ballVelocityX = 0.5f;
    }

};
