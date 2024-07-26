
#ifndef COMMONMATH_H
#include "CommonStruct.h"
#pragma once

float ClampF(float input, float max, float min);

float ReMapF(float input, float inputMax, float inputMin, float newMax, float newMin);

FloatVector2 CalculateVertexFromRadian(float radian, float radius, float x, float y);

float ClampedRandomF(float low, float high);
#endif // !COMMONMATH_H



