
class Widget{
    public:
        virtual void inputButtonEvent(GLFWwindow* window, double xpos, double ypos);
        virtual void draw();

    private:
        bool bVisible;

};