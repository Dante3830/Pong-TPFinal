#pragma once
#include "stdafx.h"
#include "Constants.h"

class AIBat {
private:
    Vector2f aiBatPosition;
    double aiBatSpeed = 24;
    RectangleShape aiBatObject;

public:
    
    AIBat(double x, double y) {
        aiBatPosition.x = x;
        aiBatPosition.y = y;
        aiBatObject.setSize(sf::Vector2f(10, 150));
        aiBatObject.setPosition(aiBatPosition);
        aiBatObject.setFillColor(sf::Color::Red);
    }

    Vector2f getAIBatPosition() {
        return aiBatPosition;
    }

    RectangleShape getAIBatObject() {
        return aiBatObject;
    }

    FloatRect getAIBatFloatRect() {
        return aiBatObject.getGlobalBounds();
    }

    void moveAIBatUp() {
        if (aiBatLimitsUp() == false) {
            aiBatPosition.y -= aiBatSpeed;
        }
    }

    void moveAIBatDown() {
        if (aiBatLimitsDown() == false) {
            aiBatPosition.y += aiBatSpeed;
        }
    }

    void update() {
        aiBatObject.setPosition(aiBatPosition);
    }

    bool aiBatLimitsUp() {
        if (aiBatPosition.y <= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    
    bool aiBatLimitsDown() {
        if (aiBatPosition.y >= windowHeight - 150) {
            return true;
        }
        else {
            return false;
        }
    }

    void AIBatSpeedReverse() {
        aiBatSpeed *= -1;
    }

}; 
