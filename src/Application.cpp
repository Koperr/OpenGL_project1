#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "Renderer.h"
//3232

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

void RGB(float& r, float& g, float& b, float& iR, float& iG, float& iB)
{
    if (r > 1.0f)
        iR = -0.003f;
    else if (r < 0.0f)
        iR = 0.003f;
    if (g > 1.0f)
        iG = -0.005f;
    else if (g < 0.0f)
        iG = 0.005f;
    if (b > 1.0f)
        iB = -0.007f;
    else if (b < 0.0f)
        iB = 0.007f;

    r += iR;
    g += iG;
    b += iB;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,// 0
         0.5f, -0.5f, 1.0f, 0.0f,// 1
         0.5f,  0.5f, 1.0f, 1.0f,// 2
        -0.5f,  0.5f, 0.0f, 1.0f// 3
    };

    unsigned int indices[] = {
        0, 1, 2, // 1st triangle indices
        2, 3, 0  // 2nd triangle indices
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);


    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/Basic.shader");
    shader.Bind();
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float incrementR = 0.005f;
    float incrementG = 0.000f;
    float incrementB = 0.007f;
    shader.SetUniform4f("u_Color", r, g, b, 1.0f);

    Texture texture("res/textures/jareczek.png");
    texture.Bind(); // ta cyferka musi sie zgadzac z ta cyferka nizej w SetUniform1i()
    shader.SetUniform1i("u_Texture", 0);

    va.UnBind();
    vb.UnBind();
    ib.UnBind();
    shader.UnBind();

    Renderer renderer;

    ////////////// GAME LOOP ////////////////
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();


        shader.Bind();
        shader.SetUniform4f("u_Color", r, g, b, 1.0f);
        
        renderer.Draw(va, ib, shader);
        
        RGB(r, g, b, incrementR, incrementG, incrementB);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}