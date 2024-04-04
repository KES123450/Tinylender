#include <vector>


class Canvas{
    public:
        // 자식들의 draw() bVisible 체크해서 호출
        void Rendering();

    private:
        vector<Widget> mChild;
    

};