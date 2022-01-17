#include "Player.h"
#include "Settings.h"

using namespace std;
using namespace cpp_sfml;
using namespace sf;

Player::Player() = default;

Player::Player(Vector2f pos) {
	_position = pos;
	_movement = Vector2f(0.f, 0.f);

	float x = pos.x;
	float y = pos.y;
	float size = PLAYER_SIZE;

	_vertex = sf::VertexArray(PrimitiveType::Quads, 4);

	_vertex[0].position = Vector2f(x + 0000, y + 0000);
	_vertex[1].position = Vector2f(x + 0000, y + size);
	_vertex[2].position = Vector2f(x + size, y + size);
	_vertex[3].position = Vector2f(x + size, y + 0000);

	Color renderColor = Color::Red;

	_vertex[0].color = renderColor;
	_vertex[1].color = renderColor;
	_vertex[2].color = renderColor;
	_vertex[3].color = renderColor;
}

Vector2f Player::getPos() {
	return _position;
}

VertexArray Player::getVertex() {
	return _vertex;
}

VertexArray& Player::getVertexRef() {
	return _vertex;
}

void Player::addMove(Vector2f move) {
	_movement += move;
}

void Player::subMove(Vector2f move) {
	_movement -= move;
}

void Player::stopMoveX() {
	_movement.x = 0.f;
}

void Player::stopMoveY() {
	_movement.y = 0.f;
}

void Player::applyMove() {
	_position += _movement;

	_vertex[0].position += _movement;
	_vertex[1].position += _movement;
	_vertex[2].position += _movement;
	_vertex[3].position += _movement;
}

sf::Vector2f Player::getMove() {
	return _movement;
}

void Player::setPosX(float x) {
	_position.x = x;

	_vertex[0].position.x = x;
	_vertex[1].position.x = x;
	_vertex[2].position.x = x + PLAYER_SIZE;
	_vertex[3].position.x = x + PLAYER_SIZE;
}

void Player::setPosY(float y) {
	_position.y = y;

	_vertex[0].position.y = y;
	_vertex[1].position.y = y + PLAYER_SIZE;
	_vertex[2].position.y = y + PLAYER_SIZE;
	_vertex[3].position.y = y;
}

