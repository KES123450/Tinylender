#include "Shader/Shader.h"
#include "GUI/button.h"
#include "GUI/Canvas.h"
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include "constants.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
glm::vec2 coordinatelocalToScreen(float x,float y, float z);
void rotateView(float xoffset, float yoffset);
bool searchVertex();
void modifyVertex();


const float CAMERA_ROTATE_SPEED = 15.0f;
float lastX =0.0f,lastY=0.0f;
float x=0.0f,y=0.0f;
int selectX=0, selectY=1, selectZ=2;
bool bLastLeftBtn=false;
bool bLastRightBtn =false;
bool bfirstRotate=true;

glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 cameraFront = glm::vec3(0.4f,0.4f,-1.3f);
glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);
float yaw, pitch;

glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection=glm::mat4(1.0f);;

unsigned int newVAO;
unsigned int newVBO;

float cube2[] ={
        -0.5f,-0.5f,0.5f, 0.2f,0.9f,0.3f,
        0.5f,-0.5f,0.5f, 0.7f,0.3f,0.1f,
        -0.5f,-0.5f,-0.5f, 0.4f,0.2f,0.7f,
        0.5f,-0.5f,-0.5f, 0.3f,0.6f,0.2f,
        -0.5f,0.5f,0.5f, 0.9f, 0.4f, 0.7f,
        0.5f,0.5f,0.5f, 0.3f, 0.6f,0.1f,
        -0.5f,0.5f,-0.5f, 0.2f, 0.6f,0.1f,
        0.5f,0.5f,0.5f, 0.7f, 0.3f,0.7f
};

const char *vertexShaderSource2 = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";
int main()
{
    
    // glfw 초기화
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // window 생성
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "gulender", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 현재 윈도우에 context를 설정
    glfwMakeContextCurrent(window);
    // buffer의 크기가 변경될 때 호출되는 콜백
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   //B glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);

    // glad 로드
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("Shader/vertexShader.glsl","Shader/fragmentShader.glsl");

    float vertices[] ={
        0.0f,0.3f,0.0f,
        0.4f,0.1f,0.0f,
        0.5f,0.8f,0.0f
    };

    float vertices2[] = {
        0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
        -0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
        0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
    };

    glm::vec3 cubePositions[] ={
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f) 
    };

    float vertices_cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    

    unsigned int indeices[] ={
        0,1,2,
        1,2,3,
        4,0,1,
        4,1,5,
        3,1,5,
        5,3,7,
        0,2,4,
        4,2,6,
        4,5,6,
        6,5,7,
        2,6,7,
        7,2,3

    };

    
    glGenVertexArrays(1,&newVAO);

    
    glGenBuffers(1,&newVBO);
    unsigned int EBO;
    glGenBuffers(1,&EBO);

    glBindVertexArray(newVAO);
    glBindBuffer(GL_ARRAY_BUFFER,newVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(cube2),cube2,GL_DYNAMIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indeices),indeices,GL_STATIC_DRAW);
    


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    projection = glm::perspective<float>(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);  

    
    Canvas* canvas = new Canvas();
    std::unique_ptr<Button> btn(new Button(glm::vec3(-0.3f,0.5f,0.0f),0.2f,0.2f,"resource/rose.jpg"));
    canvas->AddWidget(std::move(btn));

    // 메인 루프
    while (!glfwWindowShouldClose(window))
    {

        // 입력 처리
        processInput(window);
        
        // 버퍼 초기화
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        

        if(bLastLeftBtn==true){
            modifyVertex();
        }

        glm::mat4 model=glm::mat4(1.0f);;
        ourShader.use();
        unsigned int modelLoc =glGetUniformLocation(ourShader.ID,"model");
        unsigned int viewLoc =glGetUniformLocation(ourShader.ID,"view");
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
        ourShader.setMat4("projection",projection);
        glBindVertexArray(newVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  

        canvas->rendering();

        // 버퍼 출력
        glfwSwapBuffers(window);
        glfwPollEvents();
        

    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);

    delete(canvas);
    glfwTerminate();
    
    return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    float cameraSpeed = 0.05f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        cameraPos +=cameraSpeed *cameraFront;
    
    if(glfwGetKey(window,GLFW_KEY_S)==GLFW_PRESS)
        cameraPos -= cameraSpeed*cameraFront;

    if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp)) * cameraSpeed;

    if(glfwGetKey(window,GLFW_KEY_D) ==GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp))*cameraSpeed;
} 
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}          

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    
    float xoffset=xpos-lastX;
    float yoffset = lastY-ypos;
    lastX=xpos;
    lastY=ypos;

    float sensitivity =0.005f;
    xoffset *=sensitivity;
    yoffset *=sensitivity;

    x =static_cast<float>(xoffset);
    y = static_cast<float>(yoffset);

    if(bLastRightBtn)
        rotateView(xoffset,yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

    if(button == GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
        printf("%s","click");
        if(searchVertex())
            bLastLeftBtn=true;
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action==GLFW_RELEASE){
        bLastLeftBtn=false;
    }

    if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_PRESS){
        bLastRightBtn=true;
    }

    if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_RELEASE){
        bLastRightBtn=false;
    }
}


bool searchVertex(){
    for(int i=0; i<8;i++){
        glm::vec2 screenCube = coordinatelocalToScreen(cube2[6*i+0],cube2[6*i+1],cube2[6*i+2]);
        if(abs(screenCube.x- lastX)<=70 && abs(screenCube.y- (SCR_HEIGHT-lastY))<=70){
            selectX = 6*i+0;
            selectY = 6*i+1;
            selectZ = 6*i+2;
            return true;
        }
    }
    return false;
}

glm::vec2 coordinatelocalToScreen(float x,float y, float z){
    glm::vec4 local = glm::vec4(x,y,z,1.0f);
    glm::vec4 viewCoord = view*local;
    glm::vec4 clipCoord = projection * viewCoord;
    glm::vec3 ndc = glm::vec3(clipCoord)/clipCoord.w;
    glm::vec2 screen = glm::vec2((ndc.x+1)*(SCR_WIDTH/2),(ndc.y+1)*(SCR_HEIGHT/2));

    return screen;
}
void rotateView(float xoffset, float yoffset){

    if(bfirstRotate){
        yaw=xoffset*CAMERA_ROTATE_SPEED;
        pitch=yoffset*CAMERA_ROTATE_SPEED;
        bfirstRotate =false;
    }
    yaw += xoffset*CAMERA_ROTATE_SPEED;
    pitch += yoffset*CAMERA_ROTATE_SPEED;
    glm::vec3 front;
    if(pitch >89.0f){
        pitch =89.0f;
    }
    if(pitch<-89.0f){
        pitch =-89.0f;
    }
    front.x= cos(glm::radians(yaw)) *cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z= cos(glm::radians(pitch)) *sin(glm::radians(yaw));
    cameraFront = glm:: normalize(front);

}

void modifyVertex(){

    glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 right = glm::normalize(glm::cross(up,-cameraFront));

    float offset[3] ={cube2[selectX],cube2[selectY],cube2[selectZ]};
    offset[0] += x*right.x;
    offset[1] += y;
    offset[2] += x*right.z;
    glBindBuffer(GL_ARRAY_BUFFER,newVBO);
    glBufferSubData(GL_ARRAY_BUFFER,selectX*sizeof(float),sizeof(offset),offset);

    cube2[selectX]+= x*right.x;
    cube2[selectY]+= y;
    cube2[selectZ]+= x*right.z;

}

