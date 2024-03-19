#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "shader.h"

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
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        vertexArray va;

        vertexBuffer vb(positions, 4 * 2 * sizeof(float));

        vertexBufferLayout layout;
        layout.Push<float>(2);
        
        indexBuffer ib(indices, 6);

        va.AddBuffer(vb, layout, ib);

        shader sh("src/shaders/basic.glsl");
        sh.Bind();
        sh.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

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
            glClear(GL_COLOR_BUFFER_BIT);
            
            va.Bind();

            sh.Bind();
            sh.SetUniform4f("u_Color", red, 1.0f, 0.0f, 1.0f);

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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