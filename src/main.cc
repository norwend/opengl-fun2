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

    	std::vector<float> vertices {
    	    // positions          // normals           // texture coords
    	    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    	    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    	    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    	    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    	    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    	    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    	    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    	    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    	    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    	    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    	    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    	    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    	    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    	    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    	    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    	    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    	    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    	    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    	    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    	    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    	    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    	    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    	    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    	    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    	    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    	    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    	    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    	    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    	    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    	    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    	    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    	    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    	    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    	    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    	    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    	    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    	};
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

    	unsigned int VBO, cubeVAO;
    	glGenVertexArrays(1, &cubeVAO);
    	glGenBuffers(1, &VBO);

    	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
    		     vertices.data(), GL_STATIC_DRAW);

    	glBindVertexArray(cubeVAO);

    	// position attribute
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
    			      (void*)0);
    	glEnableVertexAttribArray(0);

    	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
    			      (void*)(3*sizeof(float)));
    	glEnableVertexAttribArray(1);

    	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
    			      (void*)(6*sizeof(float)));
    	glEnableVertexAttribArray(2);

    	// second, configure the light's VAO (VBO stays the same; the vertices
    	// are the same for the light object which is also a 3D cube)
    	unsigned int lightCubeVAO;
    	glGenVertexArrays(1, &lightCubeVAO);
    	glBindVertexArray(lightCubeVAO);

    	// we only need to bind to the VBO (to link it with glVertexAttribPointer),
    	// no need to fill it; the VBO's data already contains all we need
    	// (it's already bound, but we do it again for educational purposes)
    	glBindBuffer(GL_ARRAY_BUFFER, VBO);

    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
    			      nullptr);
    	glEnableVertexAttribArray(0);

    	glm::mat4 projection(1.0), view(1.0), model(1.0);
    	projection = glm::perspective((double)glm::radians(cam.get_zoom()),
    				      16.0/9.0, 0.01, 100.0);
    	view = cam.get_view();
    	projection = glm::perspective((double)glm::radians(cam.get_zoom()),
    				      16.0/9.0, 0.01, 100.0);
    	model = glm::mat4(1.0f);
    	win.scroll_callback(scroll_callback);
    	win.mouse_callback(mouse_callback);


    	Shader object_lighting_shader = { "../../shaders/colors.vert",
    					 "../../shaders/colors.frag" };
    	Shader light_cube_shader = { "../../shaders/light.vert",
    				     "../../shaders/light.frag" };
    	float last_frame = glfwGetTime();
    	float delta_time = 0;

    	Texture steel_box_diff_map("../../textures/steel_box_diff.png",
    				   GL_TEXTURE0);
    	Texture steel_box_spec_map("../../textures/steel_box_spec.png",
    				   GL_TEXTURE1);

    	glm::vec3 lightColor = {1.0f, 1.0f, 1.0f};
    	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
    	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    	std::vector<glm::vec3> pointLightPositions = {
    	    glm::vec3( 0.7f,  0.2f,   2.0f),
    	    glm::vec3( 2.3f, -3.3f,  -4.0f),
    	    glm::vec3(-4.0f,  2.0f, -12.0f),
    	    glm::vec3( 0.0f,  0.0f,  -3.0f)
    	};

    	while (!win.should_close()) {

    	    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	    process_input(win, delta_time);


    	    // ставим переменные объекта шейдеру
    	    object_lighting_shader.use();
    	    object_lighting_shader.set_int("material.diffuse", 0);
    	    object_lighting_shader.set_int("material.specular", 1);
    	    object_lighting_shader.set_float("material.shininess", 64.0f);

    	    // используем текстуры
    	    steel_box_diff_map.use();
    	    steel_box_spec_map.use();

    	    // ставим переменные света шейдеру

    	    // матрицы для взгляда в наш бренный мир
    	    projection = glm::perspective((double)glm::radians(cam.get_zoom()),
    					  16.0/9.0, 0.01, 100.0);
    	    view = cam.get_view();
    	    model = glm::mat4(1.0f);
    	    object_lighting_shader.set_mat4("projection", projection);
    	    object_lighting_shader.set_mat4("view", view);
    	    object_lighting_shader.set_mat4("model", model);

    	    // ПИЗДЕЦ!
    	    object_lighting_shader.set_vec3("viewPos", cam.get_pos());
    	    object_lighting_shader.set_vec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    	    object_lighting_shader.set_vec3("dirLight.diffuse", diffuseColor);
    	    object_lighting_shader.set_vec3("dirLight.ambient", ambientColor);
    	    object_lighting_shader.set_vec3("dirLight.specular", lightColor);

    	    object_lighting_shader.set_vec3("pointLights[0].position", pointLightPositions[0]);
    	    object_lighting_shader.set_float("pointLights[0].constant", 1.0);
    	    object_lighting_shader.set_float("pointLights[0].linear", 0.22);
    	    object_lighting_shader.set_float("pointLights[0].quadratic", 0.2);
    	    object_lighting_shader.set_vec3("pointLights[0].diffuse", diffuseColor);
    	    object_lighting_shader.set_vec3("pointLights[0].ambient", ambientColor);
    	    object_lighting_shader.set_vec3("pointLights[0].specular", lightColor);

    	    object_lighting_shader.set_vec3("pointLights[1].position", pointLightPositions[1]);
    	    object_lighting_shader.set_float("pointLights[1].constant", 1.0);
    	    object_lighting_shader.set_float("pointLights[1].linear", 0.22);
    	    object_lighting_shader.set_float("pointLights[1].quadratic", 0.2);
    	    object_lighting_shader.set_vec3("pointLights[1].diffuse", diffuseColor);
    	    object_lighting_shader.set_vec3("pointLights[1].ambient", ambientColor);
    	    object_lighting_shader.set_vec3("pointLights[1].specular", lightColor);

    	    object_lighting_shader.set_vec3("pointLights[2].position", pointLightPositions[2]);
    	    object_lighting_shader.set_float("pointLights[2].constant", 1.0);
    	    object_lighting_shader.set_float("pointLights[2].linear", 0.22);
    	    object_lighting_shader.set_float("pointLights[2].quadratic", 0.2);
    	    object_lighting_shader.set_vec3("pointLights[2].diffuse", diffuseColor);
    	    object_lighting_shader.set_vec3("pointLights[2].ambient", ambientColor);
    	    object_lighting_shader.set_vec3("pointLights[2].specular", lightColor);

    	    object_lighting_shader.set_vec3("pointLights[3].position", pointLightPositions[3]);
    	    object_lighting_shader.set_float("pointLights[3].constant", 1.0);
    	    object_lighting_shader.set_float("pointLights[3].linear", 0.22);
    	    object_lighting_shader.set_float("pointLights[3].quadratic", 0.2);
    	    object_lighting_shader.set_vec3("pointLights[3].diffuse", diffuseColor);
    	    object_lighting_shader.set_vec3("pointLights[3].ambient", ambientColor);
    	    object_lighting_shader.set_vec3("pointLights[3].specular", lightColor);

    	    // Рисуем ящики
    	    glBindVertexArray(cubeVAO);
    	    glDrawArrays(GL_TRIANGLES, 0, 36);
    	    for(unsigned int i = 0; i < 10; i++) {
    		    glm::mat4 model = glm::mat4(1.0f);
    		    model = glm::translate(model, cube_positions[i]);
    		    float angle = 20.0f * i;
    		    model = glm::rotate(model, glm::radians(angle),
    				    glm::vec3(1.0f, 0.3f, 0.5f));
    	        object_lighting_shader.set_mat4("model", model);
    		    glDrawArrays(GL_TRIANGLES, 0, 36);
    	    }


    	    // рисуем КУБЫ СВЕТА
    	    light_cube_shader.use();
    	    light_cube_shader.set_mat4("projection", projection);
    	    light_cube_shader.set_mat4("view", view);

            for (auto pos : pointLightPositions) {
    	    	model = glm::mat4(1.0f);
    	    	model = glm::translate(model, pos);
    	    	model = glm::scale(model, glm::vec3(0.2f)); // меньший куб

    	    	light_cube_shader.set_mat4("model", model);
    	    	light_cube_shader.set_vec3("lightColor", lightColor);

    	    	glBindVertexArray(lightCubeVAO);
    	    	glDrawArrays(GL_TRIANGLES, 0, 36);
    	    }



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
