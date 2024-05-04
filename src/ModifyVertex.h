#include "IPressed.h"
#include <glm/glm.hpp>

class ModifyVertex:public IPressed{
    public:
        void OnPointer(float xpos, float ypos) override;
};

ModifyVertex::OnPointer(float xpos, float ypos){
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