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
        glm::vec2 position;
        eInputState inputState;

        void inputPos(GLFWwindow* window, double xpos, double ypos);
        void inputButton(GLFWwindow* window, int button, int action, int mods)



}