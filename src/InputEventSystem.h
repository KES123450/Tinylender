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

        void inputPosCallback(GLFWwindow* window, double xpos, double ypos);
        void inputButtonClaaback(GLFWwindow* window, int button, int action, int mods)



}