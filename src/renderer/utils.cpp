#include "utils.h"

#include <iostream>

void GLClearError()
{
    while ( glGetError() != GL_NO_ERROR );
}

void GLCheckError()
{
    while ( GLenum error = glGetError() )
    {
        std::cout << "OpenGl Error : " << error << std::endl;
    }
}
