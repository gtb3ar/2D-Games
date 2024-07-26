#ifndef BUTTON_H
#include <SFML\Graphics.hpp>
#pragma once
class Button {
private:
	struct Vector2 {
		float x;
		float y;
	};

	Vector2 position;
	Vector2 dimension;

	int fontSize;
	sf::String textContent;
	sf::String fontType;

	sf::Color borderColor;
	sf::Color textColor;

	Vector2 topLeft;
	Vector2 bottomRight;

	bool buttonPressed;
	void DrawBorder();
	void DrawText();

public:
	Button(float positionX, float positionY, float dimensionX, float dimensionY, sf::Color b, sf::Color t, int fs, sf::String ft, sf::String tc);
	void resetButton();
	bool getPressed();
	void Update();
};

#endif // !BUTTON_H




