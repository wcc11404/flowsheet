#pragma once
#include "stdafx.h"

class object
{
public:
	int  left, up, right, down;			 //  ���ϡ��ҡ���
	double width;	//�߿�
	int color;		//��ɫ
	CPen pen;	//����
	//bool establish;		//�Ƿ񱻴�����
	object(int l, int u, int r, int d, int color, int width);

	void onSize(int l, int r, int u, int d);
	void offset(int dx, int dy);

	virtual void onDraw(CDC* pDC) {}
	virtual int  onPress(int x, int y) { return 0; }		//  ��갴��
	virtual int   onMove(int dx, int dy) { return 0; }		//  ����ƶ�
	virtual void  onRelease(int x, int y) {}		//  ����ͷ�
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
	virtual int  onPress(int x, int y) { return 0; }		//  ��갴��
	virtual int   onMove(int dx, int dy) { return 0; }		//  ����ƶ�
	virtual void  onRelease(int x, int y) {}		//  ����ͷ�
	virtual std::string onSave() { return ""; }
};

class arrowline :public object
{
public:
	bool click[3];		//�Ƿ�ѡ��
	int angle;			//��ͷͷ���Ƕ�
	double length;			//��ͷͷ��ռֱ�߳���
	int lx, ly, rx, ry;	//�洢���������˵�

	arrowline(int x, int y, int w, int h, int a, int l, int color, int width);
	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int   onMove(int dx, int dy);
	void  onRelease(int x, int y);
	std::string onSave();

private:
	void getTwoPoint();	//�����ͷ���������˵㣬�洢��lx,ly,rx,ry��
	bool onTheLine(int x1, int y1, int x2, int y2, int px, int py);
};