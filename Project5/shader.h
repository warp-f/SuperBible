#pragma once
#include"sb7.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

string ReadFile(const char* filename) 
{
	ifstream file(filename);
	if (!file.is_open()) 
	{
		cerr << "failed to open file : " << filename << endl;
		return "";
	}

	string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	return content;
}

GLint compile_shaders(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint tess_control_shader;
	GLuint tess_evaluation_shader;
	GLuint program;

	//readfile shader_v and shader_f 
	string vertexShaderSourceFile = ReadFile("shader_v.txt");
	string fragmentShaderSourceFile = ReadFile("shader_f.txt");

	const GLchar * vertex_shader_source[] = { vertexShaderSourceFile.c_str() };
	const GLchar * fragment_shader_source[] = { fragmentShaderSourceFile.c_str() };

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
