#pragma once

#include <stdexcept>
#include <string>

#include <glad/glad.h>
#include <stb_image.h>


class Texture {
public:
    Texture(const std::string& file_name);
    Texture(const std::string& file_name, GLenum tex_num);
    void use();
    int get_tex_num();
private:
    unsigned int texture_id_;
    GLenum texture_num_ = GL_TEXTURE0;
    unsigned int create(const std::string& file_name);
};
