module;
#include <iostream>
#include <ostream>
#include <vector>
#include <glad/glad.h>
#include <FastNoise/FastNoise.h>

module engine.renderable.terrain;

namespace Engine {
    Terrain::Terrain(): width(1000), height(1000), vao(0) {
        GLuint vbo, ebo;
        std::vector<float> points = {};
        const FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("IgD2KLxApHA9PwcA");
        std::vector<float> noiseOutput(width * height);
        fnGenerator->GenUniformGrid2D(noiseOutput.data(), 0, 0, width, height, 0.009f, 300);
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                points.push_back(i*1000);
                points.push_back(noiseOutput[i*height+j]*30000);
                points.push_back(j*1000);
            }
        }
        std::vector<unsigned> indices = {};
        for (unsigned int i = 0; i < height - 1; i++) // for each row a.k.a. each strip
        {
            for (unsigned int j = 0; j < width; j++) // for each column
            {
                for (unsigned int k = 0; k < 2; k++) // for each side of the strip
                {
                    indices.push_back(j + width * (i + k));
                }
            }
        }
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER,
                     points.size() * sizeof(float), // size of vertices buffer
                     &points[0], // pointer to first element
                     GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     indices.size() * sizeof(unsigned int), // size of indices buffer
                     &indices[0], // pointer to first element
                     GL_STATIC_DRAW);
    }

    void Terrain::render() {
        // draw mesh
        glBindVertexArray(vao);
        // render the mesh triangle strip by triangle strip - each row at a time
        for (unsigned int strip = 0; strip < width - 1; ++strip) {
            glDrawElements(GL_TRIANGLE_STRIP, // primitive type
                           height * 2, // number of indices to render
                           GL_UNSIGNED_INT, // index data type
                           (void *)(sizeof(unsigned int)
                                    * height * 2
                                    * strip)); // offset to starting index
        }
    }

    Terrain::~Terrain() = default;
}
