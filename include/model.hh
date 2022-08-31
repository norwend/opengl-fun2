#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Model {

struct Vertex {
    glm::vec3 pos, normal;
    glm::vec2 tex_coords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
	 std::vector<Texture> textures);
    void draw();
private:
    unsigned int VAO, VBO, EBO;

    void setup_mesh();
};
    
}

