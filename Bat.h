#pragma once
#include "stdafx.h"
#include "Constants.h"

class Bat {
private:
    Vector2f batPosition;
    double batSpeed = 0.85f;
    RectangleShape BatObject;

public:
    Bat(double x, double y);
    Vector2f getBatPosition();
    RectangleShape getBatObject();
    FloatRect getBatFloatRect();
    void moveBatUp();
    void moveBatDown();
    void update();

};

// Funciones de BAT

Bat::Bat(double x, double y) {
    batPosition.x = x;
    batPosition.y = y;
    BatObject.setSize(sf::Vector2f(10, 150));
    BatObject.setPosition(batPosition);
    BatObject.setFillColor(sf::Color::Blue);
}

Vector2f Bat::getBatPosition() {
    return batPosition;
}

RectangleShape Bat::getBatObject() {
    return BatObject;
}

FloatRect Bat::getBatFloatRect() {
    return BatObject.getGlobalBounds();
}

void Bat::moveBatUp() {
    batPosition.y -= batSpeed;
}

void Bat::moveBatDown() {
    batPosition.y += batSpeed;
}

void Bat::update() {
    BatObject.setPosition(batPosition);
}
