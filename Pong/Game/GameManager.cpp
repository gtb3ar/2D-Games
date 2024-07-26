#include "GameManager.h"


	void GameManager::UpdateDisplays() { // Updates the displays
		rightDisplay.SetNumber(static_cast<int>(rightPoints));
		leftDisplay.SetNumber(static_cast<int>(leftPoints));
		rightDisplay.setPoisition(screenWidthFloat - (screenWidthFloat / 4) - (screenWidthFloat / 32), margin * 4);
		rightDisplay.setDimensions(screenWidthFloat / 16, ((screenWidthFloat / 16) / 4) * 7);
		rightDisplay.DrawDisplay();
		leftDisplay.setPoisition((screenWidthFloat / 4) - (screenWidthFloat / 32), margin * 4);
		leftDisplay.setDimensions(screenWidthFloat / 16, ((screenWidthFloat / 16) / 4) * 7);
		leftDisplay.DrawDisplay();
	}

	float GameManager::CheckForWin() { // Checks if either player has got the max points
		if (leftPoints == pointMax) {
			Reset();
			return 1;
		}
		else if (rightPoints == pointMax) {
			Reset();
			return 2;
		}
		else {
			return 0;
		}
	}

	void GameManager::Reset() { //Resets the posiitons of the paddles and the ball
		leftPoints = 0;
		rightPoints = 0;
		ball.ResetBallPosition(screenHeightFloat, screenWidthFloat, 20.0f);
		leftPaddle.setPaddlePositionY(screenHeightFloat / 2);
		rightPaddle.setPaddlePositionY(screenHeightFloat / 2);
	}

	GameManager::GameManager(float swf, float shf, float m, float pm, float p) { //Contsructor
		rightPoints = 0;
		leftPoints = 0;
		screenWidthFloat = swf;
		screenHeightFloat = shf;
		margin = m;
		pointMax = pm;
		panel = p;
	}

	void GameManager::setPanel(float p) { //set the panel to display
		panel = p;
	}

	float GameManager::getPanel() {
		return panel;
	}

	void GameManager::IncrementRight() { //Increment player points
		rightPoints = rightPoints + 1;
	}
	void GameManager::IncrementLeft() {
		leftPoints = leftPoints + 1;
	}

	void GameManager::Initialise() { // Initialises the variables
		ball.ResetBallPosition(screenHeightFloat, screenWidthFloat, 100.0f);
		leftPaddle.setPaddlePositionY(screenHeightFloat / 2);
		rightPaddle.setPaddlePositionY(screenHeightFloat / 2);
	}

	void GameManager::Update(float elapsedTime) { // Send information to the display (called every frame)
		UpdateDisplays();
		CheckForWin();
		rightPaddle.VelocityLimiter = paddleLimiters * (ball.getTrueVelocity() / 100);
		leftPaddle.VelocityLimiter = paddleLimiters * (ball.getTrueVelocity() / 100);
		rightPaddle.height = paddleHeights * (100 / ball.getTrueVelocity());
		leftPaddle.height = paddleHeights * (100 / ball.getTrueVelocity());
		rightPaddle.MovePaddle(elapsedTime);
		leftPaddle.MovePaddle(elapsedTime);
		ball.UpdateBall(leftPaddle, rightPaddle, screenHeightFloat, screenWidthFloat, margin, elapsedTime, 0.3f);
		if (ball.DidBallScore(screenWidthFloat, margin * 5) == 1) {
			IncrementLeft();
			ball.ResetBallPosition(screenHeightFloat, screenWidthFloat, 100.0f);
		}
		else if (ball.DidBallScore(screenWidthFloat, margin * 5) == 2) {
			IncrementRight();
			ball.ResetBallPosition(screenHeightFloat, screenWidthFloat, -100.0f);
		}

	}
