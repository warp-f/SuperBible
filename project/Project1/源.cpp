#include<iostream>
#include"sb7.h"

using namespace std;

class my_application : public sb7::application
{
public:
	//����render����������Ļ��ɺ�ɫ
	void render(double currentTime) override
	{
		//R,G,B,͸����
		//static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

		

		//f������ v������ �����һ������ָ���Ļ��棨GL_COLOR��
		/*
		void glClearBufferfv(GLenum buffer, GLint drawBuffer, const GLfloat *value);
		�����һ������BUFFER
		�ڶ��������ڶ�����뻺�������ʹ�ã���0��ʼ����
		*/
		//glClearBufferfv(GL_COLOR, 0, red);

		//��ʱ���ɫ
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime)*0.5f + 0.5f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
	}

	//����init���������ô��ڱ��⣬���ڳߴ磬opengl�汾��
	void init() override
	{
		strcpy_s(info.title, "my opengl application");
		info.windowWidth = 800;
		info.windowHeight = 600;

		//�汾��4.3
		info.majorVersion = 4;
		info.minorVersion = 3;

	}
};

int main(int argc, char** argv)
{
	my_application app;
	app.run(&app);
	return 0;
}


