#include <shape2d.hh>

Triangle::Triangle(std::vector<float> vertices) {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    
    glBindVertexArray(VAO_);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::draw() {
    glBindVertexArray(this->VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::~Triangle() {
    glDeleteBuffers(1, &this->VBO_);
    glDeleteVertexArrays(1, &this->VAO_);
}
