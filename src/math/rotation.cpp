#define _USE_MATH_DEFINES
#include "math.h"

#include "vertexBuffer.h"

void rotate(vertexBuffer& vb, int frameNumber)
{
    float theta = float(frameNumber) / 240.0f * M_PI;
    float cosine = cosf(theta);
    float sine = sinf(theta);


    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.0f, 0.5f, 1.0f, 0.0f,
    };
    
    positions[0] = -0.5f * cosine + -0.5f *sine;
    positions[1] = 0.5f * sine + -0.5f *cosine;

    positions[4] = 0.5f * cosine + -0.5f *sine;
    positions[5] = -0.5f * sine + -0.5f *cosine;

    positions[8] = 0.5f *sine;
    positions[9] = 0.5f *cosine;

    vb.UpdateBuffer(positions, 4 * 4 * sizeof(float));
}