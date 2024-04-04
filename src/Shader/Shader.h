#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include<string>
#include <fstream>
#include<sstream>
#include<iostream>


class Shader{
public:
    unsigned int ID;

    Shader(const GLchar* vertexPath,const GLchar* fragmentPath){

        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions (std::ifstream::failbit |std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit |std::ifstream::badbit);

        try{

            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream<<vShaderFile.rdbuf();
            fShaderStream<<fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode=vShaderStream.str();
            fragmentCode=fShaderStream.str();

        }
        catch(std::ifstream::failure e){
            std::cout << "ERROR::FIRENOTREAD" << std::endl;

        }

        //std::string vShaderCodestr = std::string("#version 330 core\n") + vertexCode;
        const char* vShaderCode = vertexCode.c_str();

        //std::string fShaderCodestr = std::string("#version 330 core\n") + fragmentCode;
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex,fragment;
        int success;
        char infoLog[512];

        vertex =glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vShaderCode,NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        fragment=glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fShaderCode,NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
        };

        ID=glCreateProgram();
        glAttachShader(ID,vertex);
        glAttachShader(ID,fragment);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if(!success)
{
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }

    void use(){
        glUseProgram(ID);
    }
    //uniform 유틸리티 함수?
    void setBool(const std::string &name, bool value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string &name, bool value) const{
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setvalue(const std::string &name, bool value) const{
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const{
        glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1,GL_FALSE,&mat[0][0]);
    }
    

};

#endif