#include "Shader/Shader.h"
#include "GUI/button.h"
#include "GUI/Canvas.h"
#include "GUI/Panel.h"
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
#include "InputEventSystem.h"
#include "Model.h"
#include "Context.h"
#include "ModifyVertex.h"
#include "Pen.h"
#include "Extrude.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void rotateView(float xoffset, float yoffset);

InputEventSystem* eventSystem = new InputEventSystem();


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
glm::mat4 projection=glm::mat4(1.0f);

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("Shader/vertexShader.glsl","Shader/fragmentShader.glsl");

    
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective<float>(glm::radians(45.0f), SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

    Model *cube = new Model("resource/cube.obj","Shader/vertexShader.glsl","Shader/selectedFragShader.glsl");
    Model *backpack = new Model("resource/backpack/backpack.obj","Shader/vertexShader.glsl","Shader/selectedFragShader.glsl");

    ModifyVertex* layerState = new ModifyVertex();
    ModifyVertex* dotState = new ModifyVertex();
    Pen* lineState = new Pen();
    Extrude* surfaceState = new Extrude();

    eventSystem->AddPressed(dotState);
    eventSystem->AddPressedDown(dotState);
    eventSystem->AddPressedUp(dotState);

    eventSystem->AddPressedDown(lineState);
    eventSystem->AddMoved(lineState);

    eventSystem->AddPressed(surfaceState);
    eventSystem->AddPressedDown(surfaceState);
    eventSystem->AddPressedUp(surfaceState);

    Context* context = new Context(layerState,dotState,lineState,surfaceState);

    
    /*std::vector<Mesh>* meshes= backpack->GetMeshes();
    for(int i=0;i<meshes->size();i++){
         Mesh* m = &(*meshes)[i];
         Collection::GetInstance()->SetMesh(m);
    } */

    /*std::vector<Mesh>* meshes=cube->GetMeshes();
     for(int i=0;i<meshes->size();i++){
         Mesh* m = &(*meshes)[i];
         Collection::GetInstance()->SetMesh(m);
     } */
    
    Canvas* canvas = new Canvas();

    Button* layerBtn = new Button(glm::vec3(-0.8373015873015873f,0.8065173116089613f,0.0f)
    ,0.08994708994708994f,0.1384928716904277f,"resource/layerIcon.jpg",eImageType::JPG);
    auto layerBtnCallback =[&layerBtn](double xpos, double ypos){
        layerBtn->Pushed();

        if(layerBtn->GetPushed() == true){
            layerBtn->SetTexture("resource/layerIconPushed.png",eImageType::PNG);

        }
        else{
            layerBtn->SetTexture("resource/layerIcon.jpg",eImageType::JPG);
        }
    };
    layerBtn->SetbuttonCallback(std::function<void(double, double)>(layerBtnCallback));
    canvas ->AddWidget(layerBtn);

    Button* dotBtn = new Button(glm::vec3(-0.701058201058201f,0.8065173116089613f,0.0f)
    ,0.08994708994708994f,0.1384928716904277f,"resource/dotIcon.jpg",eImageType::JPG);
    auto dotBtnCallback =[&dotBtn,&context](double xpos, double ypos){
        dotBtn->Pushed();

        if(dotBtn->GetPushed() == true){
            dotBtn->SetTexture("resource/dotIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::DOT);
        }
        else{
            dotBtn->SetTexture("resource/dotIcon.jpg",eImageType::JPG);
            context->Transition(eUIState::EMPTY);
        }
    };
    dotBtn->SetbuttonCallback(std::function<void(double, double)>(dotBtnCallback));
    canvas ->AddWidget(dotBtn);

    Button* lineBtn = new Button(glm::vec3(-0.5886243386243386f,0.8065173116089613f,0.0f)
    ,0.08994708994708994f,0.1384928716904277f,"resource/LineIcon.jpg",eImageType::JPG);
    auto lineBtnCallback =[&lineBtn,&context](double xpos, double ypos){
        lineBtn->Pushed();

        if(lineBtn->GetPushed() == true){
            lineBtn->SetTexture("resource/LineIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::LINE);

        }
        else{
            lineBtn->SetTexture("resource/LineIcon.jpg",eImageType::JPG);
            context->Transition(eUIState::EMPTY);
        }
    };
    lineBtn->SetbuttonCallback(std::function<void(double, double)>(lineBtnCallback));
    canvas ->AddWidget(lineBtn);

    Button* squareBtn = new Button(glm::vec3(-0.4801587301587301f,0.8065173116089613f,0.0f)
    ,0.08994708994708994f,0.1384928716904277f,"resource/squareIcon.jpg",eImageType::JPG);
    auto squareBtnCallback =[&squareBtn,&context](double xpos, double ypos){
        squareBtn->Pushed();

        if(squareBtn->GetPushed() == true){
            squareBtn->SetTexture("resource/squareIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::SURFACE);

        }
        else{
            squareBtn->SetTexture("resource/squareIcon.jpg",eImageType::JPG);
            context->Transition(eUIState::EMPTY);
        }
    };
    squareBtn->SetbuttonCallback(std::function<void(double, double)>(squareBtnCallback));
    canvas ->AddWidget(squareBtn);

    Button* colorBtn = new Button(glm::vec3(-0.3234126984126984f,0.8044806517311609f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/ColorIcon.png",eImageType::PNG);
    auto colorBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),1.0f,1.0f,1.0f);
    };
    colorBtn->SetbuttonCallback(std::function<void(double, double)>(colorBtnCallback));
    canvas ->AddWidget(colorBtn);

    Button* purpleBtn = new Button(glm::vec3(-0.20965608465608465f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Purple.png",eImageType::PNG);
    auto purpleBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.7f,0.3f,0.7f);
    };
    purpleBtn->SetbuttonCallback(std::function<void(double, double)>(purpleBtnCallback));
    canvas ->AddWidget(purpleBtn);

    Button* pinkBtn = new Button(glm::vec3(-0.09589947089947093f,0.8044806517311609f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Pink.png",eImageType::PNG);
    auto pinkBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.6f,0.5f,0.5f);
    };
    pinkBtn->SetbuttonCallback(std::function<void(double, double)>(pinkBtnCallback));
    canvas ->AddWidget(pinkBtn);

    Button* redBtn = new Button(glm::vec3(0.017857142857142794f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Red.png",eImageType::PNG);
    auto redBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.8f,0.5f,0.5f);
    };
    redBtn->SetbuttonCallback(std::function<void(double, double)>(redBtnCallback));
    canvas ->AddWidget(redBtn);

    Button* orangeBtn = new Button(glm::vec3(0.13161375661375652f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Orange.png",eImageType::PNG);
    auto orangeBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.7f,0.7f,0.3f);
    };
    orangeBtn->SetbuttonCallback(std::function<void(double, double)>(orangeBtnCallback));
    canvas ->AddWidget(orangeBtn);

    Button* yellowBtn = new Button(glm::vec3(0.24537037037037046f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Yellow.png",eImageType::PNG);
    auto yellowBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.5f,0.7f,0.3f);
    };
    yellowBtn->SetbuttonCallback(std::function<void(double, double)>(yellowBtnCallback));
    canvas ->AddWidget(yellowBtn);

    Button* greenBtn = new Button(glm::vec3(0.3591269841269842f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Green.png",eImageType::PNG);
    auto greenBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.3f,0.7f,0.3f);
    };
    greenBtn->SetbuttonCallback(std::function<void(double, double)>(greenBtnCallback));
    canvas ->AddWidget(greenBtn);

    Button* skyBtn = new Button(glm::vec3(0.4728835978835979f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Sky.png",eImageType::PNG);
    auto skyBtnCallback =[&ourShader](double xpos, double ypos){
        ourShader.use();
        glUniform3f(glGetUniformLocation(ourShader.ID,"val"),0.3f,0.3f,0.7f);
    };
    skyBtn->SetbuttonCallback(std::function<void(double, double)>(skyBtnCallback));
    canvas ->AddWidget(skyBtn);

    Button* blueBtn = new Button(glm::vec3(0.5866402116402116f,0.8065173116089613f,0.0f)
    ,0.051587301587301584f,0.0814663951120163f,"resource/Blue.png",eImageType::PNG);
    canvas ->AddWidget(blueBtn);

    Panel* panel = new Panel(glm::vec3(0.014f,0.7708757637474541f,0.0f),1.8558201058201058f,0.24643584521384929f,"resource/Basic.png");
    canvas->AddWidget(panel);

    eventSystem->AddPressedUp(canvas);


    // 메인 루프튵ㅌㅌㅌ
    while (!glfwWindowShouldClose(window))
    {

        // 입력 처리
        processInput(window);
        
        // 버퍼 초기화
        glClearColor(0.95294117647f, 0.95686274509f, 0.9294117647f, 1.0f);
       //glClearColor(0.0f, 0.074509f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
      

        glm::mat4 model=glm::mat4(1.0f);
        ourShader.use();
        unsigned int modelLoc =glGetUniformLocation(ourShader.ID,"model");
        unsigned int viewLoc =glGetUniformLocation(ourShader.ID,"view");
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
        ourShader.setMat4("projection",projection);
        glUniform3f(glGetUniformLocation(ourShader.ID,"cameraPosition"),cameraPos.x,cameraPos.y,cameraPos.z);
       // glBindVertexArray(newVAO);
       // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);  

       // cube->Draw(ourShader);
        //backpack->Draw();
        context->HandleState();
        Collection::GetInstance()->Rendering(Collection::GetInstance()->GetRootLayer());
        canvas->Rendering();

        // 버퍼 출력
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);

    delete(layerBtn);
   // delete(panel);
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

    if(eventSystem){
        eventSystem->HandleInputPos(xpos,ypos);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){

    if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_PRESS){
        bLastRightBtn=true;
    }

    if(button==GLFW_MOUSE_BUTTON_RIGHT && action==GLFW_RELEASE){
        bLastRightBtn=false;
    }
    
    if(eventSystem){
        eventSystem->HandleInputEvent(button,action);
    }
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


