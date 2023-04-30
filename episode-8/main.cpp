

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
#include "Entity.h"

#include "Display.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

Camera camera; 

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
    GLFWwindow* window = glfwCreateWindow(Display::SCR_WIDTH, Display::SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    Renderer renderer(shader);


  float vertices[] = {          
                -0.5f,0.5f,-0.5f,   
                -0.5f,-0.5f,-0.5f,  
                0.5f,-0.5f,-0.5f,   
                0.5f,0.5f,-0.5f,        
                
                -0.5f,0.5f,0.5f,    
                -0.5f,-0.5f,0.5f,   
                0.5f,-0.5f,0.5f,    
                0.5f,0.5f,0.5f,
                
                0.5f,0.5f,-0.5f,    
                0.5f,-0.5f,-0.5f,   
                0.5f,-0.5f,0.5f,    
                0.5f,0.5f,0.5f,
                
                -0.5f,0.5f,-0.5f,   
                -0.5f,-0.5f,-0.5f,  
                -0.5f,-0.5f,0.5f,   
                -0.5f,0.5f,0.5f,
                
                -0.5f,0.5f,0.5f,
                -0.5f,0.5f,-0.5f,
                0.5f,0.5f,-0.5f,
                0.5f,0.5f,0.5f,
                
                -0.5f,-0.5f,0.5f,
                -0.5f,-0.5f,-0.5f,
                0.5f,-0.5f,-0.5f,
                0.5f,-0.5f,0.5f
                
        };
        
        float textureCoords[] = {
                
                0,0,
                0,1,
                1,1,
                1,0,            
                0,0,
                0,1,
                1,1,
                1,0,            
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0

                
        };
        
        unsigned int indices[] = {
                0,1,3,  
                3,1,2,  
                4,5,7,
                7,5,6,
                8,9,11,
                11,9,10,
                12,13,15,
                15,13,14,   
                16,17,19,
                19,17,18,
                20,21,23,
                23,21,22

        };
    SizedArray<float> verticesArr(vertices, sizeof(vertices));
    SizedArray<unsigned int> indicesArr(indices, sizeof(indices));
    SizedArray<float> textureCoordsArr(textureCoords, sizeof(textureCoords));


    RawModel model = loader.loadToVAO(verticesArr, textureCoordsArr, indicesArr);
    ModelTexture texture(loader.loadTexture("resources/textures/image.png"));

    TexturedModel texturedModel(model, texture);

    Entity entity(texturedModel);
    entity.setColour(glm::vec3(0.75, 0.13, 0.56));
    entity.setPosition(glm::vec3(0.0, 0.0, -10.0));
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    std::cout << camera.getYaw() << std::endl;
    std::cout << camera.getPitch() << std::endl;
    std::cout << camera.getRoll() << std::endl;

    // render loop
    // -----------

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
        shader.loadViewMatrix(camera); 
        //shader.loadColour(glm::vec3(1.0, 0.0, 1.0));
        //entity.increasePosition(glm::vec3(0.0, 0.0, -0.05));
        renderer.render(entity, shader);
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

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.increasePosition(glm::vec3(0.0, 0.0, -0.1));

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.increasePosition(glm::vec3(0.0, 0.0, 0.1));

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.increasePosition(glm::vec3(0.1, 0.0, 0.0));

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.increasePosition(glm::vec3(-0.1, 0.0, 0.0));


    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
        camera.increaseRotation(glm::vec3(0.1, 0.0, 0.0));

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
        camera.increaseRotation(glm::vec3(-0.1, 0.0, 0.0));

    /*if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.increasePosition(glm::vec3(0.1, 0.0, 0.0));

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.increasePosition(glm::vec3(-0.1, 0.0, 0.0));*/
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}