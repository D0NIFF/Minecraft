set(SOURCE_FILES main.cpp
        window/Window.cpp
        window/Window.h
        window/Event.cpp
        window/Event.h
        graphic/Shader.cpp
        graphic/Shader.h
        graphic/Texture.cpp
        graphic/Texture.h
        graphic/stb_image.h
        system/Loader.cpp
        system/Loader.h
        system/Log.cpp
        system/Log.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})