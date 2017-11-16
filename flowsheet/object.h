#pragma once
#include "stdafx.h"
#include <queue>
#include "analyze.h"
#include <fstream>

class arrowline;

class objectpoint
{
public:
	int x;
	int y;
	int radius;
	arrowline* al;
	int toward;		//0代表没有线，1代表入，2代表出

	objectpoint(int x,int y);
	int onPress(int x, int y);
	int onRelease(int x, int y);
	void offset(int dx, int dy);
	void onDraw(CDC* pDC);
};

class object
{
public:
	int  left, up, right, down;			 //  左、上、右、下
	double width;	//线宽
	int color;		//颜色
	CPen pen;		//正常绘画时所用画笔
	CPen cursepen;	//拥有焦点时所用画笔
	CPen errorpen;	//编译出错时所用画笔
	CPen runpen;	//运行高亮时所用画笔
	objectpoint *op[4];	//四个连接点

	//图元类型
	enum { OBJECT = 0, START = 1, END = 2, INPUT = 3, OUTPUT = 4, PROCESS = 5, DECISION = 6, ARROWLINE = 10 }type;
	bool error;		//编译是否出错
	bool hold;		//是否可拖动
	bool curse;		//焦点
	bool run;
	object(int ID, int Left, int Up, int Right, int Down, int color, int width);

	void onSize(int l, int r, int u, int d);				//改变大小暂时没用
	void offset(int dx, int dy);							//位移
	int getID() { return ID; }								//获得ID

	virtual void onDraw(CDC* pDC);
	virtual int onPress(int x, int y) { return 0; }			//  鼠标按下
	virtual int onMove(int dx, int dy) { return 0; }		//  鼠标移动
	virtual int onRelease(int x, int y) { return 0; }		//  鼠标释放
	virtual int onDBclick(int x, int y) { return 0; }		//  鼠标双击
	virtual int onBuild(std::queue<object*>* q,Analyze* analyze) { return 0; }
	virtual int onRuning(object** obj, Analyze* analyze) { return 0; }
	virtual std::string onSave() { return ""; }
	virtual int onRead(std::ifstream &in) { return 0; }
private:
	int ID;		//图元ID
};

class start_box :public object
{
public:
	start_box(int ID, int x, int y, int color, int width);		//x,y为图元中点
	start_box(int ID, int Left, int Up, int Width, int Height, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
	int onBuild(std::queue<object*>* q, Analyze* analyze);
	int onRuning(object** obj, Analyze* analyze);
	std::string onSave();
};

class end_box :public object
{
public:
	end_box(int ID, int x, int y, int color, int width);		//x,y为图元中点
	end_box(int ID, int Left, int Up, int Width, int Height, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
	int onBuild(std::queue<object*>* q, Analyze* analyze);
	int onRuning(object** obj, Analyze* analyze);
	std::string onSave();
};

class arrowline :public object
{
public:
	int angle;			//箭头头部角度
	double length;		//箭头头部直线长度
	int lx, ly, rx, ry;	//存储另外两个端点

	object* o_in;		//箭头入方向
	int num_in;

	object* o_out;		//箭头出方向
	int num_out;

	arrowline(int ID, int x1, int y1, int x2, int y2, int color, int width);
	arrowline(int ID, int x1, int y1, int x2, int y2, int Angle, int Length, int color, int width);
	void onDraw(CDC* pDC);
	int onPress(int x, int y);			//暂时不用
	int onMove(int dx, int dy);			//暂时不用
	int onRelease(int x, int y);		//暂时不用
	void change(int type, int x, int y);			//改变线端点的值，type=1时，改变left和up的值，type=2时改变right和down的值
	void change_d(int type,int dx, int dy);			//线端点值位移，type=1时，改变left和up的值，type=2时改变right和down的值
	void deleteline();
	std::string onSave();
	int onRead(std::ifstream &in);

private:
	void init(int Angle, int Length);	//初始化
	void getTwoPoint();	//计算箭头另外两个端点，存储在lx,ly,rx,ry中
	bool onTheLine(int x1, int y1, int x2, int y2, int px, int py);
};