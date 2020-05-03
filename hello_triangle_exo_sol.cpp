//#include <>

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    
}

const GLuint WIDTH = 800, HEIGHT = 600;

const GLchar* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\n\0";

const GLchar* fragmentShader1Source = 
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const GLchar* fragmentShader2Source = 
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "triangle lol", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint shaderProgramOrange = glCreateProgram();
    GLuint shaderProgramYellow = glCreateProgram();
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
    
    GLfloat firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // Left 
        -0.0f, -0.5f, 0.0f,  // Right
        -0.45f, 0.5f, 0.0f,  // Top 
    };
    GLfloat secondTriangle[] = {
         0.0f, -0.5f, 0.0f,  // Left
         0.9f, -0.5f, 0.0f,  // Right
         0.45f, 0.5f, 0.0f   // Top 
    };
    
    GLuint VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    
    glBindVertexArray(VAOs[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0); 
   
    glBindVertexArray(VAOs[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(0);
    glBindVertexArray(0); 
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAOs[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);    
    }
    
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    
    glfwTerminate();
    return 0;
}