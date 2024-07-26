#include "CommonMath.h"
#include "CommonStruct.h"
#include <corecrt_math.h>
#include "Main.h"

float ClampF(float input, float max, float min) {
	if (input > max) {
		input = max;
	}
	else if (input < min) {
		input = min;
	}
	return input;
}

float ReMapF(float input, float inputMax, float inputMin, float newMax, float newMin) {
	return (((input - inputMin) / (inputMax - inputMin)) * newMax) + newMin;
}

FloatVector2 CalculateVertexFromRadian(float radian, float radius, float x, float y ) {
	FloatVector2 vertexPosition;
	vertexPosition.x = cos(radian) * radius + x;
	vertexPosition.y = sin(radian) * radius + y;
	return vertexPosition;
}

float ClampedRandomF(float low, float high) {
	return ReMapF(rand(), 32767, 0, high, low);
}