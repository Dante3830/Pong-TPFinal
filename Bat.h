#pragma once
#include "stdafx.h"
#include "Constants.h"

class Bat {
private:
    Vector2f batPosition;
    double batSpeed = 0.85f;
    RectangleShape batObject;

public:

    Bat(double x, double y) {
        batPosition.x = x;
        batPosition.y = y;
        batObject.setSize(sf::Vector2f(10, 150));
        batObject.setPosition(batPosition);
        batObject.setFillColor(sf::Color::Blue);
    }

    Vector2f getBatPosition() {
        return batPosition;
    }

    RectangleShape getBatObject() {
        return batObject;
    }

    FloatRect getBatFloatRect() {
        return batObject.getGlobalBounds();
    }

    void moveBatUp() {
        if (batLimitsUp() == false) {
            batPosition.y -= batSpeed;
        }
    }

    void moveBatDown() {
        if (batLimitsDown() == false) {
            batPosition.y += batSpeed;
        }
    }

    void update() {
        batObject.setPosition(batPosition);
    }

    bool batLimitsUp() {
        return (batPosition.y <= 0);
    }

    bool batLimitsDown() {
        return (batPosition.y >= windowHeight - 150);
    }

};
