#include "CollectionCanvas.h"
#include "../Collection.h"


CollectionCanvas::CollectionCanvas(){
    Collection* collection = Collection::GetInstance();
    glm::vec3 layerUIPos = glm::vec3(-0.8f,0.1f,0.0f);
    mRootLayerUI = new LayerUI(collection->GetRootLayer(),0.0f,0.0f,layerUIPos);
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
    glm::vec3 layerUIPos = glm::vec3(-1+mLayerSizeX/2,1-mLayerOffsetY+(-mLayerSizeY)*nodeCount+(-mLayerSizeY/2)+mScrollDiscanceY,0.0f);
    LayerUI* ui = new LayerUI(layer,mLayerSizeX,mLayerSizeY,layerUIPos);
    mRootLayerUI->children.push_back(ui);
}

void CollectionCanvas::OnPointerDown(float xpos, float ypos,float xdelta,float ydelta){
    float ndcX = (2*xpos/SCR_WIDTH)-1;
    float ndcY = 1-(2*ypos/SCR_HEIGHT);

    if(ndcX >=-1+mLayerSizeX || ndcY >= 1-mLayerOffsetY)
        return;

    mCount=0;
    int selectedLayerIndex = findLayer(ndcY-mScrollDiscanceY,mRootLayerUI);
    if(selectedLayerIndex==-1)
        return;
  
    if(mPrevSelectedLayerUI!=nullptr){
        mPrevSelectedLayerUI -> UnSelectLayerUI();
    }

    mCount=selectedLayerIndex;
    LayerUI* selectedLayerUI = findLayer(mRootLayerUI);
    selectedLayerUI -> SelectLayerUI();
    Collection::GetInstance() -> SelectLayer(selectedLayerUI->GetLayer());
    mPrevSelectedLayerUI = selectedLayerUI;
}

void CollectionCanvas::OnPointer(float xpos, float ypos,float xdelta,float ydelta){

}

void CollectionCanvas::OnPointerUp(float xpos, float ypos,float xdelta,float ydelta){

}

void CollectionCanvas::OnScroll(float xoffset, float yoffset){
    ScrollLayer(mRootLayerUI,xoffset,yoffset);
    mScrollDiscanceY+=yoffset*SCROLL_SPEED;

}

int CollectionCanvas::findLayer(float yPos,LayerUI* layer){
    mCount++;

    if(yPos<=(layer->GetPos().y+layer->GetSize().y/2)
    && yPos>=(layer->GetPos().y-layer->GetSize().y/2))
        return mCount;

    for(LayerUI* child : layer->children){
        int result = findLayer(yPos,child);
        if(result != -1){
            return result;
        }
    }

    return -1;
}

LayerUI* CollectionCanvas::findLayer(LayerUI* layerUI){
    mCount--;
    if(mCount==0){
        return layerUI;
    }
    
    for(LayerUI* child :layerUI->children){
        LayerUI* findLayerUI = findLayer(child);
        if(findLayerUI != nullptr)
            return findLayerUI;
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

void CollectionCanvas::ScrollLayer(LayerUI* layer, float xoffset, float yoffset,int depth,int count){
    layer->ScrollLayerUI(xoffset,yoffset);

    if(layer->children.size()==0)
        return;

    int c =0;
    for(LayerUI* child : mRootLayerUI->children){
        ScrollLayer(child,xoffset,yoffset,depth+1,c);
        c++;
    }
}
