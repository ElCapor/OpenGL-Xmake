#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "utils/FilesystemUtils.hpp"

#include <string>

class Shader
{
public:
    Shader(const char* vs_content, const char* fs_content)
    {
        // error handling
        GLint success;
        GLchar infoLog[1024];

        // vx and fs shaders
        unsigned int vs,fs;
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vs_content, NULL);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << " Vertex " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        fs = glCreateShader(GL_FRAGMENT_INTERPOLATION_OFFSET_BITS);
        glShaderSource(fs, 1, &fs_content, NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << " Program " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        id = glCreateProgram();
        glAttachShader(id, vs);
        glAttachShader(id, fs);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "id" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void use()
    {
        glUseProgram(id);
    }
    
private:
    unsigned int id;
};

#endif /* SHADERS_HPP */
