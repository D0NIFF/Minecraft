#ifndef _CHUNK_H
#define _CHUNK_H

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

#include "VoxelStruct.h"

namespace Engine::Voxel
{

  class Chunk {
  public:
    Chunk();
    ~Chunk();

    VoxelStruct* voxels;
  };

}

#endif // _CHUNK_H
