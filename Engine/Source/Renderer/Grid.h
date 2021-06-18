#pragma once

#include "Vertex.h"
#include "pch.h"

using namespace fr;

namespace fr {
    class GLGrid {
    public:
        GLGrid() = default;
        ~GLGrid() = default;
        GLGrid(const GLGrid&) = default;

        GLGrid(unsigned int size) {
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec4> indices;

            for (int j = 0; j <= size; ++j) {
                for (int i = 0; i <= size; ++i) {
                    float x = (float)i / size;
                    float y = 0;
                    float z = (float)j / size;
                    vertices.push_back(glm::vec3(x, y, z));
                }
            }

            for (int j = 0; j < size; ++j) {
                for (int i = 0; i < size; ++i) {

                    int row1 = j * (size + 1);
                    int row2 = (j + 1) * (size + 1);

                    indices.push_back(glm::vec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
                    indices.push_back(glm::vec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));
                }
            }

            glGenVertexArrays(1, &_BufferArray);
            glBindVertexArray(_BufferArray);

            unsigned int vbo;
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

            unsigned int ibo;
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::vec4), indices.data(), GL_STATIC_DRAW);

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            _IndiceCount = (unsigned int)indices.size() * sizeof(unsigned int);

            vertices.clear();
            indices.clear();
        }

        void Render() {
            glBindVertexArray(_BufferArray);
            glDrawElements(GL_LINES, _IndiceCount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    private:
        unsigned int _BufferArray = 0;
        unsigned int _IndiceCount = 0;
    };
}