#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

enum eInputState{
    Pressed,
    Released,
    PressedAndReleased,
    NotChanged
}


class InputEventSystem{
    public:
        glm::vec2 inputPosition;
        eInputState inputState;

        // 마우스 움질일 때마다 감지해서 inputPosition 변경
        void inputPos(GLFWwindow* window, double xpos, double ypos);
        //현재 있는 canvas에 접근하여 지금 인풋 위치 범위에 있는 UI의 callback함수 호출
        void inputButton(GLFWwindow* window, int button, int action, int mods)

        glm::vec2 getMousePos() const {return inputPosition;}

    private:
        vec<Ipushed>
        vec<IClicked>
}

InputEventSystem::inputPos(GLFWwindow* window, double xpos, double ypos){
    inputPosition.x = xpos;
    inputPosition.y= ypos;
}


