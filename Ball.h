#pragma once
#include "stdafx.h"
#include "Constants.h"

class Ball {
private:

    RectangleShape ballObject;
    Vector2f ballPosition;

    SoundBuffer buffer1;
    SoundBuffer buffer2;
    Sound hit;
    Sound score;

public:
   
    RectangleShape getBallObject() {
        return ballObject;
    }

    Ball(double x, double y) {
        ballPosition.x = x;
        ballPosition.y = y;

        // Seteando el tamano, color y posicion de la pelota
        ballObject.setSize(sf::Vector2f(10, 10));
        ballObject.setPosition(ballPosition);
        ballObject.setFillColor(sf::Color::White);

        // Seteando los sonidos
        buffer1.loadFromFile("Hit.wav");
        hit.setBuffer(buffer1);
        hit.setVolume(100);

        buffer2.loadFromFile("Score.wav");
        score.setBuffer(buffer2);
        score.setVolume(100);
    }

    FloatRect getBallFloatRect() {
        return ballObject.getGlobalBounds();
    }

    // Hacer que la pelota rebote las paredes
    void reboundSides() {
        if (ballPosition.y > windowHeight) {
            ballVelocityY *= -1;      

            hit.play();
        }
        else if (ballPosition.y < 0) {
            ballVelocityY *= -1;

            hit.play();
        }       
    }

    // Si la pelota pasa la izquierda, punto para la IA
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

            score.play();
        }
    }

    Vector2f getBallPosition;

    // Si la pelota pasa la derecha, punto para el jugador
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

            score.play();
        }
    }

    // Si la pelota lo golea el jugador o la IA, se ira para el otro lado
    void reboundBatOrAI() {
        ballPosition.x -= (ballVelocityX * 30);
        ballVelocityX *= -1;

        hit.play();
    }

    // Actualizar posicion de la pelota
    void update() {
        ballPosition.x += ballVelocityX;
        ballPosition.y += ballVelocityY;

        ballObject.setPosition(ballPosition);
    }

    // Velocidad de la pelota
    double ballVelocityX = 0.5f;
    double ballVelocityY = 0.5f;

    // Pelota detenida
    void stop() {
        ballVelocityY = 0;
        ballVelocityX = 0;
    }

    // Resetear pelota
    void resetVelocity() {
        ballVelocityY = 0.5f;
        ballVelocityX = 0.5f;
    }

};
