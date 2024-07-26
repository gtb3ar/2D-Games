//Including main and classes
#include "Main.h"
#include "Helpers.h"
#include "Paddle.h"
#include "SevenSegmentDisplay.h"
#include "Ball.h"
#include "Button.h"
#include "GameManager.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>

struct Vector2 { //Vector2 structure
	float x;
	float y;
};

Vector2 mousePosition, mousePreviousPosition;		// Definig vectors used to store the current and previous mouse x and y

float totalTime = 0.0f;		// Total number of seconds since the program started

// Define variables which determine how big the window will be
float SCREEN_WIDTH = 800;
float SCREEN_HEIGHT = 600;
float margin = 5;

//Defining buttons for the home screen panel
Button playButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, sf::Color::White, sf::Color::White, 69, "SquarePixel", "PLAY");
Button exitButton(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 4), SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, sf::Color::White, sf::Color::White, 69, "SquarePixel", "EXIT");
Button title(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 3.5f), SCREEN_WIDTH / 3, SCREEN_HEIGHT / 6, sf::Color::Black, sf::Color::White, 120, "SquarePixel", "PONG");

//Defining Game Manager which houses all oter classes and logic for the game
GameManager gameManager(SCREEN_WIDTH,SCREEN_HEIGHT,margin, 5,0);

// GameInit is called once, when the program starts. Its job is to do things which only happen once, at the start.
void GameInit()
{
	// Create a window for the game
	// The numbers are the width and height in pixels. The text is the title of the window.
	window = new sf::RenderWindow(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "SFML Project - Pong");
	gameManager.Initialise();
}

// A function that returns the mouses position
void UpdateMousePosition() {
	mousePosition.x = (float)GetMouseX();
	mousePosition.y = (float)GetMouseY();
}

// GameLoop is called repeatedly. Its job is to update the 'game', and draw the screen.
void GameLoop(float elapsedSeconds)
{	// Determining which panel should be displayed by the game manager
	float panel = gameManager.getPanel();
	if (panel == 1) { //panel 1 - Game
		gameManager.Update(elapsedSeconds); //Update the screen with new data
		totalTime = totalTime + elapsedSeconds; // Keep a running total of how much time has passed
		UpdateMousePosition(); //Updating the vectors

		//Drawing border for the game
		bool toggle = true;
		for (float currentPixel = margin; currentPixel <= SCREEN_HEIGHT - margin; currentPixel += SCREEN_HEIGHT / 32) {
			if (toggle) {
				DrawLine((SCREEN_WIDTH / 2), currentPixel, (SCREEN_WIDTH / 2), currentPixel + margin, sf::Color::White);
				DrawLine((SCREEN_WIDTH - margin * 5), currentPixel, (SCREEN_WIDTH - margin * 5), currentPixel + margin, sf::Color::White);
				DrawLine((margin * 5), currentPixel,(margin * 5), currentPixel + margin, sf::Color::White);
			}
			else {
				toggle = true;
			}
		}
	}
	else if (panel == 0){ // Panel 0 - Main menu
		playButton.Update(); // Updates the buttons
		exitButton.Update();
		title.Update();

		if (playButton.getPressed()) { // Switch to game if "play" is pressed
			gameManager.setPanel(1);
		}
		else if (exitButton.getPressed()) { // Close game
			window->close();
		}
	}
	
	//Drawing border for the menu
	DrawLine(margin, margin, SCREEN_WIDTH-margin, margin, sf::Color::White);
	DrawLine(margin, margin, margin, SCREEN_HEIGHT - margin, sf::Color::White);
	DrawLine(margin, SCREEN_HEIGHT-margin, SCREEN_WIDTH - margin, SCREEN_HEIGHT - margin, sf::Color::White);
	DrawLine(SCREEN_WIDTH - margin, margin, SCREEN_WIDTH - margin, SCREEN_HEIGHT - margin, sf::Color::White);
}
