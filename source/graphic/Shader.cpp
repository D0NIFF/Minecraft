#pragma once
#include "Shader.h"

#include <exception>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "../system/Log.h"

namespace Graphic {
    Shader::Shader(unsigned int id) : id(id)
    {
    }

    Shader::~Shader()
    {
        glDeleteProgram(this->id);
    }

    void Shader::use() const
    {
        glUseProgram(this->id);
    }

    void Shader::uniformMatrix(const char* name, glm::mat4 matrix)
    {
        const GLuint transformation = glGetUniformLocation(this->id, name);
        glUniformMatrix4fv(transformation, 1, GL_FALSE, glm::value_ptr(matrix));
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
            System::Log::error("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
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
            System::Log::error("SHADER::VERTEX: compilation failed");
            System::Log::error(infoLog);
            return nullptr;
        }

        // Fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success){
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            System::Log::error("SHADER::FRAGMENT: compilation failed");
            System::Log::error(infoLog);
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
            System::Log::error("SHADER::PROGRAM: linking failed");
            System::Log::error(infoLog);

            glDeleteShader(vertex);
            glDeleteShader(fragment);
            return nullptr;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return new Shader(id);
    }
} // Graphic