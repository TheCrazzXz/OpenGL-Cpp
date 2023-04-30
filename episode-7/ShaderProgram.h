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
		getAllUniformLocations();
	}

	int getUniformLocation(const char* uniformName)
	{
		return glGetUniformLocation(programID, uniformName);
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
	
	virtual void getAllUniformLocations() {};

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
	void setBool(const char* name, bool value) {
    	glUniform1i(getUniformLocation(name), (int)value);
	}

	void setInt(const char* name, int value) {
	    glUniform1i(getUniformLocation(name), value);
	}

	void setFloat(const char* name, float value) {
	    glUniform1f(getUniformLocation(name), value);
	}

	void setVec3(const char* name, float v1, float v2, float v3) {
	    glUniform3f(getUniformLocation(name), v1, v2, v3);
	}

	void setVec3(const char* name, glm::vec3 v) {
	    glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
	}

	void setVec4(const char* name, float v1, float v2, float v3, float v4) {
	    glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
	}

	void setVec4(const char* name, glm::vec4 v) {
	    glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void setMat3(const char* name, glm::mat3 val) {
	    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
	}

	void setMat4(const char* name, glm::mat4 val) {
	    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(val));
	}
};

#endif