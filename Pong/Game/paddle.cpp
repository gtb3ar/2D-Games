
#include "Paddle.h"
#include "Helpers.h"
#include "Main.h"

	void Paddle::DrawPaddle() {
		sf::RectangleShape paddle(sf::Vector2f(width, height));
		paddle.setPosition(paddleRail - width / 2, paddlePosition - height / 2);
		paddle.setFillColor(paddleColor);
		window->draw(paddle);
	}

	float Paddle::CalculateDisplacement(float previousPosition, float newPosition, float timeElapsed) {
		float displacement = (newPosition - previousPosition);
		if (displacement > VelocityLimiter) {
			newPosition = (previousPosition + VelocityLimiter * timeElapsed);
		}
		else if (displacement < -VelocityLimiter) {
			newPosition = (previousPosition - VelocityLimiter * timeElapsed);
		}
		return newPosition;

	}

	void Paddle::MovePaddle(float timeElapsed) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		if (mouseControl == 0) {
			paddlePosition = CalculateDisplacement(paddlePosition, static_cast<float>(mousePosition.y), timeElapsed);

		}
		else if (mouseControl == 1) {
			if (IsKeyPressed(sf::Keyboard::W)) {
				paddlePosition = CalculateDisplacement(paddlePosition, static_cast<float>(-200), timeElapsed);
			}
			else if (IsKeyPressed(sf::Keyboard::S)) {
				paddlePosition = CalculateDisplacement(paddlePosition, static_cast<float>(800), timeElapsed);
			}
			else {
				paddlePosition = paddlePosition;
			}
		}
		else if (mouseControl == 2) {
			if (IsKeyPressed(sf::Keyboard::Up)) {
				paddlePosition = CalculateDisplacement(paddlePosition, static_cast<float>(-200), timeElapsed);
			}
			else if (IsKeyPressed(sf::Keyboard::Down)) {
				paddlePosition = CalculateDisplacement(paddlePosition, static_cast<float>(800), timeElapsed);
			}
			else {
				paddlePosition = paddlePosition;
			}
		}
		if (paddlePosition - height / 2 <= upperBound) {
			paddlePosition = upperBound + height / 2;
		}
		else if (paddlePosition + height / 2 >= lowerBound) {
			paddlePosition = lowerBound - height / 2;
		}
		DrawPaddle();
	}

	float Paddle::getPaddleWidth() {
		return width;
	}

	float Paddle::getPaddleRail() {
		return paddleRail;
	}

	float Paddle::getPaddlePostion() {
		return paddlePosition;
	}

	void Paddle::setPaddlePositionY(float newY) {
		paddlePosition = newY;
	}

	Paddle::Paddle(float inputWidth, float inputHeight, float rail, float screenHeight, float margin, float mouse, float limiter) {
		width = inputWidth;
		height = inputHeight;
		paddleRail = rail;
		upperBound = margin;
		lowerBound = screenHeight - margin;
		paddlePosition = screenHeight / 2;
		mouseControl = mouse;
		VelocityLimiter = limiter;

	}




