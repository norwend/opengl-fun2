#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fmt/core.h>
#include <fmt/color.h>

#define STB_IMAGE_IMPLEMENTATION

#include <window.hh>
#include <shader.hh>
#include <camera.hh>

#define PROJECT_NAME "opengl-fun2"
#define W_WIDTH 1280
#define W_HEIGHT 720

glm::vec3 camera_pos(0.0, 1.0, 3.0);
glm::vec3 camera_front(0.0, 0.0, 1.0);

Camera cam(W_WIDTH, W_HEIGHT, camera_pos, camera_front);

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

	std::vector<float> vertices {
	    -0.5f, -0.5f, -0.5f, 
	    0.5f, -0.5f, -0.5f,  
	    0.5f,  0.5f, -0.5f,  
	    0.5f,  0.5f, -0.5f,  
	    -0.5f,  0.5f, -0.5f, 
	    -0.5f, -0.5f, -0.5f, 
	    
	    -0.5f, -0.5f,  0.5f, 
	    0.5f, -0.5f,  0.5f,  
	    0.5f,  0.5f,  0.5f,  
	    0.5f,  0.5f,  0.5f,  
	    -0.5f,  0.5f,  0.5f, 
	    -0.5f, -0.5f,  0.5f, 
	    
	    -0.5f,  0.5f,  0.5f, 
	    -0.5f,  0.5f, -0.5f, 
	    -0.5f, -0.5f, -0.5f, 
	    -0.5f, -0.5f, -0.5f, 
	    -0.5f, -0.5f,  0.5f, 
	    -0.5f,  0.5f,  0.5f, 
	    
	    0.5f,  0.5f,  0.5f,  
	    0.5f,  0.5f, -0.5f,  
	    0.5f, -0.5f, -0.5f,  
	    0.5f, -0.5f, -0.5f,  
	    0.5f, -0.5f,  0.5f,  
	    0.5f,  0.5f,  0.5f,  
	    
	    -0.5f, -0.5f, -0.5f, 
	    0.5f, -0.5f, -0.5f,  
	    0.5f, -0.5f,  0.5f,  
	    0.5f, -0.5f,  0.5f,  
	    -0.5f, -0.5f,  0.5f, 
	    -0.5f, -0.5f, -0.5f, 
	    
	    -0.5f,  0.5f, -0.5f, 
	    0.5f,  0.5f, -0.5f,  
	    0.5f,  0.5f,  0.5f,  
	    0.5f,  0.5f,  0.5f,  
	    -0.5f,  0.5f,  0.5f, 
	    -0.5f,  0.5f, -0.5f, 
	};

	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(cubeVAO);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);
	
	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::mat4 projection(1.0), view(1.0), model(1.0);
	projection = glm::perspective((double)glm::radians(cam.get_zoom()), 16.0/9.0, 0.01, 100.0);
	view = cam.get_view();
	win.scroll_callback(scroll_callback);
	win.mouse_callback(mouse_callback);

	
	Shader lighting_shader = {"../shaders/colors.vert", "../shaders/colors.frag"};
	Shader light_cube_shader = {"../shaders/light.vert", "../shaders/light.frag"};

	float last_frame = glfwGetTime();
	float delta_time = 0;
	
	while (!win.should_close()) {
	    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

	    light_cube_shader.use();
	    light_cube_shader.set_vec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	    light_cube_shader.set_vec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	    projection = glm::perspective((double)glm::radians(cam.get_zoom()), 16.0/9.0, 0.01, 100.0);
	    view = cam.get_view();
	    model = glm::mat4(1.0f);
	    light_cube_shader.set_mat4("projection", projection);
	    light_cube_shader.set_mat4("view", view);
	    light_cube_shader.set_mat4("model", model);

	    glBindVertexArray(cubeVAO);
	    glDrawArrays(GL_TRIANGLES, 0, 36);


	    // also draw the lamp object
	    light_cube_shader.use();
	    light_cube_shader.set_mat4("projection", projection);
	    light_cube_shader.set_mat4("view", view);
	    model = glm::mat4(1.0f);
	    model = glm::translate(model, lightPos);
	    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	    light_cube_shader.set_mat4("model", model);
	    
	    glBindVertexArray(lightCubeVAO);
	    glDrawArrays(GL_TRIANGLES, 0, 36);

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
