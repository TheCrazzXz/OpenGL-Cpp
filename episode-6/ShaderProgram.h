#pragma once

#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <sstream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	void setBool(const std::string& name, bool value) {
    	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	}

	void setInt(const std::string& name, int value) {
	    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
	}

	void setFloat(const std::string& name, float value) {
	    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	}

	void set3Float(const std::string& name, float v1, float v2, float v3) {
	    glUniform3f(glGetUniformLocation(programID, name.c_str()), v1, v2, v3);
	}

	void set3Float(const std::string& name, glm::vec3 v) {
	    glUniform3f(glGetUniformLocation(programID, name.c_str()), v.x, v.y, v.z);
	}

	void set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
	    glUniform4f(glGetUniformLocation(programID, name.c_str()), v1, v2, v3, v4);
	}

	void set4Float(const std::string& name, glm::vec4 v) {
	    glUniform4f(glGetUniformLocation(programID, name.c_str()), v.x, v.y, v.z, v.w);
	}

	void setMat3(const std::string& name, glm::mat3 val) {
	    glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
	}

	void setMat4(const std::string& name, glm::mat4 val) {
	    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
	}
};

#endif