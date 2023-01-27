#pragma once
#include "stdafx.h"
#include "Constants.h"

class AIBat {
private:
    Vector2f aiBatPosition;
    double aiBatSpeed = 24;
    RectangleShape aiBatObject;

public:
    AIBat(double x, double y);
    Vector2f getAIBatPosition();
    RectangleShape getAIBatObject();
    FloatRect getAIBatFloatRect();
    void moveAIBatUp();
    void moveAIBatDown();
    void update();
    void Rebound();
    void AIBatSpeedReverse();

};

// AIBAT functions
AIBat::AIBat(double x, double y) {
    aiBatPosition.x = x;
    aiBatPosition.y = y;
    aiBatObject.setSize(sf::Vector2f(10, 150));
    aiBatObject.setPosition(aiBatPosition);
    aiBatObject.setFillColor(sf::Color::Red);
}

RectangleShape AIBat::getAIBatObject() {
    return aiBatObject;
}

Vector2f AIBat::getAIBatPosition() {
    return aiBatPosition;
}

FloatRect AIBat::getAIBatFloatRect() {
    return aiBatObject.getGlobalBounds();
}

void AIBat::moveAIBatUp() {
    aiBatPosition.y -= aiBatSpeed;
}

void AIBat::moveAIBatDown() {
    aiBatPosition.y += aiBatSpeed;
}

void AIBat::update() {
    aiBatObject.setPosition(aiBatPosition);
}

void AIBat::AIBatSpeedReverse() {
    aiBatSpeed *= -1;
}
