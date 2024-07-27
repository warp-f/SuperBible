#include "sb7.h"
#include "shader.h"
#include<iostream>
using namespace std;

//重写sb7 startup
class my_application : public sb7::application
{
public:
	void startup() override
	{
		rendering_program = compile_shaders();
		glCreateVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	void shutdown() override
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1, &vertex_array_object);
	}
	
	void render(double currentTime) override
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		//渲染
		glUseProgram(rendering_program);

		//渲染直径变大
		glPointSize(40.f);

		//绘图
		glDrawArrays(GL_POINTS, 0, 1);

		/*
		glDrawArrays(GLenum mode,     想要渲染的图元 点—GL_POINTS 线—GL_LINES 三角形—GL_TRIANGLES 
		             GLint first,     
					 GLsizei count);  想要渲染的顶点个数
		*/
	}

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

int main() 
{
	my_application app;
	app.run(&app);
	return 0;
}