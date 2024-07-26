#ifndef paddle_h
#define paddle_h

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Paddle
{
private:
	//Defining variables
	float width;
	float paddleRail;
	float paddlePosition;

	float upperBound;
	float lowerBound;
	sf::Color paddleColor = sf::Color::White;
	float mouseControl;

	void DrawPaddle();

	float CalculateDisplacement(float previousPosition, float newPosition, float timeElapsed);

public:
	float VelocityLimiter;
	float height;

	void MovePaddle(float timeElapsed);

	float getPaddleWidth();

	float getPaddleRail();

	float getPaddlePostion();

	void setPaddlePositionY(float newY);

	Paddle(float inputWidth, float inputHeight, float rail, float screenHeight, float margin, float mouse, float limiter);

};

#endif

