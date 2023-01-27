#pragma once
#include "stdafx.h"
#include "Bat.h"
#include "Ball.h"
#include "AIBat.h"
#include "Constants.h"

////////////////INT MAIN/////////////////

int main() {

    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

    //Creando los objetos
    Bat bat(20, windowHeight / 2);
    Ball ball(windowWidth / 2 + 50, windowHeight / 2);
    AIBat aibat(windowWidth - 40, windowHeight / 2);

    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        // Controles del usuario
        if (((event.type == event.KeyPressed) && event.key.code == Keyboard::Up)) {
            bat.moveBatUp();
        }

        if (((event.type == event.KeyPressed) && event.key.code == Keyboard::Down)) {
            bat.moveBatDown();
        }

        // Logica
        ball.reboundSides();
        ball.passLeft();
        ball.passRight();

        if (ball.getBallFloatRect().intersects(bat.getBatFloatRect())) {
            ball.reboundBatorAI();
        }

        if (ball.getBallFloatRect().intersects(aibat.getAIBatFloatRect())) {
            ball.reboundBatorAI();
        }

        if (ball.getBallFloatRect().top > (aibat.getAIBatFloatRect().top) + 50) {
            if (aibatcounter % 60 == 0) {
                aibat.moveAIBatDown();
            }
        }

        if (ball.getBallFloatRect().top < (aibat.getAIBatFloatRect().top) + 50) {
            if (aibatcounter % 60 == 0) {
                aibat.moveAIBatUp();
            }
        }

        if (ball.getBallPosition.x > windowWidth) {
            aibat.AIBatSpeedReverse();
        }


        //Texto y fuente
        std::stringstream ss;

        ss << "Score: " << batscore << "       Lives: " << lives;

        Text text;
        Font font;
        font.loadFromFile("VCR_OSD_MONO_1.001.ttf");

        text.setFont(font);
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);

        text.setString(ss.str());


        // Mensaje de pausa
        std::stringstream ss2;
        ss2 << "You ran out of lives. \n\nYour score is " << batscore << ".\n\nPress any key to play again.";
        Text pauseMessage;

        pauseMessage.setCharacterSize(50);
        pauseMessage.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        pauseMessage.setFont(font);
        pauseMessage.setString(ss2.str());
        
        // Mensaje del inicio
        std::stringstream ss3;
        ss3 << "Welcome to Pong.\n\nPress any key to begin";
        Text startMessage;

        startMessage.setCharacterSize(50);
        startMessage.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        startMessage.setFont(font);
        startMessage.setString(ss3.str());
        
        // Actualizacion
        if (aibatcounter == 1000000) {
            aibatcounter = 0;
        }
        aibatcounter++;
        ball.update();
        bat.update();
        aibat.update();
        
        // Dibujar
        window.clear(Color(34, 34, 34, 100));

        if (lives == 0) {

            window.draw(pauseMessage);
            ball.stop();

            if (event.type == event.KeyPressed) {
                lives = 3;
                batscore = 0;
                ball.go();
            }

        } else if (lives == -1) {
            window.draw(startMessage);
            ball.stop();
            
            if (event.type == event.KeyPressed) {
                lives = 3;
                batscore = 0;
                ball.go();
            }

        } else {
            window.draw(bat.getBatObject());
            window.draw(ball.getBallObject());

            window.draw(text);
            window.draw((aibat.getAIBatObject()));
        }

        window.display();
    }

    return 0;
}
