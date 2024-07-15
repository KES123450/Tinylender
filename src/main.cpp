#define STB_IMAGE_IMPLEMENTATION
#include <map>
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
#include "Fucking.h"
#include "constants.h"
#include "InputEventSystem.h"
#include "Model.h"
#include "Context.h"
#include "ModifyVertex.h"
#include "Pen.h"
#include "GUI/TextBox.h"
#include "Extrude.h"
#include "GUI/CollectionCanvas.h"
#include "GUI/LayerUI.h"
#include "stb_image.h"
#include "Character.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void rotateView(float xoffset, float yoffset);
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

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

std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;

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
    glfwSetScrollCallback(window, mouse_scroll_callback);
    glfwSetKeyCallback(window,key_callback);

    // glad 로드
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

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

    
    Shader textShader("Shader/fontVertex.glsl", "Shader/fontFrag.glsl");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    textShader.use();
    glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

	// find path to font
    std::string font_name = "resource/font/LINESeedSans_A_Th.ttf";
    if (font_name.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return -1;
    }

   
	//------------------------
	// load font as face
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //------------------------
    CollectionCanvas* collectionCanvas = new CollectionCanvas();
    Collection::GetInstance() -> SetCollectionCanvas(collectionCanvas);
    Canvas* canvas = new Canvas();

    TextBox* t = new TextBox(glm::vec3(0.5f,0.2f,0.0f),0.6f,0.4f,"Fuck",true);
    eventSystem->AddKeyDown(t);
    eventSystem->AddPressedDown(t);
    canvas->AddWidget(t);

    Button* fileBtn = new Button(glm::vec3(-0.957418496340652f,0.9390243902439024f,0.0f)
    ,0.05056553559547571f,0.09268292682926829f,"resource/state/fileIcon.png",eImageType::PNG);
    auto fileBtnCallback =[&fileBtn](double xpos, double ypos){
        fileBtn->Pushed();

        if(fileBtn->GetPushed() == true){
            fileBtn->SetTexture("resource/state/fileIconPushed.png",eImageType::PNG);
            printf("%s","  layerBTN  ");

        }
        else{
            fileBtn->SetTexture("resource/state/fileIcon.png",eImageType::PNG);
        }
    };
    fileBtn->SetbuttonCallback(std::function<void(double, double)>(fileBtnCallback));
    canvas ->AddWidget(fileBtn);

    Button* dotBtn = new Button(glm::vec3(-0.8775781769793746f,0.9390243902439024f,0.0f)
    ,0.05056553559547571f,0.09268292682926829f,"resource/state/dotIcon.png",eImageType::PNG);
    auto dotBtnCallback =[&dotBtn,&context](double xpos, double ypos){
        dotBtn->Pushed();

        if(dotBtn->GetPushed() == true){
            dotBtn->SetTexture("resource/state/dotIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::DOT);
        }
        else{
            dotBtn->SetTexture("resource/state/dotIcon.png",eImageType::PNG);
            context->Transition(eUIState::EMPTY);
        }
    };
    dotBtn->SetbuttonCallback(std::function<void(double, double)>(dotBtnCallback));
    canvas ->AddWidget(dotBtn);

    Button* lineBtn = new Button(glm::vec3(-0.7964071856287425f,0.9390243902439024f,0.0f)
    ,0.05056553559547571f,0.09268292682926829f,"resource/state/lineIcon.png",eImageType::PNG);
    auto lineBtnCallback =[&lineBtn,&context](double xpos, double ypos){
        lineBtn->Pushed();

        if(lineBtn->GetPushed() == true){
            lineBtn->SetTexture("resource/state/lineIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::LINE);
            printf("%s","  lineBTN  ");

        }
        else{
            lineBtn->SetTexture("resource/state/lineIcon.png",eImageType::PNG);
            context->Transition(eUIState::EMPTY);
        }
    };
    lineBtn->SetbuttonCallback(std::function<void(double, double)>(lineBtnCallback));
    canvas ->AddWidget(lineBtn);

    Button* squareBtn = new Button(glm::vec3(-0.7165668662674651f,0.9390243902439024f,0.0f)
    ,0.05056553559547571f,0.09268292682926829f,"resource/state/extrudeIcon.png",eImageType::PNG);
    auto squareBtnCallback =[&squareBtn,&context](double xpos, double ypos){
        squareBtn->Pushed();

        if(squareBtn->GetPushed() == true){
            squareBtn->SetTexture("resource/state/extrudeIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::SURFACE);
            printf("%s","  squreBTN  ");

        }
        else{
            squareBtn->SetTexture("resource/state/extrudeIcon.png",eImageType::PNG);
            context->Transition(eUIState::EMPTY);
        }
    };
    squareBtn->SetbuttonCallback(std::function<void(double, double)>(squareBtnCallback));
    canvas ->AddWidget(squareBtn);

    Button* selectBtn = new Button(glm::vec3(-0.7165668662674651f,0.9390243902439024f,0.0f)
    ,0.05056553559547571f,0.09268292682926829f,"resource/state/selectIcon.png",eImageType::PNG);
    auto selectBtnCallback =[&selectBtn,&context](double xpos, double ypos){
        selectBtn->Pushed();

        if(selectBtn->GetPushed() == true){
            selectBtn->SetTexture("resource/state/selectIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::SURFACE);

        }
        else{
            selectBtn->SetTexture("resource/state/selectIcon.png",eImageType::PNG);
            context->Transition(eUIState::EMPTY);
        }
    };
    selectBtn->SetbuttonCallback(std::function<void(double, double)>(selectBtnCallback));
    canvas ->AddWidget(selectBtn);

    Button* textBtn = new Button(glm::vec3(-0.5555555555555556f,0.9390243902439024f,0.0f)
    ,0.05056553559547571f,0.09268292682926829f,"resource/state/textIcon.png",eImageType::PNG);
    auto textBtnCallback =[&textBtn,&context](double xpos, double ypos){
        textBtn->Pushed();

        if(textBtn->GetPushed() == true){
            textBtn->SetTexture("resource/state/textIconPushed.png",eImageType::PNG);
            context->Transition(eUIState::SURFACE);

        }
        else{
            textBtn->SetTexture("resource/state/textIcon.png",eImageType::PNG);
            context->Transition(eUIState::EMPTY);
        }
    };
    textBtn->SetbuttonCallback(std::function<void(double, double)>(textBtnCallback));
    canvas ->AddWidget(textBtn);


    Panel* statePanel = new Panel(glm::vec3(0.0f,0.9390243902439024f,0.0f),2.0f,0.12195121951219512f,"resource/StatePanel.jpg",eImageType::JPG);
    canvas->AddWidget(statePanel);

    Panel* layerPanel = new Panel(glm::vec3(-0.844311377245509f,-0.060975609756097615f,0.0f),0.31137724550898205f,1.8780487804878048f,"resource/LayerPanel.jpg",eImageType::JPG);
    canvas->AddWidget(layerPanel);

    eventSystem->AddPressedUp(canvas);
    eventSystem->AddPressedDown(collectionCanvas);
    eventSystem -> AddScrolled(collectionCanvas);


    // 메인 루프튵ㅌㅌㅌ
    while (!glfwWindowShouldClose(window))
    {

        // 입력 처리
        processInput(window);
        
        // 버퍼 초기화
        glClearColor(0.95294117647f, 0.95686274509f, 0.9294117647f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
      
        //RenderText(textShader, "Tinylender is vert very very tiny lender2343454565", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        glm::mat4 model=glm::mat4(1.0f);
        ourShader.use();
        unsigned int modelLoc =glGetUniformLocation(ourShader.ID,"model");
        unsigned int viewLoc =glGetUniformLocation(ourShader.ID,"view");
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,&view[0][0]);
        ourShader.setMat4("projection",projection);
        glUniform3f(glGetUniformLocation(ourShader.ID,"cameraPosition"),cameraPos.x,cameraPos.y,cameraPos.z);
        glStencilFunc(GL_ALWAYS, 1, 0x00);
        glStencilMask(0x00);
       // cube->Draw(ourShader);
        //backpack->Draw();
        context->HandleState();
        Collection* instance = Collection::GetInstance();
        Collection::GetInstance()->Rendering(instance->GetRootLayer());
        collectionCanvas->Rendering();
        canvas->Rendering();
       
        // 버퍼 출력
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);

    delete(fileBtn);
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(eventSystem){
        eventSystem->HandleKeyEvent(key,action);
    }
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

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if(eventSystem){
        eventSystem->HandleScrollEvent(xoffset,yoffset);
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


void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}