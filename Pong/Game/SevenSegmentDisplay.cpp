#include "SevenSegmentDisplay.h"
#include "Helpers.h"

	
	void SevenSegmentDisplay::setPoisition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void SevenSegmentDisplay::setDimensions(float x, float y) {
		dimension.x = x;
		dimension.y = y;
		margin.x = x / 4;
		margin.y = y / 7;
	}

	void SevenSegmentDisplay::SetNumber(int number) {
		switch (number) {
		case 0:
			bools.one = true;
			bools.two = true;
			bools.three = true;
			bools.four = false;
			bools.five = true;
			bools.six = true;
			bools.seven = true;
			break;
		case 1:
			bools.one = false;
			bools.two = false;
			bools.three = true;
			bools.four = false;
			bools.five = false;
			bools.six = true;
			bools.seven = false;
			break;
		case 2:
			bools.one = true;
			bools.two = false;
			bools.three = true;
			bools.four = true;
			bools.five = true;
			bools.six = false;
			bools.seven = true;
			break;
		case 3:
			bools.one = true;
			bools.two = false;
			bools.three = true;
			bools.four = true;
			bools.five = false;
			bools.six = true;
			bools.seven = true;
			break;
		case 4:
			bools.one = false;
			bools.two = true;
			bools.three = true;
			bools.four = true;
			bools.five = false;
			bools.six = true;
			bools.seven = false;
			break;
		case 5:
			bools.one = true;
			bools.two = true;
			bools.three = false;
			bools.four = true;
			bools.five = false;
			bools.six = true;
			bools.seven = true;
			break;
		case 6:
			bools.one = true;
			bools.two = true;
			bools.three = false;
			bools.four = true;
			bools.five = true;
			bools.six = true;
			bools.seven = true;
			break;
		case 7:
			bools.one = true;
			bools.two = false;
			bools.three = true;
			bools.four = false;
			bools.five = false;
			bools.six = true;
			bools.seven = false;
			break;
		case 8:
			bools.one = true;
			bools.two = true;
			bools.three = true;
			bools.four = true;
			bools.five = true;
			bools.six = true;
			bools.seven = true;
			break;
		case 9:
			bools.one = true;
			bools.two = true;
			bools.three = true;
			bools.four = true;
			bools.five = false;
			bools.six = true;
			bools.seven = false;
			break;
		default:
			break;
		}
	}

	void SevenSegmentDisplay::DrawDisplay() {
		for (int segment = 1; segment <= 7; segment++) {
			switch (segment) {
			case 1:
				if (bools.one) {
					DrawRectangle(position.x + margin.x, position.y, dimension.x / 2, margin.y, color);
				}
				break;
			case 2:
				if (bools.two) {
					DrawRectangle(position.x, position.y + margin.y, margin.x, margin.y * 2, color);
				}
				break;
			case 3:
				if (bools.three) {
					DrawRectangle(position.x + (dimension.x - margin.x), position.y + margin.y, margin.x, margin.y * 2, color);
				}
				break;
			case 4:
				if (bools.four) {
					DrawRectangle(position.x + margin.x, position.y + margin.y * 3, dimension.x / 2, margin.y, color);
				}
				break;
			case 5:
				if (bools.five) {
					DrawRectangle(position.x, position.y + margin.y * 4, margin.x, margin.y * 2, color);
				}
				break;
			case 6:
				if (bools.six) {
					DrawRectangle(position.x + (dimension.x - margin.x), position.y + margin.y * 4, margin.x, margin.y * 2, color);
				}
				break;
			case 7:
				if (bools.seven) {
					DrawRectangle(position.x + margin.x, position.y + (dimension.y - margin.y), dimension.x / 2, margin.y, color);
				}
				break;
			default:
				break;
			}
		}
	}

