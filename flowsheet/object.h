#pragma once
#include "stdafx.h"

class object
{
public:
	int  left, up, right, down;			 //  左、上、右、下
	double width;	//线宽
	int color;		//颜色
	CPen pen;	//画笔
	//bool establish;		//是否被创建中
	object(int l, int u, int r, int d, int color, int width);

	void onSize(int l, int r, int u, int d);
	void offset(int dx, int dy);

	virtual void onDraw(CDC* pDC) {}
	virtual int  onPress(int x, int y) { return 0; }		//  鼠标按下
	virtual int   onMove(int dx, int dy) { return 0; }		//  鼠标移动
	virtual void  onRelease(int x, int y) {}		//  鼠标释放
	virtual std::string onSave() { return ""; }
};

class start :public object
{
public:
	bool click;

	start(int x, int y, int w, int h, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int   onMove(int dx, int dy);
	void  onRelease(int x, int y);
	std::string onSave();
};

class end :public object
{
public:
	bool click;

	end(int x, int y, int w, int h, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int   onMove(int dx, int dy);
	void  onRelease(int x, int y);
	std::string onSave();
};

class unit:public object
{
public:
	bool click;

	unit(int x, int y, int w, int h, int color, int width);

	virtual void onDraw(CDC* pDC) {}
	virtual int  onPress(int x, int y) { return 0; }		//  鼠标按下
	virtual int   onMove(int dx, int dy) { return 0; }		//  鼠标移动
	virtual void  onRelease(int x, int y) {}		//  鼠标释放
	virtual std::string onSave() { return ""; }
};

class arrowline :public object
{
public:
	bool click[3];		//是否被选中
	int angle;			//箭头头部角度
	double length;			//箭头头部占直线长度
	int lx, ly, rx, ry;	//存储另外两个端点

	arrowline(int x, int y, int w, int h, int a, int l, int color, int width);
	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int   onMove(int dx, int dy);
	void  onRelease(int x, int y);
	std::string onSave();

private:
	void getTwoPoint();	//计算箭头另外两个端点，存储在lx,ly,rx,ry中
	bool onTheLine(int x1, int y1, int x2, int y2, int px, int py);
};