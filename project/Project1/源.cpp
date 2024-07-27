#include<iostream>
#include"sb7.h"

using namespace std;

class my_application : public sb7::application
{
public:
	//重载render方法，将屏幕变成红色
	void render(double currentTime) override
	{
		//R,G,B,透明度
		//static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };

		

		//f：浮点 v：向量 清除第一个参数指定的缓存（GL_COLOR）
		/*
		void glClearBufferfv(GLenum buffer, GLint drawBuffer, const GLfloat *value);
		清除第一个参数BUFFER
		第二个参数在多个输入缓存清除下使用，从0开始索引
		*/
		//glClearBufferfv(GL_COLOR, 0, red);

		//随时间变色
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime)*0.5f + 0.5f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
	}

	//重载init方法，设置窗口标题，窗口尺寸，opengl版本，
	void init() override
	{
		strcpy_s(info.title, "my opengl application");
		info.windowWidth = 800;
		info.windowHeight = 600;

		//版本号4.3
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


