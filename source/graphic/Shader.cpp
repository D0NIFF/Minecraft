#include "Shader.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Graphic {
    Shader::Shader(unsigned int id) : ID(id)
    {
    }

    Shader::~Shader()
    {
        glDeleteProgram(this->ID);
    }

    void Shader::use()
    {
        glUseProgram(this->ID);
    }

    Shader* loadShader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
            return nullptr;
        }

        const GLchar* vShaderCode = vertexCode.c_str();
        const GLchar* fShaderCode = fragmentCode.c_str();

        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        // Vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
            std::cerr << infoLog << std::endl;
            return nullptr;
        }

        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
            std::cerr << infoLog << std::endl;
            return nullptr;
        }

        // Shader Program
        GLuint id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success){
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
            std::cerr << infoLog << std::endl;

            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return nullptr;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return new Shader(id);
    }
} // Graphic