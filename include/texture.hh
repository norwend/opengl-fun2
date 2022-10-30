#pragma once

#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <stb_image.h>


class Texture {
public:
    explicit Texture(const std::string& file_name) : Texture(file_name, GL_TEXTURE0) {}
    Texture(const std::string& file_name, GLenum tex_num);
    int get_tex_num();
    void use();
private:
    unsigned int id_;
    GLenum texture_num_ = GL_TEXTURE0;
};
