#pragma once

#include "stdafx.h"
#include "Bat.h"
#include "Ball.h"
#include "AiBat.h"
#include "Constants.h"

class Game {
private:

    RenderWindow* wnd;
    Ball* bll;
    Bat* bt;
    AiBat* aiBt;

    Font font;
    SoundBuffer buffer;
    Sound music;

    Texture Space;
    Sprite space;

    Text title;
    Text startMessage;
    Text _batScore;
    Text _aiBatScore;
    Text finishMessage1;
    Text finishMessage2;

    Event event;

    bool score;
    bool loop = true;

    // Actualizar el puntaje del jugador
    void updateBatScore() {
        char bts[10];
        _itoa_s(batScore, bts, 10);
        _batScore.setString(bts);
    }

    // Actualizar el puntaje de la IA
    void updateAiBatScore() {
        char aibts[10];
        _itoa_s(aiBatScore, aibts, 10);
        _aiBatScore.setString(aibts);
    }

public:

    Game() {
        wnd = new RenderWindow(VideoMode(windowWidth, windowHeight), "Pong");
        
        // Seteando posicion de la pelota, el jugador y la IA
        bll = new Ball(windowWidth / 2 + 50, windowHeight / 2);
        bt = new Bat(20, windowHeight / 2);
        aiBt = new AiBat(windowWidth - 40, windowHeight / 2);

        // Si score esta en false, no mostara el puntaje todavia
        score = false;

        // Cargando la fuente, el fondo y la musica 
        font.loadFromFile("VCR_OSD_MONO.ttf");

        Space.loadFromFile("space.png");
        space.setTexture(Space);

        buffer.loadFromFile("MainMusic.wav");
        music.setBuffer(buffer);
        music.setVolume(10);

        // Mensaje del inicio
        title.setCharacterSize(90);
        title.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        title.setFont(font);
        title.setFillColor(Color::Color(21, 182, 185));
        title.setString("     PONG");

        startMessage.setCharacterSize(30);
        startMessage.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        startMessage.setFont(font);
        startMessage.setString("\n\n\n\n\n\n\n\n      Presiona las flechas para iniciar");

        // Mensaje de victoria
        finishMessage1.setCharacterSize(30);
        finishMessage1.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        finishMessage1.setFont(font);
        finishMessage1.setFillColor(Color::White);
        finishMessage1.setString("                 ¡Ganaste!\n\n   Presiona las felchas para reiniciar");

        // Mensaje de derrota
        finishMessage2.setCharacterSize(30);
        finishMessage2.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 100);
        finishMessage2.setFont(font);
        finishMessage2.setFillColor(Color::White);
        finishMessage2.setString("                 Perdiste...\n\n   Presiona las flechas para reiniciar");

        //Mostrar puntaje del jugador
        _batScore.setCharacterSize(120);
        _batScore.setPosition(200.0f, 100.0f);
        _batScore.setFont(font);
        _batScore.setFillColor(Color::Color(63, 65, 227));

        //Mostrar puntaje de la IA
        _aiBatScore.setCharacterSize(120);
        _aiBatScore.setPosition(750.0f, 100.0f);
        _aiBatScore.setFont(font);
        _aiBatScore.setFillColor(Color::Red);

        updateBatScore();
        updateAiBatScore();
    }

    // Controles del usuario
    void controls() {
        if (((event.type == event.KeyPressed) && event.key.code == Keyboard::Up)) {
            bt->moveBatUp();
        } else if (((event.type == event.KeyPressed) && event.key.code == Keyboard::Down)) {
            bt->moveBatDown();
        }
    }

    // Logica del juego
    void logic() {
        bll->reboundSides();
        bll->passLeft();
        bll->passRight();

        if (bll->getBallFloatRect().intersects(bt->getBatFloatRect())) {
            bll->reboundBatOrAI();
        }

        if (bll->getBallFloatRect().intersects(aiBt->getAiBatFloatRect())) {
            bll->reboundBatOrAI();
        }

        if (bll->getBallFloatRect().top > (aiBt->getAiBatFloatRect().top) + 50) {
            if (aiBatCounter % 60 == 0) {
                aiBt->moveAiBatDown();
            }
        }

        if (bll->getBallFloatRect().top < (aiBt->getAiBatFloatRect().top) + 50) {
            if (aiBatCounter % 60 == 0) {
                aiBt->moveAiBatUp();
            }
        }

        if (bll->getBallPosition.x > windowWidth) {
            aiBt->aiBatSpeedReverse();
        }
    }

    // Actualizacion de la posicion de la pelota, el jugador y la IA
    void update() {
        if (aiBatCounter == 1000000) {
            aiBatCounter = 0;
        }

        aiBatCounter++;

        bll->update();
        bt->update();
        aiBt->update();
    }

    // Iniciacion del juego
    void winOrLose() {
        if (score) {
            //Mostrar puntaje de cada uno
            wnd->draw(_batScore);
            wnd->draw(_aiBatScore);
        }
        
        if (batScore == 10) {
            //En caso de victoria
            wnd->draw(finishMessage1);
            bll->stop();

            if (event.type == event.KeyPressed) {
                aiBatScore = 0;
                batScore = 0;

                bll->resetVelocity();
            }

        }
        else if (aiBatScore == 10) {
            //En caso de derrota
            wnd->draw(finishMessage2);
            bll->stop();

            if (event.type == event.KeyPressed) {
                aiBatScore = 0;
                batScore = 0;

                bll->resetVelocity();
            }

        }
        else if (batScore == -1) {
            wnd->draw(title);
            wnd->draw(startMessage);
            bll->stop();

            if (event.type == event.KeyPressed) {
                aiBatScore = 0;
                batScore = 0;
                score = true;

                bll->resetVelocity();
            }

        }
        else {
            wnd->draw(bt->getBatObject());
            wnd->draw(bll->getBallObject());
            wnd->draw((aiBt->getAiBatObject()));
        }
    }

    void pong() {
         
         music.setLoop(loop);
         music.play();
         
         while (wnd->isOpen()) {
            // Limpiar y dibujar fondo
            wnd->clear();
            wnd->draw(space);

            // Setear limite de frames por segundo
            wnd->setFramerateLimit(480);

            while (wnd->pollEvent(event)) {
                if (event.type == Event::Closed)
                    wnd->close();
            }

            updateBatScore();
            updateAiBatScore();

            controls();

            logic();

            update();

            winOrLose();

            wnd->display();
        }

    }
};
