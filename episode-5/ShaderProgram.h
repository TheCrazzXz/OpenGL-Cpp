#pragma once

#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <sstream>
#include <fstream>
#include <string>

#include <cstring>

std::string file_to_string(const std::string& file_name)
{
    std::ifstream file_stream{file_name};

    if (file_stream.fail())
    {
        std::cerr << "Error while opening file '"+file_name+"'" << std::endl;
        exit(-1);
    }

    std::ostringstream str_stream{};
    file_stream >> str_stream.rdbuf();  // NOT str_stream << file_stream.rdbuf()

    if (file_stream.fail() && !file_stream.eof())
    {
       std::cerr << "Error with file '"+file_name+"'" << std::endl;
       exit(-1);
    }

    return str_stream.str();
}
char *strdup(const char *src_str) noexcept {
    char *new_str = new char[std::strlen(src_str) + 1];
    std::strcpy(new_str, src_str);
    return new_str;
}


class ShaderProgram
{
private:
	int programID;
	int vertexShaderID;
	int fragmentShaderID;
public:

	ShaderProgram(std::string vertexFile, std::string fragmentFile){
		vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
		fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		bindAttributes();
		glLinkProgram(programID);
		glValidateProgram(programID);
	}
	
	void start(){
		glUseProgram(programID);
	}
	
	void stop(){
		glUseProgram(0);
	}
	
	void cleanUp(){
		stop();
		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		glDeleteProgram(programID);
	}
protected:
	virtual void bindAttributes() {};
	
	void bindAttribute(int attribute, std::string variableName){
		glBindAttribLocation(programID, attribute, variableName.c_str());
	}
public:
	static int loadShader(std::string fileName, int type)
	{
		const char* shaderSource = strdup(file_to_string(fileName).c_str());

		unsigned int shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);
		int success;
	    char infoLog[512];
	    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	    if (!success)
	    {
	        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
	        std::cerr << "Error at shader compilation\n" << infoLog << std::endl;
	        exit(-1);
	    }
	    return shaderID;
	}
};

#endif