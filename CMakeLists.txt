cmake_minimum_required(VERSION 3.29)    # Minimum CMake version required
project(Minecraft)                      # Project name
set(CMAKE_CXX_STANDARD 26)              # Set C++ standard to C++26

set(VCPKG_DIR "C:/vcpkg/installed/x64-windows")     # Set vcpkg local path

# Include directories
include_directories("${VCPKG_DIR}/include")

# Add project files
add_subdirectory(source)

install(                                        # To set the target and install path
        TARGETS ${PROJECT_NAME}                 # Add the prefix to path
        RUNTIME DESTINATION bin                 # bin - binary (path to binary files)
)


find_package(glfw3 CONFIG REQUIRED)     # Find and load GLFW
find_package(OpenGL REQUIRED)           # Find and load OpenGL
find_package(GLEW REQUIRED)             # Find and load GLEW
find_package(glm CONFIG REQUIRED)       # Find and load GLM
find_package(ZLIB REQUIRED)             # Find and load ZLIB
find_package(PNG REQUIRED)              # Find and load LIBPNG


# Properties
if(PRODUCTION_BUILD)
    # setup the RESOURCES_PATH macro to be in the root folder of your exe
    target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
    target_compile_definitions("${PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) # remove the option to debug asserts.
else()
    # This is useful to get an RESOURCES_PATH in your IDE during development
    target_compile_definitions("${PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions("${PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) # add the option to debug asserts.
endif()


# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${VCPKG_DIR}/lib/glew32.lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${VCPKG_DIR}/lib/zlib.lib)
else ()
    target_link_libraries(${PROJECT_NAME} PRIVATE glew)
    target_link_libraries(${PROJECT_NAME} PRIVATE zlib)
endif ()
target_link_libraries(${PROJECT_NAME} PRIVATE PNG::PNG)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
