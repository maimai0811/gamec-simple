#include <iostream>
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main() {
    //Game ne di copy thui hehe
    //Init srand
    srand(static_cast<unsigned>(time(NULL)));

    //Init game engine
    Game game;

    //Game loop
    while (game.running() && !game.getEndGame()) {

        //Update
        game.update();


        //Render
        game.render();
    }

    //End app
    return 0;
}