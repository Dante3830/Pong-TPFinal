#pragma once
#include "stdafx.h"
#include "Constants.h"

class Ball {
private:
    RectangleShape BallObject;
    Vector2f ballPosition;

public:
    SoundBuffer buffer;
    Sound sound;

    RectangleShape getBallObject() {
        return BallObject;
    }

    Ball(double x, double y) {
        ballPosition.x = x;
        ballPosition.y = y;
        BallObject.setSize(sf::Vector2f(10, 10));

        BallObject.setPosition(ballPosition);

        BallObject.setFillColor(sf::Color::White);

        //Tengo que poder hacer que me cargue el audio
        //if (!buffer.loadFromFile("C:\\Users\\Leo\\Desktop\\Pong\\Audios\\PongHit2.wav")) {
        //     cout << "Error. No se pudo cargar audio." << fs::current_path() << endl;
        // }

        //sound.setBuffer(buffer);
    }

    FloatRect getBallFloatRect() {
        return BallObject.getGlobalBounds();
    }
    
    void reboundSides() {
        
        if (ballPosition.y > windowHeight) {
            ballVelocityY *= -1;
        }
        else if (ballPosition.y < 0) {
            ballVelocityY *= -1;
        }

        sound.play();

    }

    void passLeft() {
        if (ballPosition.x < 0) {
            batscore++;
            ballPosition.x = windowWidth / 2;
            ballPosition.y = windowHeight / 2;

            if (rand() % 2 == 1) {
                ballVelocityY *= -1;
            } else if (rand() % 2 == 2) {
                ballVelocityX *= -1;
            }
        }
    }

    Vector2f getBallPosition;
    
    void passRight() {
        if (ballPosition.x > windowWidth) {
            ballPosition.x = windowWidth / 2;
            ballPosition.y = windowHeight / 2;

            if (rand() % 2 == 1) { 
                ballVelocityY *= -1; 
            } else if (rand() % 2 == 2) { 
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

        BallObject.setPosition(ballPosition);
    }

    double ballVelocityX = 0.5f;
    double ballVelocityY = 0.5f;
    
    void stop() {
        ballVelocityY = 0;
        ballVelocityX = 0;
    }

    void go() {
        ballVelocityY = 0.5f;
        ballVelocityX = 0.5f;
    }

};
