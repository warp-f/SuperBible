#pragma once
#pragma once
#include"sb7.h"
#include<iostream>
using namespace std;

GLint compile_shaders(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	//vertex shader
	static const GLchar * vertex_shader_source[] =
	{
		"#version 450 core   \n"
		"layout(location = 0) in vec4 position;   \n"
		"void main(void)     \n"
		"{                   \n"
		"    gl_Position = position;                                                                                    \n"
		"}                   \n"
	};

	//fragment shader
	static const GLchar * fragment_shader_source[] =
	{
		"#version 450 core   \n"
		"out vec4 color      \n"
		"                    \n"
		"void main(void)     \n"
		"{                   \n"
		"    color = vec4{0.0, 0.0, 0.0, 1.0}; \n"
		"}                   \n"
	};

	//create and compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	/*
	glCreateShader 创建空的着色器对象
	glShaderSource 将着色器代码传递给着色器对象
	glCompileShader 编译
	*/


	//create and compile fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	//Create program, attach shaders to it, and link it
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	/*
	glCreateProgran 创建空的程序对象
	glAttachShader 将着色器对象附加到策划给你续对象
	glLinkProgram 将所有附加对象的着色器对象链接在一起
	*/

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	/*
	glDeleteShader 已经附加到程序对象中了 删除着色器对象
	*/

	return program;
};