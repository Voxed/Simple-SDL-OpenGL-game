#ifndef _MESH_H
#define _MESH_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>
#include <vector>
#include <GL/glew.h>
#include "Sprite.h"
#include "Shader.h"
#include "Texture.h" 
#include "RenderTarget.h"

class Mesh
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> texCoords;
public:
    /**
     * @brief Initialize an empty mesh object
     * 
     */
    Mesh();
    /**
     * @brief Load a mesh object from file
     * 
     * @param path Relative path to file
     */
    Mesh(const char* pathname);
    void render(Texture& texture, Shader& render_shader, glm::mat4 mvm, Color color = Color(1,1,1));
};

#endif