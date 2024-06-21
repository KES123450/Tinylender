#include "Pen.h"


Pen::Pen(){
    mVertices.push_back({glm::vec3(0.0f),glm::vec3(0.0f),glm::vec2(0.0f),glm::vec3(0.0f)});
    glGenVertexArrays(1,&mVAO);
    glGenBuffers(1,&mVBO);
    glGenBuffers(1,&mEBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mVBO);
    glBufferData(GL_ARRAY_BUFFER,mVertices.size()*sizeof(Vertex),&mVertices[0],GL_DYNAMIC_DRAW);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,mIndice.size()*sizeof(unsigned int),&mIndice[0],GL_DYNAMIC_DRAW);
    

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);


    glGenVertexArrays(1,&mLineVAO);
    glGenBuffers(1,&mLineVBO);

    glBindVertexArray(mLineVAO);
    glBindBuffer(GL_ARRAY_BUFFER,mLineVBO);
    glBufferData(GL_ARRAY_BUFFER,9*sizeof(float),&mLineVertices[0],GL_DYNAMIC_DRAW);
    

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    glBindVertexArray(0);

}

void Pen::Handle(){
    bDraw=true;
    DrawMesh();
}


void Pen::HandleOut(){
    bDraw=false;
}

void Pen::DrawMesh(){

    if(mVertices.size()<2)
        return;

    if(mVertices.size()==2){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glBindVertexArray(mVAO);
        
        glDrawArrays(GL_LINES,0,2);
        glBindVertexArray(0);

    }
    else{
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glBindVertexArray(mVAO);
        glDrawArrays(GL_TRIANGLES,0,mVertices.size());
        glBindVertexArray(0);
    }

     glBindVertexArray(mLineVAO);
     glBindBuffer(GL_ARRAY_BUFFER,mLineVBO);
     glBufferSubData(GL_ARRAY_BUFFER,3*sizeof(float),3*sizeof(float),&mLineVertices[3]);
     glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
     
     glDrawArrays(GL_TRIANGLES,0,3);
}

void Pen::OnPointerDown(float xpos, float ypos,float xdelta,float ydelta){
    if(!bDraw)
        return;

    glm::vec3 point = screenToLocal(glm::vec2(xpos,ypos));
    Vertex vert = {point,glm::vec3(1.0f),glm::vec2(1.0f),glm::vec3(1.0f)};
   
    if(glm::length(point-mVertices[0].Position) <= 0.1f &&mVertices.size()>3){
        //mesh로 만들어서 collection에 추가
        std::vector<std::vector<unsigned int>> faces;
        std::vector<unsigned int> f;
        faces.push_back(f);

        for(int i=0;i<mVertices.size();i++){
            faces[0].push_back(i);
            faces[0].push_back(i);
            faces[0].push_back(i);
        }
        
        Mesh* mesh= new Mesh(mVertices,mIndice,std::vector<Texture>(0),faces,"Shader/vertexShader.glsl","Shader/fragmentShader.glsl");
        ShapeLayer* shape = new ShapeLayer(mesh);
        Collection::GetInstance()->AddLayer(shape);
        mVertices.clear();
        mVertices.push_back({glm::vec3(0.0f),glm::vec3(0.0f),glm::vec2(0.0f),glm::vec3(0.0f)});
        mIndice.clear();
        bFirst=true;
        return;
    }
    else{
        mLineVertices[0] = point.x;
        mLineVertices[1] = point.y;
        mLineVertices[2] = point.z;


        if(bFirst){
            mVertices[0] = vert;
            mLineVertices[6] = vert.Position.x;
            mLineVertices[7] = vert.Position.y;
            mLineVertices[8] = vert.Position.z;

             glBindBuffer(GL_ARRAY_BUFFER,mLineVBO);
             glBufferSubData(GL_ARRAY_BUFFER,6*sizeof(float),3*sizeof(float),&mLineVertices[6]);

        }
        else{
            if(mVertices.size()>=3){

            Vertex vert2 = mVertices[mVertices.size()-1];
            mVertices.push_back(mVertices[0]);
            mVertices.push_back(vert2);
            mVertices.push_back(vert);
            }
            else{
                mVertices.push_back(vert);
            }
            
        }
        
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER,mVBO);
        glBufferData(GL_ARRAY_BUFFER,mVertices.size()*sizeof(Vertex),&mVertices[0],GL_DYNAMIC_DRAW);

        //glBindVertexArray(mLineVAO);
        glBindBuffer(GL_ARRAY_BUFFER,mLineVBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,3*sizeof(float),&mLineVertices);


        if(mVertices.size()>=3){
            /*
            mIndice.push_back(0);
            mIndice.push_back(mVertices.size()-2);
            mIndice.push_back(mVertices.size()-1);

            for(int i=0;i<mIndice.size();i++){
                printf(" index %d :  %u  ", i,mIndice[i]);
            }
            printf("\n");

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,mIndice.size()*sizeof(unsigned int),&mIndice[0],GL_DYNAMIC_DRAW);
            */
        }
    }
    bFirst=false;
}

void Pen::OnMove(float xpos, float ypos,float xdelta,float ydelta){
    if(!bDraw)
        return;

    glm::vec3 point = screenToLocal(glm::vec2(xpos,ypos));

    mLineVertices[3] = point.x * PEN_SPEED;
    mLineVertices[4] = point.y * PEN_SPEED;
    mLineVertices[5] = point.z * PEN_SPEED;

//    glBindVertexArray(mLineVAO);
    // glBindBuffer(GL_ARRAY_BUFFER,mLineVBO);
    // glBufferSubData(GL_ARRAY_BUFFER,3*sizeof(float),3*sizeof(float),&mLineVertices);


}

glm::vec3 Pen::screenToLocal(glm::vec2 screen){  //[TODO] 나중에 static으로 유틸함수로 빼버리기


    glm::vec4 ndcCoord;
    ndcCoord.x = (2.0f * screen.x) / SCR_WIDTH - 1.0f;
    ndcCoord.y = 1.0f - (2.0f *screen.y) / SCR_HEIGHT;
    ndcCoord.z = 0.0f-1.0f;
    ndcCoord.w = 1.0f;
/*
    // NDC 좌표를 클립 공간 좌표로 변환
    glm::vec4 clipCoord = glm::inverse(projection) * ndcCoord;

    // 클립 공간 좌표를 월드 좌표로 변환
    glm::vec4 worldCoord = glm::inverse(view * glm::mat4(1.0f)) * clipCoord;

    if(worldCoord.w !=0.0f){
        worldCoord /= worldCoord.w;
    }
    

    return glm::vec3(worldCoord.x,worldCoord.y,0.0f);*/

    return  glm::vec3(ndcCoord.x,ndcCoord.y,0.0f);

}
