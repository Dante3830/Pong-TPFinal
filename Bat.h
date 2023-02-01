#pragma once
#include "stdafx.h"
#include "Constants.h"

class Bat {
private:
    Vector2f batPosition;
    double batSpeed = 0.85f;
    RectangleShape BatObject;

public:
    
    Bat(double x, double y) {
        batPosition.x = x;
        batPosition.y = y;
        BatObject.setSize(sf::Vector2f(10, 150));
        BatObject.setPosition(batPosition);
        BatObject.setFillColor(sf::Color::Blue);
    }

    Vector2f getBatPosition() {
        return batPosition;
    }

    RectangleShape getBatObject() {
        return BatObject;
    }

    FloatRect getBatFloatRect() {
        return BatObject.getGlobalBounds();
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
        BatObject.setPosition(batPosition);
    }

    bool batLimitsUp() {
        if (batPosition.y <= 0) {
            return true;
        } else {
            return false;
        }
    }

    bool batLimitsDown() {
        if (batPosition.y >= windowHeight - 150) {
            return true;
        } else {
            return false;
        }
    }

};
