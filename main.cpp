

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "RawModel.h"
#include "Loader.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "StaticShader.h"

#include "TexturedModel.h"
#include "Maths.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    StaticShader shader;

    Loader loader;
    Renderer renderer;


  float vertices[] = {
    -0.5, 0.5, 0,
    -0.5, -0.5, 0,

    0.5, -0.5, 0,
    0.5, 0.5, 0
  };
  unsigned int indices[] = { 0, 1, 3, 3, 1, 2 };
  float textureCoords[] =
  {
    0, 0,
    0, 1,
    1, 1,
    1, 0
  };
    SizedArray<float> verticesArr(vertices, sizeof(vertices));
    SizedArray<unsigned int> indicesArr(indices, sizeof(indices));
    SizedArray<float> textureCoordsArr(textureCoords, sizeof(textureCoords));


    RawModel model = loader.loadToVAO(verticesArr, textureCoordsArr, indicesArr);
    ModelTexture texture(loader.loadTexture("resources/textures/image.png"));

    TexturedModel texturedModel(model, texture);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------

    float rotation = 0;

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        renderer.prepare();

        // render
        // ------
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        shader.start();
        shader.loadColour(glm::vec3(1.0, 0.0, 1.0));
        rotation++;
        shader.loadTransformationMatrix(Maths::createTransformationMatrix(glm::vec3(0.0, 0.0, 0.0), glm::vec3(rotation, 0.0, rotation), glm::vec3(1.5)));
        renderer.render(texturedModel);
        shader.stop();
        //glUseProgram(shaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();


    }
    loader.cleanUP();
    shader.cleanUp();
    //glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}