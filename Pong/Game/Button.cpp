#include "Button.h"
#include "Helpers.h"
#include "Main.h"

	void Button::DrawBorder() {
		DrawLine(topLeft.x, topLeft.y, bottomRight.x, topLeft.y, borderColor);
		DrawLine(bottomRight.x, topLeft.y, bottomRight.x, bottomRight.y, borderColor);
		DrawLine(bottomRight.x, bottomRight.y, topLeft.x, bottomRight.y, borderColor);
		DrawLine(topLeft.x, bottomRight.y, topLeft.x, topLeft.y, borderColor);
	}

	void Button::DrawText() {
		sf::Font font;
		if (font.loadFromFile(fontType + ".ttf")) {
			sf::Text text;
			text.setFont(font);
			text.setString(textContent);
			text.setCharacterSize(fontSize);
			text.setFillColor(textColor);
			sf::FloatRect textRect = text.getLocalBounds();
			text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			text.setPosition(sf::Vector2f(position.x, position.y));

			window->draw(text);
		}
	}

	Button::Button(float positionX, float positionY, float dimensionX, float dimensionY, sf::Color b, sf::Color t, int fs, sf::String ft, sf::String tc) {
		position.x = positionX;
		position.y = positionY;
		dimension.x = dimensionX;
		dimension.y = dimensionY;
		borderColor = b;
		textColor = t;
		fontSize = fs;
		fontType = ft;
		textContent = tc;
		topLeft = { position.x - dimension.x / 2, position.y - dimension.y / 2 };
		bottomRight = { position.x + dimension.x / 2, position.y + dimension.y / 2 };
		buttonPressed = false;
	}

	void Button::resetButton() {
		buttonPressed = false;
	}

	bool Button::getPressed() {
		return buttonPressed;
	}

	void Button::Update() {
		DrawBorder();
		DrawText();
		if (IsMouseButtonPressed() && BoxCheckHit(static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()), topLeft.x, topLeft.y, bottomRight.x, bottomRight.y)) {
			buttonPressed = true;
		}
	}

