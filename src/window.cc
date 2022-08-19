#include <window.hh>

void Window::framebuffer_size_callback(GLFWwindow* win [[maybe_unused]], int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window(int w, int h, std::string t): width_(w), height_(h), title_(t) {
    win_ = glfwCreateWindow(width_, height_, title_.c_str(), 0, 0);
    if (win_ == nullptr) throw std::runtime_error("Failed to create GLFW window.\n");

    glfwMakeContextCurrent(this->win_);

    auto load_gl_loader = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!load_gl_loader) throw std::runtime_error("Failed to initialize GLAD.");
    
    glViewport(0, 0, width_, height_);
    glfwSetFramebufferSizeCallback(win_, framebuffer_size_callback);
    glfwSetInputMode(this->win_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
}

