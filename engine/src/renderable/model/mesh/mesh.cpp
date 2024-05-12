module;
#include <cstddef>
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
module engine;
namespace Engine {
     Mesh::Mesh(const std::vector<Vertex> &vertices_, const std::vector<unsigned int> &indices_, const std::vector<ModelTexture> &textures_, Shader &shader): Renderable(0,0,glm::vec3(0.0f), glm::vec3(0.0f), {}, shader), indices(indices_), textures(textures_), ebo(0), vertices(vertices_) {
         glGenVertexArrays(1, &vao);
         glGenBuffers(1, &vbo);
         glGenBuffers(1, &ebo);

         glBindVertexArray(vao);
         glBindBuffer(GL_ARRAY_BUFFER, vbo);

         glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                      &indices[0], GL_STATIC_DRAW);

         glEnableVertexAttribArray(0);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(0));
         glEnableVertexAttribArray(1);
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));
         glEnableVertexAttribArray(2);
         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));

         glBindVertexArray(0);
     }

    void Mesh::render() const {
         shader.use();
         unsigned int diffuseNr = 1;
         unsigned int specularNr = 1;
         for(unsigned int i = 0; i < textures.size(); i++)
         {
             glActiveTexture(GL_TEXTURE0 + i);
             std::string number;
             std::string name = textures[i].type;
             if(name == "texture_diffuse")
                 number = std::to_string(diffuseNr++);
             else if(name == "texture_specular")
                 number = std::to_string(specularNr++);
             auto uniformName = "material." + name + number;
             shader.addUniform(uniformName);
             shader.setInt(uniformName, i);
             glBindTexture(GL_TEXTURE_2D, textures[i].id);
         }
         glActiveTexture(GL_TEXTURE0);
         glBindVertexArray(vao);
         glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
         glBindVertexArray(0);
     }


} // namespace Engine
