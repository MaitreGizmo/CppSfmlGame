#include <iostream>
#include <cstdlib>
#include <limits>

#include "MainWindow.h"
#include "Settings.h"

using namespace std;
using namespace cpp_sfml;

int main() {
	MainWindow mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

	mainWindow.render();

	cout << "Press ENTER to quit ...";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return EXIT_SUCCESS;
}