#pragma once
#include "stdafx.h"
class arrowline;

class objectpoint
{
public:
	int x;
	int y;
	int r;
	arrowline* al;
	int toward;		//0代表没有线，1代表入，2代表出

	objectpoint(int x,int y);
	int onPress(int x, int y);
	int onRelease(int x, int y);
	void offset(int dx, int dy);
};

class object
{
public:
	int  left, up, right, down;			 //  左、上、右、下
	double width;	//线宽
	int color;		//颜色
	CPen pen;	//画笔
	objectpoint *op[4];

	bool hold;
	bool curse;
	object(int ID, int l, int u, int r, int d, int color, int width);

	void onSize(int l, int r, int u, int d);
	void offset(int dx, int dy);
	//void deleteobject();
	int getID() { return ID; }

	virtual void onDraw(CDC* pDC) {}
	virtual int onPress(int x, int y) { return 0; }		//  鼠标按下
	virtual int onMove(int dx, int dy) { return 0; }		//  鼠标移动
	virtual int onRelease(int x, int y) { return 0; }		//  鼠标释放
	virtual std::string onSave() { return ""; }

private:
	int ID;
};

class start :public object
{
public:
	start(int ID, int x, int y, int w, int h, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
	std::string onSave();
};

class end :public object
{
public:
	end(int ID, int x, int y, int w, int h, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
	std::string onSave();
};

class unit:public object
{
public:
	unit(int ID, int x, int y, int w, int h, int color, int width);

	virtual void onDraw(CDC* pDC) {}
	virtual int  onPress(int x, int y) { return 0; }		//  鼠标按下
	virtual int onMove(int dx, int dy) { return 0; }		//  鼠标移动
	virtual int onRelease(int x, int y) { return 0; }		//  鼠标释放
	virtual std::string onSave() { return ""; }
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

	arrowline(int ID, int x, int y, int r, int d, int a, int l, int color, int width);
	void onDraw(CDC* pDC);
	int onPress(int x, int y);			//暂时不用
	int onMove(int dx, int dy);			//暂时不用
	int onRelease(int x, int y);		//暂时不用
	void change(int type,int dx, int dy);			//type=1时，改变left和up的值，type=2时改变right和down的值
	void deleteline();
	std::string onSave();

private:
	void getTwoPoint();	//计算箭头另外两个端点，存储在lx,ly,rx,ry中
	bool onTheLine(int x1, int y1, int x2, int y2, int px, int py);
};