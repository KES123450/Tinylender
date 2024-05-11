#include "Mesh.h"
#include <vector>
#include "Shader/Shader.h"

#pragma once

class Collection{
    public:
        static Collection* GetInstance();
        Mesh* GetSelectedMesh() const {return mMeshes[mSelected];}

        void SetMesh(Mesh* mesh);
        void SelectMesh(int idx);
        void Rendering();

    private:
        static Collection* instance;
        std::vector<Mesh*> mMeshes;
        int mSelected;

};

Collection* Collection::instance = nullptr;

Collection* Collection::GetInstance(){
    if(instance==NULL)
        instance = new Collection();
    return instance;
}

void Collection::SelectMesh(int idx){
    if(idx <= mMeshes.size())
        mSelected=idx;
}

void Collection::SetMesh(Mesh* mesh){
    mMeshes.push_back(mesh);
}

void Collection::Rendering(){
    for(auto const& child : mMeshes){
       // printf("   %zu     ",mMeshes.size());
        child->Draw();
    }

    mMeshes[mSelected]->DrawSelected();
}