#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>

#include <window.hh>
#include <shape2d.hh>
#include <shader.hh>


#define PROJECT_NAME "opengl-lightning"
#define W_WIDTH 1280
#define W_HEIGHT 720

int main(int argc [[maybe_unused]], char **argv [[maybe_unused]]) { 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    try {
	Window win(W_WIDTH, W_HEIGHT, "aboba");

	std::vector<float> verts = {
	    -0.5, -0.5, 1.0,
	    0.5, -0.5, 1.0,
	    0.0, 0.0, 1.0,
	};
	
	Triangle triangle(verts);
	Shader sh = {"../shaders/shader.vert", "../shaders/shader.frag"};
	
	while (!win.should_close()) {
	    glClearColor(0.15f, 0.2f, 0.15f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    /* Place the code here! */
	    sh.use();
	    triangle.draw();

	    glfwSwapBuffers(win.get_win_ptr());
	    glfwPollEvents();
	}

    } catch (const std::exception& e){
	fmt::print(stderr, fmt::fg(fmt::color::pale_violet_red), "{}\n", e.what());
    }
    return 0;
}

