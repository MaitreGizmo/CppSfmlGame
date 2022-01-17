#include <iostream>
#include <chrono>

#include "MainWindow.h"
#include "Settings.h"

using namespace std;
using namespace std::chrono;
using namespace cpp_sfml;
using namespace sf;

MainWindow::MainWindow(unsigned width, unsigned height, const string& title) {
	_width = width;
	_height = height;
	_title = title;
}

void MainWindow::render() {
	_window.create(VideoMode(_width, _height), _title, Style::Close);

	loadMap();

	_player = Player(Vector2f(1200, 20));
	_player.addMove(Vector2f(0, GRAVITY));

	time_point<system_clock> timePoint = system_clock::now();

	while (_window.isOpen()) {
		if ((system_clock::now().time_since_epoch() - timePoint.time_since_epoch()) >=
			chrono::milliseconds(TIME_PER_FRAME)) {

			dispatchEvents();

			applyGravity();

			_player.applyMove();

			detectCollisions();

			displayFrame();

			timePoint = system_clock::now();
		}

	}
}

void MainWindow::dispatchEvents() {
	Event e;

	while (_window.pollEvent(e)) {
		switch (e.type) {
		case Event::Closed:
			close();
			break;
		case Event::KeyPressed:
			keyPressed(e);
			break;
		case Event::KeyReleased:
			keyReleased(e);
			break;
		}
	}
}

void MainWindow::displayFrame() {
	_window.clear(WINDOW_BACK_COLOR);

	// display world
	for (WorldBloc& bloc : _world) {
		_window.draw(bloc.getVertexRef());
	}

	// display player
	_window.draw(_player.getVertexRef());

	_window.display();
}

void MainWindow::close() {
	_window.close();
}

void MainWindow::loadMap() {
	Image map;
	map.loadFromFile(MAP_FILE_LOCATION);

	for (int x = 0; x < 80; ++x) {
		float posX = x * WORLD_BLOC_SIZE;

		for (int y = 0; y < 40; ++y) {
			Color color = map.getPixel(x, y);

			if (WorldBloc::getType(color) != WorldBlocType::BACKGROUND) {
				Vector2f pos(posX, y * WORLD_BLOC_SIZE);

				WorldBloc bloc(pos, color, WORLD_BLOC_SIZE);

				_world.push_back(bloc);
			}
		}
	}
}

void MainWindow::detectCollisions() {
	FloatRect playerHitbox = _player.getVertexRef().getBounds();

	// detect intersections between player and world blocs
	for (WorldBloc& bloc : _world) {
		if (playerHitbox.intersects(bloc.getVertexRef().getBounds())) {
			if (_player.getMove().x > _player.getMove().y && _player.getMove().x != 0) {
				cout << "> detect collision left/right ..." << endl;
				detectCollisionLeftRight(bloc);
			}
			else if (_player.getMove().y > _player.getMove().x && _player.getMove().y != 0) {
				cout << "> detect collision top/bottom ..." << endl;
				detectCollisionTopBottom(bloc);
			}
			else {
				cout << "> detect collision left/right/top/bottom ..." << endl;
				detectCollisionLeftRight(bloc);
				detectCollisionTopBottom(bloc);
			}

		}
	}
}

void MainWindow::keyPressed(Event e) {
	switch (e.key.code) {
	case Keyboard::Left:
		if (!_player.moveLeft) {
			_player.moveLeft = true;
			_player.addMove(Vector2f((-1.f) * SPEED_LEFT_RIGHT, 0));
		}
		break;
	case Keyboard::Right:
		if (!_player.moveRight) {
			_player.addMove(Vector2f(SPEED_LEFT_RIGHT, 0));
			_player.moveRight = true;
		}
		break;
	case Keyboard::Space:
		if (!_player.moveTop) {
			_player.addMove(Vector2f(0, (-1) * JUMP_STRENGTH));
			_player.moveTop = true;
		}
		break;
	}
}

void MainWindow::keyReleased(Event e) {
	switch (e.key.code) {
	case Keyboard::Left:
		if (_player.moveLeft) {
			_player.subMove(Vector2f((-1) * SPEED_LEFT_RIGHT, 0));
			_player.moveLeft = false;
		}
		break;
	case Keyboard::Right:
		if (_player.moveRight) {
			_player.subMove(Vector2f(SPEED_LEFT_RIGHT, 0));
			_player.moveRight = false;
		}
		break;
	}
}

void MainWindow::applyGravity() {
	Vector2f gravityMove(0, GRAVITY);

	if (_player.moveBottom) {
		_player.addMove(gravityMove);
	}
	else { // check if there is a block underneath
		VertexArray vertex = _player.getVertex();
		vertex[0].position += gravityMove;
		vertex[1].position += gravityMove;
		vertex[2].position += gravityMove;
		vertex[3].position += gravityMove;

		FloatRect playerHitbox = vertex.getBounds();

		bool blocUnderneath = false;

		for (WorldBloc& bloc : _world) {
			if (playerHitbox.intersects(bloc.getVertexRef().getBounds())) {
				blocUnderneath = true;
				_player.moveBottom = false;
			}
		}

		if (!blocUnderneath) {
			_player.addMove(gravityMove);
			_player.moveBottom = true;
		}
	}
}

void MainWindow::detectCollisionLeftRight(WorldBloc& bloc) {
	float px = _player.getPos().x;
	float bx = bloc.getPos().x;

	if (_player.moveRight) {
		if (px + PLAYER_SIZE > bx) {
			float delta = (px + PLAYER_SIZE) - bx;
			_player.setPosX(px - delta);
			_player.stopMoveX();
			_player.moveRight = false;

			cout << "> collision : right" << endl;
		}
	}
	else if (_player.moveLeft) {
		if (px < bx + WORLD_BLOC_SIZE) {
			float delta = px - (bx + WORLD_BLOC_SIZE);
			_player.setPosX(px + delta);
			_player.stopMoveX();
			_player.moveLeft = false;

			cout << "> collision : left" << endl;
		}
	}
}

void MainWindow::detectCollisionTopBottom(WorldBloc& bloc) {
	float py = _player.getPos().y;
	float by = bloc.getPos().y;

	if (_player.moveBottom) {
		if (py + PLAYER_SIZE > by) {
			float delta = py + PLAYER_SIZE - by;
			_player.setPosY(py - delta);
			_player.stopMoveY();
			_player.moveBottom = false;
			_player.moveTop = false;

			cout << "> collision : bottom" << endl;
		}
		else {
			_player.moveBottom = true;
			_player.moveTop = false;
		}
	}
	else if (_player.moveTop) {
		if (py < by + WORLD_BLOC_SIZE) {
			float delta = (by + WORLD_BLOC_SIZE) - py;
			_player.setPosY(py + delta);
			_player.stopMoveY();
			_player.moveTop = false;

			cout << "> collision : top" << endl;
		}
	}
}


