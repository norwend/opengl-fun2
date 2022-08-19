#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Shape2D {
protected:
    unsigned int VAO_, VBO_;
    unsigned int texture_;
public:
    Shape2D() = default;
    virtual void draw() = 0;
    virtual ~Shape2D() = default;
};

class Triangle : public Shape2D {
public:
    Triangle(std::vector<float> vertices);
    void draw() override;
    ~Triangle() override;
};
