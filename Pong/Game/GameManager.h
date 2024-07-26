#ifndef GM_D
#define GM_D

#include "Ball.h"
#include "SevenSegmentDisplay.h"
#include "Paddle.h"

#pragma once
class GameManager {
private:

	float rightPoints; //Player point storage
	float leftPoints;
	float pointMax; //Points required to win

	float screenWidthFloat; //Window dimensions
	float screenHeightFloat;
	float margin;

	float panel; //Stores which panel should be displayed at the time

	SevenSegmentDisplay rightDisplay; //displays for player scores
	SevenSegmentDisplay leftDisplay;

	float paddleLimiters = 100.0f; //Some adjustable modifiers for the paddles to adjust difficulty
	float paddleHeights = 100.0f;

	Paddle rightPaddle = { 10, paddleHeights, 750, 600, 5, 2, paddleLimiters }; 
	Paddle leftPaddle = { 10, paddleHeights, 50, 600, 5, 1, paddleLimiters };
	Ball ball;

	void UpdateDisplays(); //Update scores 
	float CheckForWin(); //Check if a player has won
	void Reset(); //Reset the posiitons of the ball and players.

public:
	//Constructor
	GameManager(float swf, float shf, float m, float pm, float p);
	void setPanel(float p);
	float getPanel();
	void IncrementRight();
	void IncrementLeft();
	void Initialise();
	void Update(float elapsedTime);
};

#endif // !GM_D




