#pragma once
#pragma clang diagnostic ignored "-Wvla-extension"

#include <stdexcept>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/matrix.hpp>
#include <iostream>

#include <file_utils.hh>


class Shader {
private:
    unsigned int id_;
    unsigned int compile_shader(unsigned int type, const std::string& contents);
    
public:
    Shader(const std::string& vsh_file, const std::string& fsh_file);
    unsigned int get_id() { return id_; }
    void set_bool(const std::string& var, bool val);
    void set_int(const std::string& var, int val);
    void set_float(const std::string& var, float val);
    void set_mat4(const std::string& var, const glm::mat4& val);
    void use() { glUseProgram(id_); }
};
