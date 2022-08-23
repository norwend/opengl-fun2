#include "glm/gtc/type_ptr.hpp"
#include <shader.hh>

unsigned int Shader::compile_shader(unsigned int type, const std::string& contents) {
    unsigned int shader_id = glCreateShader(type);
    const char* src = contents.c_str();

    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);

    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
	int length;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
	char message[length];
	glGetShaderInfoLog(shader_id, length, &length, message);
	throw std::runtime_error(message);
    }
    return shader_id;
}
    
Shader::Shader(const std::string& vsh_file, const std::string& fsh_file) {
    id_ = glCreateProgram();
    unsigned int vsh_id, fsh_id;
    auto vsh_src = read_file(vsh_file);
    auto fsh_src = read_file(fsh_file);
    vsh_id = compile_shader(GL_VERTEX_SHADER, vsh_src);
    fsh_id = compile_shader(GL_FRAGMENT_SHADER, fsh_src);

    glAttachShader(id_, vsh_id);
    glAttachShader(id_, fsh_id);
    
    glLinkProgram(id_);
    glValidateProgram(id_);


    int result;
    glGetProgramiv(id_, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
	int length;
	glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &length);
	char message[length];
	glGetProgramInfoLog(id_, length, &length, message);
	throw std::runtime_error(message);
    }
    glDeleteShader(vsh_id);
    glDeleteShader(fsh_id);
}

void Shader::set_bool(const std::string& var, bool val) {
    glUniform1i(glGetUniformLocation(this->id_, var.c_str()), val);
}
void Shader::set_int(const std::string& var, int val) {
    glUniform1i(glGetUniformLocation(this->id_, var.c_str()), val);
}
void Shader::set_float(const std::string& var, float val) {
    glUniform1f(glGetUniformLocation(this->id_, var.c_str()), val);
}
void Shader::set_mat4(const std::string& var, const glm::mat4& val) {
    glUniformMatrix4fv(glGetUniformLocation(this->id_, var.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}
void Shader::set_vec3(const std::string& var, const glm::vec3& val) {
    glUniform3fv(glGetUniformLocation(this->id_, var.c_str()), 1, glm::value_ptr(val));
}
