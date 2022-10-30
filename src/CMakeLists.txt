add_executable(opengl-fun2 main.cc file_utils.cc glad.c shader.cc texture.cc window.cc camera.cc)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW 2.0 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp)
find_package(fmt 9.0)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(../include /opt/homebrew/include ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})
link_directories(/opt/homebrew/lib/)
target_link_libraries(opengl-fun2 ${OPENGL_LIBRARIES} glfw GLEW glm::glm assimp fmt)
