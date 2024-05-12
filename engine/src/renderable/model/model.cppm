module;
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
export module engine:renderable.model;
import :renderable;
import :renderable.mesh;

export namespace Engine {
    class Model {
    public:
        Model(const std::string &path_, const glm::vec3 &position_, Shader &shader_);
        void render() const;
        void processNode(const aiNode *node, const aiScene *scene);
        Mesh processMesh(const aiMesh *mesh, const aiScene *scene);
        std::vector<ModelTexture> loadMaterialTextures(const aiMaterial *mat, aiTextureType type,
                                                       const std::string &typeName);

        [[nodiscard]] const glm::vec3 &getPosition() const;
        [[nodiscard]] const Shader &getShader() const;

    private:
        Shader &shader;
        const std::string &path;
        const std::string &directory;
        std::vector<Mesh> meshes;
        std::vector<ModelTexture> texturesLoaded;
        glm::vec3 position;
    };
} // namespace Engine
