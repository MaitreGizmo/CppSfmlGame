#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

namespace gst {
    class Player {
    public:
        Player();

        explicit Player(sf::Vector2f pos);

        sf::Vector2f getPos();

        sf::VertexArray getVertex();

        sf::VertexArray& getVertexRef();

        sf::Vector2f getMove();

        void addMove(sf::Vector2f move);

        void subMove(sf::Vector2f move);

        void stopMoveX();

        void stopMoveY();

        void applyMove();

        void setPosX(float x);

        void setPosY(float y);

        bool moveLeft = false;
        bool moveRight = false;
        bool moveTop = false;
        bool moveBottom = false;

    private:
        sf::VertexArray _vertex;
        sf::Vector2f    _position;
        sf::Vector2f    _movement;
    };
}


#endif //PLAYER_H
