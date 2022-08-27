#include "glm/trigonometric.hpp"
#include <_types/_uint32_t.h>
#include <iostream>
#include <sys/signal.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>

#define STB_IMAGE_IMPLEMENTATION

#include <window.hh>
#include <shader.hh>
#include <camera.hh>
#include <texture.hh>

#define PROJECT_NAME "opengl-fun2"
#define W_WIDTH 1280
#define W_HEIGHT 720

glm::vec3 camera_pos(0.0, 1.0, 3.0);
glm::vec3 camera_front(0.0, 0.0, 1.0);

Camera cam(W_WIDTH, W_HEIGHT, camera_pos, camera_front);


void process_input(const Window& win, const float& delta_time);
void scroll_callback(GLFWwindow*, double, double);
void mouse_callback(GLFWwindow*, double, double);

int main(int argc [[maybe_unused]], char **argv [[maybe_unused]]) { 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    try {
	Window win(W_WIDTH, W_HEIGHT, "Main Window");

	glm::mat4 projection(1.0), view(1.0), model(1.0);
	projection = glm::perspective((double)glm::radians(cam.get_zoom()),
				      16.0/9.0, 0.01, 100.0);
	view = cam.get_view();
	projection = glm::perspective((double)glm::radians(cam.get_zoom()),
				      16.0/9.0, 0.01, 100.0);
	model = glm::mat4(1.0f);
	win.scroll_callback(scroll_callback);
	win.mouse_callback(mouse_callback);

	float last_frame = glfwGetTime();
	float delta_time = 0;

	glm::vec3 lightColor = {1.0f, 1.0f, 1.0f};
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	while (!win.should_close()) {

	    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    process_input(win, delta_time);

	    // матрицы для взгляда в наш бренный мир
	    projection = glm::perspective((double)glm::radians(cam.get_zoom()),
					  16.0/9.0, 0.01, 100.0);
	    view = cam.get_view();
	    model = glm::mat4(1.0f);


	    glfwSwapBuffers(win.get_win_ptr());
	    glfwPollEvents();

	    float currfr = glfwGetTime();
	    delta_time = currfr - last_frame;
	    last_frame = currfr;
	}

    } catch (const std::exception& e){
	fmt::print(stderr, fmt::fg(fmt::color::pale_violet_red),
		   "{}\n", e.what());
    }
    return 0;
}

void process_input(const Window& win, const float& delta_time) {
    if (win.is_key_pressed(GLFW_KEY_W)) {
	cam.move(CameraMovement::FORWARD, delta_time);
    }
    if (win.is_key_pressed(GLFW_KEY_S)) {
	cam.move(CameraMovement::BACKWARD, delta_time);
    }
    if (win.is_key_pressed(GLFW_KEY_A)) {
	cam.move(CameraMovement::LEFT, delta_time);
    }
    if (win.is_key_pressed(GLFW_KEY_D)) {
	cam.move(CameraMovement::RIGHT, delta_time);
    }
    if (win.is_key_pressed(GLFW_KEY_LEFT_SHIFT)) {
	cam.move(CameraMovement::DOWN, delta_time);
    }
    if (win.is_key_pressed(GLFW_KEY_SPACE)) {
	cam.move(CameraMovement::UP, delta_time);
    }
    if (win.is_key_pressed(GLFW_KEY_B)) {
	glfwSetInputMode(win.get_win_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if (win.is_key_pressed(GLFW_KEY_ESCAPE)) {
	glfwSetInputMode(win.get_win_ptr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    if (win.is_key_pressed(GLFW_KEY_Q)) {
	win.close();
    }
}

void scroll_callback(GLFWwindow* win [[maybe_unused]],
		     double xoffset, double yoffset) {
    cam.scroll_callback(xoffset, yoffset);
}
void mouse_callback(GLFWwindow* win [[maybe_unused]],
		    double xpos, double ypos) {
    cam.mouse_callback(xpos, ypos);
}
