#pragma once
#include "stdafx.h"
#include "Constants.h"

class AiBat {
private:
    
    Vector2f aiBatPosition;
    
    // Velocidad de la IA
    double aiBatSpeed = 24;
    
    RectangleShape aiBatObject;

public:

    AiBat(double x, double y) {
        aiBatPosition.x = x;
        aiBatPosition.y = y;

        // Seteando el tamano, color y posicion de la IA
        aiBatObject.setSize(Vector2f(10, 150));
        aiBatObject.setPosition(aiBatPosition);
        aiBatObject.setFillColor(Color::Red);
    }

    Vector2f getAiBatPosition() {
        return aiBatPosition;
    }

    RectangleShape getAiBatObject() {
        return aiBatObject;
    }

    FloatRect getAiBatFloatRect() {
        return aiBatObject.getGlobalBounds();
    }

    // Mover la IA para arriba
    void moveAiBatUp() {
        if (aiBatLimitsUp() == false) {
            aiBatPosition.y -= aiBatSpeed;
        }
    }

    // Mover la IA para abajo
    void moveAiBatDown() {
        if (aiBatLimitsDown() == false) {
            aiBatPosition.y += aiBatSpeed;
        }
    }

    // Actualizar posicion de la IA
    void update() {
        aiBatObject.setPosition(aiBatPosition);
    }

    // Limite para chocar con arriba
    bool aiBatLimitsUp() {
        return (aiBatPosition.y <= 0);
    }

    // Limite para chocar con abajo
    bool aiBatLimitsDown() {
        return (aiBatPosition.y >= windowHeight - 150);
    }

    // Velocidad de la IA para arriba
    void aiBatSpeedReverse() {
        aiBatSpeed *= -1;
    }

};
