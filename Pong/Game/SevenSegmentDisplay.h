#ifndef SSD_H
#define SSD_H
#include "Helpers.h"

#pragma once
class SevenSegmentDisplay {
private:
	struct SegmentBool { //Sructure used to store which segments should be on or off
		bool one;
		bool two;
		bool three;
		bool four;
		bool five;
		bool six;
		bool seven;
	};
	struct Vector2 { //Structure used to store transform data
		float x;
		float y;
	};

	SegmentBool bools{ false, false, false, false, false, false, false };
	Vector2 position{ 0,0 };
	Vector2 dimension{ 0,0 };
	Vector2 margin{ 0,0 };
	sf::Color color = sf::Color::White;

public:
	//set the position of the display
	void setPoisition(float x, float y);

	//set the size of the diplay
	void setDimensions(float x, float y);

	//Set the number of the display
	void SetNumber(int number);

	//Update the display on the scren
	void DrawDisplay();
};



#endif SSD_H


