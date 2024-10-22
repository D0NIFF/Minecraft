cmake_minimum_required(VERSION 3.29)   # Minimum CMake version required
project(Minecraft)                    # Project name
include(FetchContent)                 # Include FetchContent module for dependencies

set(CMAKE_CXX_STANDARD 26)            # Set C++ standard to C++26

# Paths to GLEW libraries and headers
set(GLEW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/external/glew/include)
set(GLEW_LIB_DIR ${CMAKE_SOURCE_DIR}/external/glew/lib/Release/x64)
set(GLEW_BIN_DIR ${CMAKE_SOURCE_DIR}/external/glew/bin/Release/x64)
set(GLEW_LIB ${GLEW_LIB_DIR}/glew32.lib)

# Load GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)

# Load GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e
)
FetchContent_MakeAvailable(glm)

# Find necessary libraries
find_package(OpenGL REQUIRED)
find_library(GLEW_LIB NAMES glew32s PATHS "${GLEW_LIB_DIR}" REQUIRED)

# Add project files
add_subdirectory(source)

# Properties
if(PRODUCTION_BUILD)
    # setup the DOMAINS_PATH macro to be in the root folder of your exe
    target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")

    # remove the option to debug asserts.
    target_compile_definitions("${PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    # This is useful to get an DOMAINS_PATH in your IDE during development
    target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")

    # add the option to debug asserts.
    target_compile_definitions("${PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()


# Include libraries
include_directories(${INCLUDE_DIR})
link_directories(${GLEW_LIB_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_LIB})
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
