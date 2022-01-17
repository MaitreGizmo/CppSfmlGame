#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "WorldBloc.h"
#include "Player.h"

namespace gst {

    class MainWindow {
    public:
        MainWindow(unsigned width, unsigned height, const std::string& title);

        void render();

    private:
        unsigned         _width;
        unsigned         _height;
        std::string      _title;
        sf::RenderWindow _window;

        std::vector<WorldBloc> _world;
        Player                 _player;

        void dispatchEvents();

        void displayFrame();

        void close();

        void loadMap();

        void detectCollisions();

        void applyGravity();

        void detectCollisionLeftRight(WorldBloc& bloc);

        void detectCollisionTopBottom(WorldBloc& bloc);

        void keyPressed(sf::Event e);

        void keyReleased(sf::Event e);
    };

}

#endif
