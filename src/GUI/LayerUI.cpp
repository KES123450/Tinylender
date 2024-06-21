#include "LayerUI.h"

LayerUI::LayerUI(Layer* layer,float layerSizeX,float layerSizeY,glm::vec3 layerPos){
    mLayerUIShader = new Shader("Shader/UIVertexShader.glsl", "Shader/UIFragmentShader.glsl");
    mLayer=layer;

    mSizeX =layerSizeX;
    mSizeY = layerSizeY;
    mPos = layerPos;

    float halfX = mSizeX/2;
    float halfY = mSizeY/2;


    glm::vec3 vertex[4];
    vertex[0] = glm::vec3(mPos.x-halfX,mPos.y+halfY,0.0f);
    vertex[1] = glm::vec3(mPos.x-halfX,mPos.y-halfY,0.0f);
    vertex[2] = glm::vec3(mPos.x+halfX,mPos.y+halfY,0.0f);
    vertex[3] = glm::vec3(mPos.x+halfX,mPos.y-halfY,0.0f);

    glm::vec2 texCoord[4];
    texCoord[0] = glm::vec2(0.0f,1.0f);
    texCoord[1] = glm::vec2(0.0f,0.0f);
    texCoord[2] = glm::vec2(1.0f,1.0f);
    texCoord[3] = glm::vec2(1.0f,0.0f);

    for(int i=0;i<4;i++){
        mVertexArray[i*5+0] = vertex[i].x;
        mVertexArray[i*5+1] = vertex[i].y;
        mVertexArray[i*5+2] = vertex[i].z;
        mVertexArray[i*5+3] = texCoord[i].x;
        mVertexArray[i*5+4] = texCoord[i].y;

    }

    glGenBuffers(1,&mVBO);
    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(mVertexArray),mVertexArray,GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(mIndices),mIndices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);  
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,5*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1,&mTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,mTexture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    
    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(mTexPath,&mWidth,&mHeight,&mMinimaps,0);


    if(data){
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,mWidth,mHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        printf("%s","textureFail");
    }

    stbi_image_free(data);
    mLayerUIShader->use();
    glUniform1i(glGetUniformLocation(mLayerUIShader->ID, "ourTexture"), 0);
}
void LayerUI::SelectLayerUI(){
    bSelected=true;
}

void LayerUI::UnSelectLayerUI(){
    bSelected=false;
}


void LayerUI::Draw(){
    if(bSelected){
        
    }

    if(bDragged){

    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,mTexture);
    mLayerUIShader->use();
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

}


