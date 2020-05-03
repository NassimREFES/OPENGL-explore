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

int main()
{
    glfwInit();
    // si la version est inferieur y aura une error
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // si on utilise immediate mode function(old function) y aura une error
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // la fenetre né pas resizable
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    // l'actuel context utilisé (the main context) dans l'actuel thread
    glfwMakeContextCurrent(window);
    
    // set callback functions
    glfwSetKeyCallback(window, key_callback);
    
    glewExperimental = GL_TRUE; // le laissé a GL_FALSE peu avoir de problm avec les core profile function
    // initialisé glew pr s'assurer t'utilisé modern technique pr le management des fonctions
    // au lieu de pointé chaque fonction utilisé pr pouvoir lutilisé
    if (glewInit() != GLEW_OK) { 
        std::cout << "failed to initialize GLEW\n";
        return -1;
    }
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    // normalize device coordonnée range -1 to 1 
    // to window coordonnée
    
    // les deux premier represente le coin inferieur gauche, 
    // les deux dernier la largueur et longueur
    // point (-0.5, 0.5) represente (200, 450)
    glViewport(0, 0, width, height);
    
    while (!glfwWindowShouldClose(window)) { // fenetre fermé !! 
        glfwPollEvents(); // voir si les evenement quelquan est activé (input keyboard or mouse mouvement...)
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // clear screen with this color (state-setting function)
        glClear(GL_COLOR_BUFFER_BIT); // use previous color to clear framebuffer (state-using function)
        
        glfwSwapBuffers(window); // utilisé le double buffer et l'affiche sur le front buff
    }
    
    glfwTerminate(); // liberer les ressources
    return 0;
}