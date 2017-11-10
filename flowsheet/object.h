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
	int toward;		//0����û���ߣ�1�����룬2�����

	objectpoint(int x,int y);
	int onPress(int x, int y);
	int onRelease(int x, int y);
	void offset(int dx, int dy);
};

class object
{
public:
	int  left, up, right, down;			 //  ���ϡ��ҡ���
	double width;	//�߿�
	int color;		//��ɫ
	CPen pen;	//����
	objectpoint *op[4];

	bool hold;
	bool curse;
	object(int ID, int l, int u, int r, int d, int color, int width);

	void onSize(int l, int r, int u, int d);
	void offset(int dx, int dy);
	//void deleteobject();
	int getID() { return ID; }

	virtual void onDraw(CDC* pDC) {}
	virtual int onPress(int x, int y) { return 0; }		//  ��갴��
	virtual int onMove(int dx, int dy) { return 0; }		//  ����ƶ�
	virtual int onRelease(int x, int y) { return 0; }		//  ����ͷ�
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
	virtual int  onPress(int x, int y) { return 0; }		//  ��갴��
	virtual int onMove(int dx, int dy) { return 0; }		//  ����ƶ�
	virtual int onRelease(int x, int y) { return 0; }		//  ����ͷ�
	virtual std::string onSave() { return ""; }
};

class arrowline :public object
{
public:
	int angle;			//��ͷͷ���Ƕ�
	double length;		//��ͷͷ��ֱ�߳���
	int lx, ly, rx, ry;	//�洢���������˵�

	object* o_in;		//��ͷ�뷽��
	int num_in;

	object* o_out;		//��ͷ������
	int num_out;

	arrowline(int ID, int x, int y, int r, int d, int a, int l, int color, int width);
	void onDraw(CDC* pDC);
	int onPress(int x, int y);			//��ʱ����
	int onMove(int dx, int dy);			//��ʱ����
	int onRelease(int x, int y);		//��ʱ����
	void change(int type,int dx, int dy);			//type=1ʱ���ı�left��up��ֵ��type=2ʱ�ı�right��down��ֵ
	void deleteline();
	std::string onSave();

private:
	void getTwoPoint();	//�����ͷ���������˵㣬�洢��lx,ly,rx,ry��
	bool onTheLine(int x1, int y1, int x2, int y2, int px, int py);
};