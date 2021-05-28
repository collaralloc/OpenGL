/*
*程序2-1
*一个完整的OpenGL程序
*/
#include"pch.h"
#include<iostream>
#include<gl/glut.h>

using namespace std;
void Initial(){
	glClearColor(1.0f,1.0f,1.0f,1.0f);	//RGBA设置窗口背景颜色为白色
	glMatrixMode(GL_PROJECTION);		//指定设置投影参数
	gluOrtho2D(0.0,200.0,0.0,150.0);	//设置投影参数
	/*虽然这里是绘制一个二维矩形，但是OpenGL处理图形的方式仍然是三维的。
	也就是说，二维矩形要在三维坐标空间中创建。
	*/
}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);	//用当前背景色填充窗口
	glColor3f(1.0f,0.0f,0.0);		//设置当前绘图颜色为红色
	glRectf(50.0f,100.0f,150.0f,50.0f);//绘制一个矩形
	glFlush();//清空OpenGL缓冲区，执行OpenGL程序
}
int main(int argc, char* argv[])
{
	glutInit(&argc,argv);		//对GLUT库进行初始化
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);	//设定窗口的显示模式，包括缓存和颜色模型等
	glutInitWindowSize(400,300);		//设置窗口大小400x300
	glutInitWindowPosition(100,120);	//设置窗口位置（Windows下右上角为(0,0)）
	glutCreateWindow("矩形");			//创建一个名为矩形的窗口
	glutDisplayFunc(Display);			//设置当前窗口的回调函数（即窗口显示的内容）
	Initial();					//完成窗口初始化
	glutMainLoop();			//启动主GLUT事件处理循环
	return 0;
}