#include "texture.hh"

void Texture::use() {
    glActiveTexture(texture_num_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}

Texture::Texture(const std::string& file_name, GLenum tex_num) : texture_num_(tex_num) {
    if (file_name.size() <= 4) throw std::runtime_error("No valid file specified!");
    if (std::string(file_name, file_name.size()-4, 4) != ".png") throw std::runtime_error("Only PNG is supported now");
    
    int width, height, nr_channels;
    unsigned char* tex_data = stbi_load(file_name.c_str(), &width, &height, &nr_channels, 0);
    
    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    if (tex_data) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nr_channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
	glGenerateMipmap(GL_TEXTURE_2D);
    }
    else 
	throw std::runtime_error("Failed to load texture!");
    
    stbi_image_free(tex_data);
}

Texture::Texture(const std::string& file_name) {
    Texture(file_name, GL_TEXTURE0);
}

int Texture::get_tex_num() {
    switch (texture_num_) {
    case GL_TEXTURE0:
	return 0;
	break;
    case GL_TEXTURE1:
	return 1;
	break;
    case GL_TEXTURE2:
	return 2;
	break;
    case GL_TEXTURE3:
	return 3;
	break;
    case GL_TEXTURE4:
	return 4;
	break;
    case GL_TEXTURE5:
	return 5;
	break;
    case GL_TEXTURE6:
	return 6;
	break;
    case GL_TEXTURE7:
	return 7;
	break;
    case GL_TEXTURE8:
	return 8;
	break;
    case GL_TEXTURE9:
	return 9;
	break;
    case GL_TEXTURE10:
	return 10;
	break;
    case GL_TEXTURE11:
	return 11;
	break;
    case GL_TEXTURE12:
	return 12;
	break;
    case GL_TEXTURE13:
	return 13;
	break;
    case GL_TEXTURE14:
	return 14;
	break;
    case GL_TEXTURE15:
	return 15;
	break;
    case GL_TEXTURE16:
	return 16;
	break;
    case GL_TEXTURE17:
	return 17;
	break;
    case GL_TEXTURE18:
	return 18;
	break;
    case GL_TEXTURE19:
	return 19;
	break;
    case GL_TEXTURE20:
	return 20;
	break;
    case GL_TEXTURE21:
	return 21;
	break;
    case GL_TEXTURE22:
	return 22;
	break;
    case GL_TEXTURE23:
	return 23;
	break;
    case GL_TEXTURE24:
	return 24;
	break;
    case GL_TEXTURE25:
	return 25;
	break;
    case GL_TEXTURE26:
	return 26;
	break;
    case GL_TEXTURE27:
	return 27;
	break;
    case GL_TEXTURE28:
	return 28;
	break;
    case GL_TEXTURE29:
	return 29;
	break;
    case GL_TEXTURE30:
	return 30;
	break;
    case GL_TEXTURE31:
	return 31;
	break;
    default:
	return -1;
	break;
    }
}
