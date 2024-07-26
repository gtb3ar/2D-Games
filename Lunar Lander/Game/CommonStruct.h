
#ifndef COMMONSTRUCT_H
#define COMMONSTRUCT_H


#pragma once
struct FloatVector2 {
    // Member variables
    float x;
    float y;

    // Constructor declaration (if needed)
    FloatVector2(float xInput, float yInput);  // Default constructor

    FloatVector2();
};

struct Vertex {
    float radian;
    float radius;

    Vertex();
};


#endif


