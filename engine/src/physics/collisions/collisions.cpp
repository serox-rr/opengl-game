module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <optional>
module engine;

namespace Engine::Physics {
    std::optional<glm::vec3> checkCollision(const Entity *entity,
                                            const std::vector<std::reference_wrapper<const Renderable>> &renderables,
                                            const glm::vec3 &position) {
        if (const auto terrain = dynamic_cast<const Terrain *>(&renderables[0].get())) {
            const auto &heightMap = terrain->getHeightMap();
            const auto width = terrain->getWidth();
            const auto height = terrain->getHeight();
            float floorX1 = floor(position.x);
            float floorZ1 = floor(position.z);
            const int xHeightMap = floorX1 + width / 2;
            const auto zHeightMap = floorZ1 + height / 2;
            if (xHeightMap+1 > width || zHeightMap+1 > height || xHeightMap-1 < 0 || zHeightMap < 0)
                return std::nullopt;
            const auto y1 = heightMap.at(zHeightMap * width + xHeightMap);
            const auto y2 = heightMap.at(zHeightMap * width + xHeightMap + 1);
            const auto y3 = heightMap.at((zHeightMap + 1) * width + xHeightMap);
            const auto y4 = heightMap.at((zHeightMap + 1) * width + xHeightMap + 1);
            points->setVertices(
                    {floorX1, static_cast<float>(heightMap.at(zHeightMap * width + xHeightMap) * 64.0 + 0.5),
                     floorZ1, floor(position.x + 1),
                     static_cast<float>(heightMap.at((zHeightMap + 1) * width + (xHeightMap + 1)) * 64.0 + 0.5),
                     floor(position.z + 1), floor(position.x + 1),
                     static_cast<float>(heightMap.at(zHeightMap * width + (xHeightMap + 1)) * 64.0 + 0.1),
                     floorZ1, floorX1,
                     static_cast<float>(heightMap.at((zHeightMap + 1) * width + xHeightMap) * 64.0 + 0.5),
                     floor(position.z + 1)});
            const auto y = (y1 + (y2 - y1) * (position.x - floorX1) +
                           (y3 - y1) * (position.z - floorZ1) +
                           (y1 + y4 - y2 - y3) * (position.x - floorX1) * (position.z - floorZ1))*64.0+1.0;
            if (y > position.y)
                return glm::vec3(position.x, y, position.z);
        }
        return std::nullopt;
    }
} // namespace Engine::Physics
