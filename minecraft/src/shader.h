#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "reader.h"

class Shader {
private:
	unsigned int m_id;
	Reader m_reader;
	glm::mat4 model;
	//methods
	unsigned int createShader(GLenum type, const char* path)
	{
		m_reader.read(path);
		string srcString = m_reader.getContent();
		const char* src = srcString.c_str();
		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		return shader;
	}
	unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		unsigned int program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		int success;
		char infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return program;
	}
public:
	enum TransType {
		scale,
		translate,
		rotate
	};
	Shader(const char* vertexPath, const char* fragmentPath) : m_reader()
	{
		unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexPath);
		unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentPath);
		m_id = createProgram(vertexShader, fragmentShader);
		bind();
	}
	~Shader()
	{
		glDeleteProgram(m_id);
	}
	unsigned int getId() const
	{
		return m_id;
	}
	void bind() const
	{
		glUseProgram(m_id);
	}
	void unbind() const
	{
		glUseProgram(0);
	}
	
	void resetModelMatrix()
	{
		model = glm::mat4(1.0f);
		updateModelUniform();
	}

	void updateModelMatrix(TransType tType, glm::vec3 vector, float angle = 0)
	{
		switch (tType)
		{
		case scale:
			model = glm::scale(model, vector);
			break;
		case translate:
			model = glm::translate(model, vector);
			break;
		case rotate:
			model = glm::rotate(model, glm::radians(angle), vector);
			break;
		default:;
		}
		updateModelUniform();
	}

	void updateModelUniform()
	{
		setUniformMatrix("model", model);
	}
	
	//uniform methods
	void setUniformInt(const char* locationName, int i)
	{
		unsigned int location = glGetUniformLocation(m_id, locationName);
		glUniform1i(location, i);
	}

	void setUniformFloat(const char* locationName, float f)
	{
		unsigned int location = glGetUniformLocation(m_id, locationName);
		glUniform1f(location, f);
	}

	void setUniformMatrix(const char* locationName, glm::mat4 matrix)
	{
		unsigned int location = glGetUniformLocation(m_id, locationName);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void setUniformVec3(const char* locationName, glm::vec3 vector)
	{
		unsigned int location = glGetUniformLocation(m_id, locationName);
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void setUniformVec4(const char* locationName, glm::vec4 vector)
	{
		unsigned int location = glGetUniformLocation(m_id, locationName);
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}
};

#endif
