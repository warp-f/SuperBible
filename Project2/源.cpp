#include "sb7.h"
#include "shader.h"
#include<iostream>
using namespace std;

//��дsb7 startup
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

		//��Ⱦ
		glUseProgram(rendering_program);

		//��Ⱦֱ�����
		glPointSize(40.f);

		//��ͼ
		glDrawArrays(GL_POINTS, 0, 1);

		/*
		glDrawArrays(GLenum mode,     ��Ҫ��Ⱦ��ͼԪ �㡪GL_POINTS �ߡ�GL_LINES �����Ρ�GL_TRIANGLES 
		             GLint first,     
					 GLsizei count);  ��Ҫ��Ⱦ�Ķ������
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