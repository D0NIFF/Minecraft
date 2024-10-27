set(SOURCE_FILES main.cpp
        window/Window.cpp
        window/Window.h
        window/Event.cpp
        window/Event.h
        window/Camera.cpp
        window/Camera.h

        graphics/Shader.cpp
        graphics/Shader.h
        graphics/Texture.cpp
        graphics/Texture.h
        graphics/stb_image.h
        graphics/Mesh.cpp
        graphics/Mesh.h
        graphics/render/Voxel.cpp
        graphics/render/Voxel.h

        system/Loader.cpp
        system/Loader.h
        system/Log.cpp
        system/Log.h

        engine/voxel/Chunk.cpp
        engine/voxel/Chunk.h
        engine/voxel/VoxelStruct.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})