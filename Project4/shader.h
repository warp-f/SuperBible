#pragma once
#include"sb7.h"
#include<iostream>
using namespace std;

GLint compile_shaders(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint tess_control_shader;
	GLuint tess_evaluation_shader;
	GLuint program;

	//vertex shader
	static const GLchar * vertex_shader_source[] =
	{
		"#version 450 core\n"
		"layout(location = 0) in vec4 position;   \n"
		"void main(void)     \n"
		"{                   \n"
		"    gl_Position = position;   \n"
		"}                   \n"
	};

	//fragment shader
	static const GLchar * fragment_shader_source[] =
	{
		"#version 450 core\n"
		"out vec4 color;\n"
		"void main(void)\n"
		"{\n"
		"    color = vec4(0.0, 0.0, 0.0, 1.0);\n"
		"}\n"
	};

	//ϸ�����������ɫ��
	static const GLchar * tess_control_shader_source[] = 
	{
		"#version 450 core\n"
		"layout(vertices = 3) out;\n"
		"void main(void)\n"
		"{\n"
		"	if(gl_InvocationID == 0)\n"
		"	{\n"
		"		gl_TessLevelInner[0] = 3.0;\n"
		"		gl_TessLevelOuter[0] = 3.0;\n"
		"		gl_TessLevelOuter[1] = 4.0;\n"
		"		gl_TessLevelOuter[2] = 5.0;\n"
		"	}\n"
		"	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;\n"
		"}\n"
	};

	/*
	layout(vertices = 3) out;����Ķ�������Ϊ3��ÿ��ϸ��patch��3�����㣨�����Σ�
	if(gl_InvocationID == 0) ��ǰʵ����IDΪ0
	gl_TessLevelInner[0] �����ڲ�ϸ�ּ����ڲ�ϸ�ֵ�������ͷֲ�
	gl_TessLevelOuter[0],[1],[2] �����ⲿϸ�ּ��� =5ÿ���߶���ϸ��Ϊ5�� [0],[1],[2]�ֱ��ʾ�����ߵ�ϸ�ַּ�
	ϸ���ⲿ���� ��һ������ ϸ���ڲ�����
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; �����붥��λ�ô��ݵ��������λ��
	*/

	//ϸ������������ɫ��
	static const GLchar * tess_evaluation_shader_source[] =
	{
		"#version 450 core \n"
		"layout(triangles, equal_spacing, ccw) in;\n"
		"void main(void)\n"
		"{\n"
		"	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position + \n"
		"                  gl_TessCoord.y * gl_in[1].gl_Position + \n"
		"                  gl_TessCoord.z * gl_in[2].gl_Position); \n"
		"}\n"
	};

	/*
	layout(triangles, equal_spacing, cw) in; ָ������Ϊ�����Σ�ʹ�þ��ȼ��(equal_spacing),˳ʱ��˳��(cw)
	cw-Clockwise ������Ϊ����ʱ��ʹ��˳ʱ��  ccw-Counter Clockwise ��ʱ�� ������Ϊ���棨�޳������ִ�й��ռ���ʱʹ�ã�
	gl_TessCoord.x .y .zΪ���붥��gl_in[0].gl_Position�ϵ�Ȩ�أ������ģ������ߵĽ��㣩��������
	*/

	/*
	ϸ����ɫ����������ͼԪϸ�ֳɸ�С��ͼԪ����߼���ϸ��
	ϸ�ֿ�����ɫ��������ϸ�ּ���ϸ���ܶ�
	ϸ��������ɫ��������ϸ�ֺ��¶����λ��
	*/


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

	//create and compile tess control shader
	tess_control_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tess_control_shader, 1, tess_control_shader_source, NULL);
	glCompileShader(tess_control_shader);

	//create and compile tess evaluation shader
	tess_evaluation_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tess_evaluation_shader, 1, tess_evaluation_shader_source, NULL);
	glCompileShader(tess_evaluation_shader);

	//Create program, attach shaders to it, and link it
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);	
	glAttachShader(program, fragment_shader);
	glAttachShader(program, tess_control_shader);
	glAttachShader(program, tess_evaluation_shader);
	glLinkProgram(program);

	/*
	glCreateProgran �����յĳ������
	glAttachShader ����ɫ�����󸽼ӵ��߻�����������
	glLinkProgram �����и��Ӷ������ɫ������������һ��
	*/

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(tess_control_shader);
	glDeleteShader(tess_evaluation_shader);

	/*
	glDeleteShader �Ѿ����ӵ������������ ɾ����ɫ������
	*/

	return program;
}; 
