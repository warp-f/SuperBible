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

	//细分曲面控制着色器
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
	layout(vertices = 3) out;输出的顶点数量为3，每个细分patch有3个顶点（三角形）
	if(gl_InvocationID == 0) 当前实例的ID为0
	gl_TessLevelInner[0] 设置内部细分级别，内部细分点的数量和分布
	gl_TessLevelOuter[0],[1],[2] 设置外部细分级别 =5每条边都被细分为5段 [0],[1],[2]分别表示三条边的细分分级
	细分外部级别 不一定等于 细分内部级别
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; 将输入顶点位置传递到输出顶点位置
	*/

	//细分曲面评估着色器
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
	layout(triangles, equal_spacing, cw) in; 指定输入为三角形，使用均匀间隔(equal_spacing),顺时针顺序(cw)
	cw-Clockwise 三角形为正面时，使用顺时针  ccw-Counter Clockwise 逆时针 三角形为背面（剔除背面和执行光照计算时使用）
	gl_TessCoord.x .y .z为输入顶点gl_in[0].gl_Position上的权重，与重心（三中线的交点）坐标类似
	*/

	/*
	细分着色器：将几何图元细分成更小的图元，提高几何细节
	细分控制着色器：负责细分级别，细分密度
	细分评估着色器：计算细分后新顶点的位置
	*/


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
	glCreateProgran 创建空的程序对象
	glAttachShader 将着色器对象附加到策划给你续对象
	glLinkProgram 将所有附加对象的着色器对象链接在一起
	*/

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glDeleteShader(tess_control_shader);
	glDeleteShader(tess_evaluation_shader);

	/*
	glDeleteShader 已经附加到程序对象中了 删除着色器对象
	*/

	return program;
}; 
