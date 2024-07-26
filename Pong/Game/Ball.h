#ifndef BALL_H
#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Main.h"
#include "Paddle.h"
#include "Helpers.h"
class Ball { 
private:

	struct Vector2 {
		float x;
		float y;
	};
	Vector2 position{ 0,0 };
	Vector2 velocity{ 0,0 };

	float numberOfPoints = 16; //How many points should be marked on the edge of the ball
	float radius = 5; // The radius of the ball
	sf::Clock clock; //timer used to implement a collision grace period 

	void DrawBall(); // Draw ball in window
	void CalculateNewPosition(float timeElapsed); //Calculated the amount the ball should move based on current velocity
	void InvertVelocityX(); //Invert the velocity applied to the ball
	void InvertVelocityY();
	bool CirularCollisionDetector(float tlX, float tlY, float brX, float brY); // Detects n points on a ball and asks if the are inside a paddle or edge

public:
	sf::Sound collisionSound = LoadSound("Collision.wav"); // Sound efect
	sf::Color color = sf::Color::White; // Ball color

	void UpdateBall(Paddle one, Paddle two, float screenHeight, float screenWidth, float margin, float timeElapsed, float rigidity); //Combines the collision detection and new poisiotn and the displays the ball
	int DidBallScore(float screenWidth, float goal);
	void SetRadius(float newRadius);
	void ResetBallPosition(float screenHeight, float screenWidth, float inputVelocity);
	float getTrueVelocity(); // Returns the velocity of the ball (trig)
};

#endif // !BALL_H


