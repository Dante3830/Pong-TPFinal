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
    Ball(double x, double y);
    FloatRect getBallFloatRect();
    void reboundSides();
    void passLeft();
    Vector2f getBallPosition;
    void passRight();
    void intersectBat();
    void intersectAIBat();
    void reboundBatorAI();
    void update();
    double ballVelocityX = 0.5f;
    double ballVelocityY = 0.5f;
    void stop();
    void go();

};

// BALL functions

Ball::Ball(double x, double y) {
    ballPosition.x = x;
    ballPosition.y = y;
    BallObject.setSize(sf::Vector2f(10, 10));

    BallObject.setPosition(ballPosition);

    BallObject.setFillColor(sf::Color::White);
}

void Ball::update() {
    ballPosition.x += ballVelocityX;
    ballPosition.y += ballVelocityY;

    BallObject.setPosition(ballPosition);
}

void Ball::reboundSides() {
    if (ballPosition.y > windowHeight) {
        ballVelocityY *= -1;
    }
    else if (ballPosition.y < 0) {
        ballVelocityY *= -1;
    }
}

void Ball::passLeft() {
    if (ballPosition.x < 0) {
        batscore++;
        ballPosition.x = windowWidth / 2;
        ballPosition.y = windowHeight / 2;

        if (rand() % 2 == 1) ballVelocityY *= -1;
        if (rand() % 2 == 2) ballVelocityX *= -1;
    }
}

void Ball::passRight() {
    if (ballPosition.x > windowWidth ) {
        ballPosition.x = windowWidth / 2;
        ballPosition.y = windowHeight / 2;
        lives--;
        if (rand() % 2 == 1) ballVelocityY *= -1;
        if (rand() % 2 == 2) ballVelocityX *= -1;
    }
}

FloatRect Ball::getBallFloatRect() {
    return BallObject.getGlobalBounds();
}

void Ball::reboundBatorAI() {
    ballPosition.x -= (ballVelocityX * 30);
    ballVelocityX *= -1;
}

void Ball::stop() {
    ballVelocityY = 0;
    ballVelocityX = 0;
}

void Ball::go() {
    ballVelocityY = 0.5f;
    ballVelocityX = 0.5f;
}
