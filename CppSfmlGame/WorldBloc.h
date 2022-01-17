#ifndef WORLD_BLOC_H
#define WORLD_BLOC_H

#include <SFML/Graphics.hpp>

#include "Settings.h"

namespace cpp_sfml {
    class WorldBloc {
    public:
        WorldBloc(sf::Vector2f& pos, sf::Color& color, float size);

        sf::Vector2f getPos();

        sf::VertexArray getVertex();

        sf::VertexArray& getVertexRef();

        static cpp_sfml::WorldBlocType getType(sf::Color color);

    private:
        sf::Vector2f            _position;
        sf::VertexArray         _vertex;
        cpp_sfml::WorldBlocType _type;

        sf::Color getRenderColor();

    };
}


#endif //WORLD_BLOC_H
