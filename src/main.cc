#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>

#define STB_IMAGE_IMPLEMENTATION

#include <window.hh>
#include <shape2d.hh>
#include <shader.hh>
#include <texture.hh>


#define PROJECT_NAME "opengl-lightning"
#define W_WIDTH 1280
#define W_HEIGHT 720

// Camera cam;

void process_input(const Window& win) {
    if (win.is_key_pressed(GLFW_KEY_W)) {

    }
}

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
	model = glm::scale(model, glm::vec3(5.0, 5.0, 1.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0, 0.0, 0.0));
	projection = glm::perspective(45.0, 16.0/9.0, 0.01, 100.0);
	view = glm::lookAt(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	
	Triangle triangle(verts);
	Shader sh = {"../shaders/shader.vert", "../shaders/shader.frag"};
	Texture box("../textures/box.png", GL_TEXTURE0);
	
	while (!win.should_close()) {
	    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    /* Place the code here! */
	    sh.use();
	    sh.set_mat4("model", model);
	    sh.set_mat4("view", view);
	    sh.set_mat4("projection", view);
	    box.use();
	    triangle.draw();

	    glfwSwapBuffers(win.get_win_ptr());
	    glfwPollEvents();
	}

    } catch (const std::exception& e){
	fmt::print(stderr, fmt::fg(fmt::color::pale_violet_red), "{}\n", e.what());
    }
    return 0;
}

