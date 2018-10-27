//
// Created by adria on 12/10/2018.
//

#ifndef SPACEINVADERS_GRAPHICSENGINE_HPP
#define SPACEINVADERS_GRAPHICSENGINE_HPP


#include <vector>
#include <memory>
#include "GraphicHolder.hpp"
#include "Shader.h"
#include "../Singleton.hpp"

class GraphicsEngine : public Singleton<GraphicsEngine>{
    struct InternalMesh {
        unsigned int VAO;
        unsigned int vbo;
        unsigned int ibo;
    };

    std::vector<std::shared_ptr<GraphicHolder>> graphics_;
    InternalMesh mesh_;
    std::shared_ptr<Shader> spriteShader_;
    glm::mat4 projMatrix_;
public:
    ~GraphicsEngine() override;
    void init(int width, int height);
    void draw();
    void registerGraphic(const std::shared_ptr<GraphicHolder> &graphic);

};


#endif //SPACEINVADERS_GRAPHICSENGINE_HPP
