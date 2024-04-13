#pragma once

#define GLEW_STATIC

#include <GL/glew.h>

#define GLCall(x) GLClearError();\
    x;\
    GLCheckError();

void GLClearError();

void GLCheckError();