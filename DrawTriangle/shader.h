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
	glCreateShader �����յ���ɫ������
	glShaderSource ����ɫ�����봫�ݸ���ɫ������
	glCompileShader ����
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
	glCreateProgran �����յĳ������
	glAttachShader ����ɫ�����󸽼ӵ��߻�����������
	glLinkProgram �����и��Ӷ������ɫ������������һ��
	*/

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	/*
	glDeleteShader �Ѿ����ӵ������������ ɾ����ɫ������
	*/

	return program;
};