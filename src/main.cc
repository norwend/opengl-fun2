#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>

#define STB_IMAGE_IMPLEMENTATION

#include <window.hh>
#include <shape.hh>
#include <shader.hh>
#include <texture.hh>
#include <camera.hh>

#define PROJECT_NAME "opengl-lightning"
#define W_WIDTH 1280
#define W_HEIGHT 720

glm::vec3 camera_pos(0.0, 1.0, 3.0);
glm::vec3 camera_front(0.0, 0.0, 1.0);

Camera cam(W_WIDTH, W_HEIGHT, camera_pos, camera_front);

void process_input(const Window& win); 
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

	std::vector<float> verts = {
	    -0.5, -0.5, 0.0, 0.0, 0.0,
	    0.5, -0.5, 0.0, 1.0, 0.0,
	    0.0, 0.5, 0.0, 0.5, 1.0,
	};

	glm::mat4 projection(1.0), view(1.0), model(1.0);
	model = glm::scale(model, glm::vec3(10.0, 15.0, 1.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
	projection = glm::perspective((double)glm::radians(cam.get_zoom()), 16.0/9.0, 0.01, 100.0);
	view = cam.get_view();
	win.scroll_callback(scroll_callback);
	win.mouse_callback(mouse_callback);

	std::vector<glm::vec3> cube_positions = {
	glm::vec3( 0.0f,  0.0f,   0.0f),
	glm::vec3( 2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f,  -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3( 2.4f, -0.4f,  -3.5f),
	glm::vec3(-1.7f,  3.0f,  -7.5f),
	glm::vec3( 1.3f, -2.0f,  -2.5f),
	glm::vec3( 1.5f,  2.0f,  -2.5f),
	glm::vec3( 1.5f,  0.2f,  -1.5f),
	glm::vec3(-1.3f,  1.0f,  -1.5f)
        };

	
	Shader sh = {"../shaders/shader.vert", "../shaders/shader.frag"};
	Texture box("../textures/box.png", GL_TEXTURE0);
	Cube t2(box);

	float last_frame = glfwGetTime();
	float delta_time = 0;
	sh.use();
	sh.set_int("texture0", box.get_tex_num());
	
	while (!win.should_close()) {
	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	    if (win.is_key_pressed(GLFW_KEY_B)) 
		glfwSetInputMode(win.get_win_ptr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	    if (win.is_key_pressed(GLFW_KEY_ESCAPE))
		glfwSetInputMode(win.get_win_ptr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	    if (win.is_key_pressed(GLFW_KEY_Q))
		win.close();

	    sh.use();
	    sh.set_mat4("model", model);
	    view = cam.get_view();
	    sh.set_mat4("view", view);
	    projection = glm::perspective((double)glm::radians(cam.get_zoom()), 16.0/9.0, 0.01, 100.0);
	    sh.set_mat4("projection", projection);
	    // triangle.draw();

	    for(unsigned int i = 0; i < 10; i++) {
		glm::mat4 model1 = glm::mat4(1.0f);
		model1 = glm::translate(model1, cube_positions[i]);
		float angle = 20.0f * i;
		if (i % 3 == 0) angle *= glfwGetTime();
		model1 = glm::rotate(model1, glm::radians(angle),
				     glm::vec3(1.0f, 0.3f, 0.5f));
		sh.set_mat4("model", model1);
		t2.draw();
	    }

	    glfwSwapBuffers(win.get_win_ptr());
	    glfwPollEvents();
	    float currfr = glfwGetTime();
	    delta_time = currfr - last_frame;
	    fmt::print("{}\n", 1/(currfr-last_frame));
	    last_frame = currfr;
	}

    } catch (const std::exception& e){
	fmt::print(stderr, fmt::fg(fmt::color::pale_violet_red), "{}\n", e.what());
    }
    return 0;
}

void process_input(const Window& win [[maybe_unused]]) {
}

void scroll_callback(GLFWwindow* win [[maybe_unused]], double xoffset, double yoffset) {
    cam.scroll_callback(xoffset, yoffset);
}
void mouse_callback(GLFWwindow* win [[maybe_unused]], double xpos, double ypos) {
    cam.mouse_callback(xpos, ypos);
}
