#include "CollectionCanvas.h"
#include "../Collection.h"


CollectionCanvas::CollectionCanvas(){
    Collection* collection = Collection::GetInstance();
    glm::vec3 layerUIPos = glm::vec3(-0.7f,0.2f,0.0f);
    mRootLayerUI = new LayerUI(collection->GetRootLayer(),mLayerSizeX,mLayerSizeY,layerUIPos);
}

void CollectionCanvas::Rendering(LayerUI* layer, int depth,int count){
    layer->Draw();

    if(layer->children.size()==0)
        return;

    int c =0;
    for(LayerUI* child : mRootLayerUI->children){
        Rendering(child,depth+1,c);
        c++;
    }
}

void CollectionCanvas::AddLayerUI(Layer* layer){
    mCount=1;
    int nodeCount = countNodes(mRootLayerUI);
    glm::vec3 layerUIPos = glm::vec3(mLayerSizeX/2,-mLayerOffsetY+(-mLayerSizeY)*nodeCount+(-mLayerSizeY/2),0.0f);
    LayerUI* ui = new LayerUI(layer,mLayerSizeX,mLayerSizeY,layerUIPos);
    mRootLayerUI->children.push_back(ui);
}

void CollectionCanvas::OnPointerDown(float xpos, float ypos,float xdelta,float ydelta){
    float ndcX = (2*xpos/SCR_WIDTH)-1;
    float ndcY = 1-(2*ypos/SCR_HEIGHT);

    if(ndcX >=mLayerSizeX&& ndcY >= 1-mLayerOffsetY)
        return;
    
    int selectedLayerIndex = findLayer(ypos,mRootLayerUI);
    if(selectedLayerIndex==-1)
        return;
    
    prevSelectedLayerUI -> UnSelectLayerUI();
    LayerUI* selectedLayerUI = findLayer(selectedLayerIndex,mRootLayerUI);
    selectedLayerUI -> SelectLayerUI();
    Collection::GetInstance() -> SelectLayer(selectedLayerUI->GetLayer());
    prevSelectedLayerUI = selectedLayerUI;
}

void CollectionCanvas::OnPointer(float xpos, float ypos,float xdelta,float ydelta){

}

void CollectionCanvas::OnPointerUp(float xpos, float ypos,float xdelta,float ydelta){

}

int CollectionCanvas::findLayer(float yPos,LayerUI* layer,int count){
    //조건에 부합하는 레이어를 못찾은 경우
    if(layer->children.size()==0)
        return -1;

    if(yPos<=(layer->GetPos().y+layer->GetSize().y/2)
    && yPos>=(layer->GetPos().y-layer->GetSize().y/2))
        return count;


    for(LayerUI* child : layer->children){
        int result = findLayer(yPos,child,count+1);
        if(result != -1){
            return result;
        }
    }

    return -1;
}

LayerUI* CollectionCanvas::findLayer(int index, LayerUI* layerUI){
    if(layerUI->children.size()==0){
        return nullptr;
    }

    if(index==0){
        return layerUI;
    }
    
    for(LayerUI* child :layerUI->children){
        LayerUI* findLayerUI = findLayer(index-1,child);
        if(findLayerUI==nullptr){
            findLayerUI = findLayer(index-1,child);
        }
        else{
            return findLayerUI;
        }
    }
    return nullptr;
}


int CollectionCanvas::countNodes(LayerUI* layer){
    if(layer==nullptr)
        return 0;

    int count =1;
    for(LayerUI* child : layer->children){
        count += countNodes(child);
    }

    return count;
}
