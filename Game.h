#pragma once

#include "stdafx.h"
#include "Bat.h"
#include "Ball.h"
#include "AIBat.h"
#include "Constants.h"

class Game {
	public:

    Game(){}

	void pong() {
        RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");

        //Creando los objetos
        Bat bat(20, windowHeight / 2);
        Ball ball(windowWidth / 2 + 50, windowHeight / 2);
        AIBat aibat(windowWidth - 40, windowHeight / 2);

        //Tengo que poder hacer que me cargue la musica mp3
        // Music music;
        // music.openFromFile("Audios/lady-of-the-80s-.mp3");
        // music.setVolume(100);

        while (window.isOpen()) {

            //music.play();

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
            void updateLives() {
                char pts[10];
                _itoa_s(lives, pts, 10);
                _lives.setString(pts);
            }

            ss << batscore << endl;

            Text BatScore;
            Font font;
            font.loadFromFile("VCR_OSD_MONO.ttf");

            BatScore.setFont(font);
            BatScore.setCharacterSize(60);
            BatScore.setFillColor(sf::Color::White);

            BatScore.setString(batscore);


            // Mensaje de victoria
            Text finishMessage1;

            finishMessage1.setCharacterSize(50);
            finishMessage1.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
            finishMessage1.setFont(font);
            finishMessage1.setString("You win\n\nPress any key to play again.");

            // Mensaje de derrota
            Text finishMessage2;

            finishMessage2.setCharacterSize(50);
            finishMessage2.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
            finishMessage2.setFont(font);
            finishMessage2.setString("You lose\n\nPress any key to play again.");

            // Mensaje del inicio
            Text startMessage;

            startMessage.setCharacterSize(50);
            startMessage.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
            startMessage.setFont(font);
            startMessage.setString("Welcome to Pong.\n\nPress any key to begin");

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

            // Textos e iniciacion //
            
            if (batscore == 10){
                //En caso de victoria
                window.draw(finishMessage1);
                ball.stop();

                if (event.type == event.KeyPressed) {
                    aiBatscore = 0;
                    batscore = 0;
                    ball.go();
                }

            } else if (aiBatscore == 10) {
                //En caso de derrota
                window.draw(finishMessage2);
                ball.stop();

                if (event.type == event.KeyPressed) {
                    aiBatscore = 0;
                    batscore = 0;
                    ball.go();
                }

            }
            else if (batscore == -1) {
                window.draw(startMessage);
                ball.stop();

                if (event.type == event.KeyPressed) {
                    aiBatscore = 0;
                    batscore = 0;
                    ball.go();
                }

            }
            else {
                window.draw(bat.getBatObject());
                window.draw(ball.getBallObject());

                window.draw(BatScore);
                window.draw((aibat.getAIBatObject()));
            }

            //music.stop();

            window.display();
        }
    }
};
