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

		//vertex positions
		static const GLfloat vertex_positions[] =
		{
			0.25f, -0.25f, 0.5f, 1.0f,
			-0.25f, -0.25f, 0.5f, 1.0f,
			0.25f, 0.25f, 0.5f, 1.0f
		};

		glCreateVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		//create and blind vertex buffer object
		glCreateBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);

		//enable vertex 
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0); // 0: vertex positions 1: vertex color
	}

	void shutdown() override
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteBuffers(1, &vertex_buffer);
		glDeleteProgram(rendering_program);
	}

	void render(double currentTime) override
	{
		const GLfloat color[] = { 0.0f, 0.2f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		//��Ⱦ
		glUseProgram(rendering_program);

		//��ͼ ������
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*
		glDrawArrays(GLenum mode,     ��Ҫ��Ⱦ��ͼԪ �㡪GL_POINTS �ߡ�GL_LINES �����Ρ�GL_TRIANGLES
					 GLint first,
					 GLsizei count);  ��Ҫ��Ⱦ�Ķ������
		*/
	}

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
	GLuint vertex_buffer;
};

int main()
{
	my_application app;
	app.run(&app);
	return 0;
}