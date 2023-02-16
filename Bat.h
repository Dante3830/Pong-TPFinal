#pragma once
#include "stdafx.h"
#include "Constants.h"

class Bat {
private:

    Vector2f batPosition;
    
    // Velocidad del jugador
    double batSpeed = 0.85f;

    RectangleShape batObject;

public:

    Bat(double x, double y) {
        batPosition.x = x;
        batPosition.y = y;

        // Seteando el tamano, color y posicion del jugador
        batObject.setSize(Vector2f(10, 150));
        batObject.setPosition(batPosition);
        batObject.setFillColor(Color::Color(63, 65, 227));
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

    // Mover jugador para arriba
    void moveBatUp() {
        if (batLimitsUp() == false) {
            batPosition.y -= batSpeed;
        }
    }

    // Mover jugador para abajo
    void moveBatDown() {
        if (batLimitsDown() == false) {
            batPosition.y += batSpeed;
        }
    }

    // Actualizar posicion del jugador
    void update() {
        batObject.setPosition(batPosition);
    }

    // Limite para chocar con arriba
    bool batLimitsUp() {
        return (batPosition.y <= 0);
    }

    // Limite para chocar con abajo
    bool batLimitsDown() {
        return (batPosition.y >= windowHeight - 150);
    }

};
