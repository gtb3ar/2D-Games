#include "Ball.h"
#include "Main.h"


	void Ball::DrawBall() {
		sf::CircleShape ball(radius);
		ball.setPosition(position.x - radius, position.y - radius);
		ball.setFillColor(color);
		window->draw(ball);
	}

	void Ball::CalculateNewPosition(float timeElapsed) {
		position.x += velocity.x * timeElapsed;
		position.y += velocity.y * timeElapsed;
	}

	void Ball::InvertVelocityX() {
		velocity.x = -velocity.x;
	}
	void Ball::InvertVelocityY() {
		velocity.y = -velocity.y;
	}

	bool Ball::CirularCollisionDetector(float tlX, float tlY, float brX, float brY) {
		std::vector<std::pair<float, float>> points;
		for (int partition = 1; partition <= numberOfPoints; partition++) { //Looping through the partitions
			float partitionAngle = 2 * 3.14159265359f * (static_cast<float>(partition) / numberOfPoints); // Finding the angle of the partition
			float pointX = position.x + radius * std::cos(partitionAngle); //Using Trig to find the intersection with the edge of the circle
			float pointY = position.y + radius * std::sin(partitionAngle);
			points.push_back(std::make_pair(pointX, pointY)); //Storing the vector
		}
		for (int cood = 0; cood < points.size(); cood++) {
			if (BoxCheckHit(points.at(cood).first, points.at(cood).second, tlX, tlY, brX, brY) == true) {
				return true;
			}
		}
		return false;
	}

	void Ball::UpdateBall(Paddle one, Paddle two, float screenHeight, float screenWidth, float margin, float timeElapsed, float rigidity) {
		float diffX;
		float diffY;
		bool collision = false;
		bool invertY = false;
		bool invertX = false;
		float rigidityCoeffecient = 1 - rigidity;
		if (clock.getElapsedTime().asSeconds() > 1) {
			if (CirularCollisionDetector(one.getPaddleRail() - one.getPaddleWidth() / 2, one.getPaddlePostion() - one.height / 2, one.getPaddleRail() + one.getPaddleWidth() / 2, one.getPaddlePostion() + one.height / 2)) {
				diffX = abs(one.getPaddleRail() - position.x);
				diffY = abs(one.getPaddlePostion() - position.y);
				collision = true;
				clock.restart();
				if (one.getPaddlePostion() - position.y > 0) {
					invertY = true;
				}
				invertX = true;
			}
			else if (CirularCollisionDetector(two.getPaddleRail() - two.getPaddleWidth() / 2, two.getPaddlePostion() - two.height / 2, two.getPaddleRail() + two.getPaddleWidth() / 2, two.getPaddlePostion() + two.height / 2)) {
				diffX = abs(two.getPaddleRail() - position.x);
				diffY = abs(two.getPaddlePostion() - position.y);
				collision = true;
				clock.restart();
				if (two.getPaddlePostion() - position.y > 0) {
					invertY = true;
				}
			}
		}
		if (collision) {
			collisionSound.play();
			float ratioX = diffX / (diffX + diffY);
			float ratioY = diffY / (diffX + diffY);
			diffX = abs(velocity.x) + 20;
			diffY = abs(velocity.y) + 20;

			if (!invertX) {
				velocity.x = (((diffX + diffY) * ratioX) * rigidity) + (diffX * rigidityCoeffecient);
			}
			else {
				velocity.x = ((-(diffX + diffY) * ratioX) * rigidity) + (-diffX * rigidityCoeffecient);
			}

			if (!invertY) {
				velocity.y = (((diffX + diffY) * ratioY) * rigidity) + (diffY * rigidityCoeffecient);
			}
			else {
				velocity.y = ((-(diffX + diffY) * ratioY) * rigidity) + (-diffY * rigidityCoeffecient);
			}

			InvertVelocityX();
		}
		else if (position.y - radius <= margin) {
			collisionSound.play();
			InvertVelocityY();
		}
		else if (position.y + radius >= screenHeight - margin) {
			collisionSound.play();
			InvertVelocityY();
		}

		CalculateNewPosition(timeElapsed);
		DrawBall();
	}

	int Ball::DidBallScore(float screenWidth, float goal) {
		if (position.x - radius <= goal) {
			return 1;
		}
		else if (position.x + radius >= screenWidth - goal) {
			return 2;
		}
		else {
			return 0;
		}
	}

	void Ball::SetRadius(float newRadius) {
		radius = newRadius;
	}

	void Ball::ResetBallPosition(float screenHeight, float screenWidth, float inputVelocity) {
		position.y = screenHeight / 2;
		position.x = screenWidth / 2;
		velocity.y = 0;
		velocity.x = inputVelocity;

	}

	float Ball::getTrueVelocity() {
		float absoluteX = abs(velocity.x);
		float absoluteY = abs(velocity.y);
		return sqrt((absoluteX * absoluteX) + (absoluteY * absoluteY));
	}