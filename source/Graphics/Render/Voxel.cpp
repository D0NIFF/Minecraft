#include "Voxel.h"

#include <format>

#include "../../Engine/Voxel/Chunk.h"
#include "../../Engine/Voxel/VoxelStruct.h"
#include "../../Debug/Log.h"

/*
 * Defines the size of the vertex consisting of 3 coordinates (X, Y, Z), 2 texture coordinates (U, V) and 1 light value (L).
 */
#define VERTEX_SIZE (3 + 2 + 1)

/*
 * Checks if the coordinate is within the chunk size (width, height, depth).
 */
#define IS_IN(X,Y,Z) ((X) >= 0 && (X) < CHUNK_W && (Y) >= 0 && (Y) < CHUNK_H && (Z) >= 0 && (Z) < CHUNK_D)

/*
 *	Gets a voxel at the given coordinates, using a formula to access elements in a 3D array.
 */
#define VOXEL(X,Y,Z) (chunk->voxels[((Y) * CHUNK_D + (Z)) * CHUNK_W + (X)])

/*
 * Checks if a voxel exists at the given coordinates and if it has a non-zero identifier (i.e. if it is “locked”).
 */
#define IS_BLOCKED(X, Y, Z) ((IS_IN(X, Y, Z)) && VOXEL(X, Y, Z).id)

/*
 * A macro to add a vertex to the buffer and update the index. It simplifies adding vertices to the array.
 */
#define VERTEX(INDEX, X, Y, Z, U, V, L) buffer[INDEX + 0] = (X);\
buffer[INDEX + 1] = (Y);\
buffer[INDEX + 2] = (Z);\
buffer[INDEX + 3] = (U);\
buffer[INDEX + 4] = (V);\
buffer[INDEX + 5] = (L);\
INDEX += VERTEX_SIZE;

int chunkAttrs[] = {3,2,1, 0};

namespace Graphics::Render
{
	Voxel::Voxel(size_t capacity) : bufferCapacity(capacity) {
		buffer = new float[bufferCapacity * VERTEX_SIZE * 6];
		Debug::Log::alert("Voxel initialized");
	}

	Voxel::~Voxel(){
		delete[] buffer;
		Debug::Log::alert("Voxel deleted");
	}

	Graphics::Mesh* Voxel::render(const Engine::Voxel::Chunk* chunk) const
	{
		size_t vertexIndex  = 0;
		for (int y = 0; y < CHUNK_H; y++){
			for (int z = 0; z < CHUNK_D; z++){
				for (int x = 0; x < CHUNK_W; x++){
					VoxelStruct currentVoxel  = chunk->voxels[(y * CHUNK_D + z) * CHUNK_W + x];
					const unsigned int voxelId = currentVoxel.id;

					if (!voxelId){
						continue;
					}

					float lightValue;
					constexpr float textureAtlasTileSize = 1.0f / 16.0f;
					const float textureCoordU = static_cast<float>(voxelId % 16) * textureAtlasTileSize;
					//const float textureCoordV = (1 - (voxelId / 16) * textureAtlasTileSize);
					constexpr float textureCoordV = 1.0f;

					if (!IS_BLOCKED(x, y + 1, z)){
						lightValue = 1.0f;
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z - 0.5f, textureCoordU  + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z + 0.5f, textureCoordU  + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z + 0.5f, textureCoordU, textureCoordV  + textureAtlasTileSize, lightValue);

						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z - 0.5f, textureCoordU  + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z + 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z - 0.5f, textureCoordU, textureCoordV, lightValue);
					}
					if (!IS_BLOCKED(x, y - 1, z)){
						lightValue = 0.75f;
						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z - 0.5f, textureCoordU, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z + 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);

						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z - 0.5f, textureCoordU, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
					}

					if (!IS_BLOCKED(x + 1, y, z)){
						lightValue = 0.95f;
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z + 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);

						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z + 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z + 0.5f, textureCoordU, textureCoordV, lightValue);
					}
					if (!IS_BLOCKED(x - 1, y, z)){
						lightValue = 0.85f;
						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z - 0.5f, textureCoordU, textureCoordV, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z - 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);

						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z - 0.5f, textureCoordU, textureCoordV, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
					}

					if (!IS_BLOCKED(x, y, z + 1)){
						lightValue = 0.9f;
						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z + 0.5f, textureCoordU, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z + 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);

						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z + 0.5f, textureCoordU, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z + 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
					}
					if (!IS_BLOCKED(x, y, z - 1)){
						lightValue = 0.8f;
						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x - 0.5f, y + 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z - 0.5f, textureCoordU, + textureAtlasTileSize, lightValue);

						VERTEX(vertexIndex, x - 0.5f, y - 0.5f, z - 0.5f, textureCoordU + textureAtlasTileSize, textureCoordV, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y + 0.5f, z - 0.5f, textureCoordU, textureCoordV + textureAtlasTileSize, lightValue);
						VERTEX(vertexIndex, x + 0.5f, y - 0.5f, z - 0.5f, textureCoordU, textureCoordV, lightValue);
					}
				}
			}
		}
		if (vertexIndex / VERTEX_SIZE >= bufferCapacity * 6) {
			Debug::Log::error("Buffer overflow, increase capacity.");
		}
		Debug::Log::alert(std::format("Total vertices generated: {}", vertexIndex / VERTEX_SIZE));
		return new Mesh(buffer, vertexIndex / VERTEX_SIZE, chunkAttrs);
	}
}