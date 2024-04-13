#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "utils.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"
#include "renderer.h"
#include "texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error : Failed to initialize glew" << std::endl;
    
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        vertexArray va;

        vertexBuffer vb(positions, 4 * 4 * sizeof(float));

        vertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        
        indexBuffer ib(indices, 6);

        va.AddBuffer(vb, layout, ib);

        shader sh("src/shaders/basic.glsl");
        sh.Bind();
            
        texture tex("src/textures/awesomeface.png");
        tex.Bind();

        sh.SetUniform1i("u_Texture", 0);

        renderer renderer;

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        sh.Unbind();

        float red = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            
            va.Bind();

            sh.Bind();

            renderer.Draw(va, ib, sh);
            
            if(red > 1.0f)
                red = 0.0f;
            
            red += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}