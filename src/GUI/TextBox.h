

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "Widget.h"
#include "../Shader/Shader.h"
#include "../IPressedDown.h"
#include "../IKeyDown.h"
#include "../constants.h"
#include "../Utils.h"
#include "../Character.h"
#include "../Fucking.h"

#pragma once

class TextBox : public Widget,public IPressedDown,public IKeyDown{
    public:
        TextBox(glm::vec3 textBoxPos,float sizeX, float sizeY,std::string text, float textSize,glm::vec3 textColor, bool stringFlag);
        void OnPointerDown(float xpos, float ypos,float xdelta,float ydelta) override;
        void GeyKeyDown(std::string str) override;
        void SetText(std::string str);
        void SetEventCallback(std::function<void(std::string)> func);
        std::string GetText() const {return mStr;}
        void Draw() override;

        
    private:
        bool bString; //입력이 string인지 number인지
        bool bTextActive=true;
        unsigned int mVAO, mVBO, mEBO;
        float mVertexArray[20];
        unsigned int mIndices[6]={
        0,1,2,
        2,1,3
        };
        unsigned int mTextVAO, mTextVBO;
        Shader* UIShader= new Shader("Shader/UIVertexShader.glsl", "Shader/FragShader.glsl");
        Shader* mTextShader = new Shader("Shader/fontVertex.glsl", "Shader/fontFrag.glsl");
        float mTextSize=1.0f;
        std::string mStr;
        glm::vec3 mTextColor;
      
        FT_Library mFreeType;
        std::string mFont = "resource/font/LINESeedSans_A_Th.ttf";
        FT_Face mFace;
        std::map<GLchar, Character> mCharacters;
        std::function<void(std::string str)> mEventCallback=NULL;

        void renderText(Shader* shader, std::string text, float scale, glm::vec3 color);
};