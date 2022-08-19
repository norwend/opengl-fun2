#pragma once

#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <stdexcept>
#include <string>


class Window {
    int  width_, height_;
    std::string title_;
    GLFWwindow* win_ = nullptr;
    static void framebuffer_size_callback(GLFWwindow* win [[maybe_unused]], int width, int height);

public:
    Window(int w, int h, std::string t);

    GLFWwindow* get_win_ptr() const { return win_; }

    void close() {
	glfwSetWindowShouldClose(win_, true);
    }
    
    inline void mouse_callback(GLFWcursorposfun func) {
	glfwSetCursorPosCallback(win_, func);
    }
    inline void scroll_callback(GLFWscrollfun func) {
	glfwSetScrollCallback(win_, func);
    }
    inline bool should_close() const {
	return glfwWindowShouldClose(win_);
    }
    inline bool is_key_pressed(int key) const {
	return glfwGetKey(win_, key);
    }
};

