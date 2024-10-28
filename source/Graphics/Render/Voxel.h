#ifndef VOXEL_H
#define VOXEL_H

#include <iostream>

#include "../../Engine/Voxel/Chunk.h"
#include "../Mesh.h"



namespace Graphics::Render
{
    class Voxel {
    private:
        float* buffer;
        size_t bufferCapacity;

    public:
        Voxel(size_t capacity);
        ~Voxel();

        Graphics::Mesh* render(const Engine::Voxel::Chunk* chunk) const;
    };
}
// Render
// Graphics

#endif //VOXEL_H
