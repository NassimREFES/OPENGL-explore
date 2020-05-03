#define GLEW_STATIC

//#include <>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

const GLuint WIDTH = 800, HEIGHT = 600;

const GLchar* vertexShaderSource = 
    "#version 330 core\n"

    "layout (location = 0) in vec3 position;\n"

    "void main()\n"
    "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
    
const GLchar* fragmentShaderSource1 = 
    "#version 330 core\n"
    
    "out vec4 color;\n"
    
    "void main()\n"
    "{\n"
        "color = vec4(1.0f, 0.84f, 0.0f, 1.0f);\n"
    "}\0";
    
const GLchar* fragmentShaderSource = 
    "#version 330 core\n"
    
    "out vec4 color;\n"
    
    "void main()\n"
    "{\n"
        "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "FIRST TRIANGLE", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //-----------------------------------------------------------
    
    // vertex shader
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    // lié shader object avec shader source code
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    
    glCompileShader(vertexShader);
    // verifier la compilation du shader 
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << '\n';
    }
    
    // fragment shader
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << '\n';
    }
    
    // fragment shader 1
    GLuint fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << '\n';
    }
    
    // link shaders
    
    // lié les 2 shaders object dans le shader program
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // si le lié c bien effectuer
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << '\n';
    }
    
    GLuint shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    // si le lié c bien effectuer
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING::FAILED\n" << infoLog << '\n';
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader1);
    
    // ----------------------------------------------------------------------
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        -0.2f, -0.2f, 0.0f, // gauche
        0.2f, -0.2f, 0.0f,  // droite
        0.0f, 0.5f, 0.0f,
        0.3f, -0.2f, 0.0f,
        0.7f, -0.2f, 0.0f,  
        0.5f, 0.5f, 0.0f 
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // bind vertex array object en premier
    glBindVertexArray(VAO);
    // puis bind et set vertex buffers et attribute pointer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);     
        
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        
        glBindVertexArray(VAO);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 3, sizeof(vertices));
        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
}