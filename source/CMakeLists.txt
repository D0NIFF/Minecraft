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
        Graphics/render/Voxel.cpp
        Graphics/render/Voxel.h

        System/ImageLoader.cpp
        System/ImageLoader.h
        Debug/Log.cpp
        Debug/Log.h

        Engine/voxel/Chunk.cpp
        Engine/voxel/Chunk.h
        Engine/voxel/VoxelStruct.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})