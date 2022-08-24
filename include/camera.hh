#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

enum CameraMovement { FORWARD, BACKWARD, UP, DOWN, LEFT, RIGHT };

class Camera {
    glm::vec3 position_;
    glm::vec3 start_pos_;
    glm::vec3 front_;
    glm::vec3 up_;

    float lastX, lastY;

    float yaw_ = -90.0f;
    float pitch_ = 0.0f;
    float zoom_ = 45.0f;
    constexpr static float SENSITIVITY = 0.15f;
    constexpr static float camera_speed = 5.0f;
    bool firstMouse = true;

  public:
    Camera(uint32_t scr_width, uint32_t src_height, glm::vec3 pos,
           glm::vec3 front);

    glm::mat4 get_view() {
        return glm::lookAt(position_, position_ + front_, up_);
    }

    float get_zoom() const { return zoom_; }

    void mouse_callback(double xpos, double ypos);

    void scroll_callback(double xoffset [[maybe_unused]], double yoffset);

    void move(CameraMovement dir, float delta_time);

    glm::vec3 get_pos() { return position_; }
};
