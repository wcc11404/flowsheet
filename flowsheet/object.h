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
	int toward;		//0����û���ߣ�1�����룬2�����

	objectpoint(int x,int y);
	int onPress(int x, int y);
	int onRelease(int x, int y);
	void offset(int dx, int dy);
	void onDraw(CDC* pDC);
};

class object
{
public:
	int  left, up, right, down;			 //  ���ϡ��ҡ���
	double width;	//�߿�
	int color;		//��ɫ
	CPen pen;		//�����滭ʱ���û���
	CPen cursepen;	//ӵ�н���ʱ���û���
	CPen errorpen;	//�������ʱ���û���
	CPen runpen;	//���и���ʱ���û���
	objectpoint *op[4];	//�ĸ����ӵ�

	//ͼԪ����
	enum { OBJECT = 0, START = 1, END = 2, INPUT = 3, OUTPUT = 4, PROCESS = 5, DECISION = 6, ARROWLINE = 10 }type;
	bool error;		//�����Ƿ����
	bool hold;		//�Ƿ���϶�
	bool curse;		//����
	bool run;
	object(int ID, int Left, int Up, int Right, int Down, int color, int width);

	void onSize(int l, int r, int u, int d);				//�ı��С��ʱû��
	void offset(int dx, int dy);							//λ��
	int getID() { return ID; }								//���ID

	virtual void onDraw(CDC* pDC);
	virtual int onPress(int x, int y) { return 0; }			//  ��갴��
	virtual int onMove(int dx, int dy) { return 0; }		//  ����ƶ�
	virtual int onRelease(int x, int y) { return 0; }		//  ����ͷ�
	virtual int onDBclick(int x, int y) { return 0; }		//  ���˫��
	virtual int onBuild(std::queue<object*>* q,Analyze* analyze) { return 0; }
	virtual int onRuning(object** obj, Analyze* analyze) { return 0; }
	virtual std::string onSave() { return ""; }
	virtual int onRead(std::ifstream &in) { return 0; }
private:
	int ID;		//ͼԪID
};

class start_box :public object
{
public:
	start_box(int ID, int x, int y, int color, int width);		//x,yΪͼԪ�е�
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
	end_box(int ID, int x, int y, int color, int width);		//x,yΪͼԪ�е�
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
	int angle;			//��ͷͷ���Ƕ�
	double length;		//��ͷͷ��ֱ�߳���
	int lx, ly, rx, ry;	//�洢���������˵�

	object* o_in;		//��ͷ�뷽��
	int num_in;

	object* o_out;		//��ͷ������
	int num_out;

	arrowline(int ID, int x1, int y1, int x2, int y2, int color, int width);
	arrowline(int ID, int x1, int y1, int x2, int y2, int Angle, int Length, int color, int width);
	void onDraw(CDC* pDC);
	int onPress(int x, int y);			//��ʱ����
	int onMove(int dx, int dy);			//��ʱ����
	int onRelease(int x, int y);		//��ʱ����
	void change(int type, int x, int y);			//�ı��߶˵��ֵ��type=1ʱ���ı�left��up��ֵ��type=2ʱ�ı�right��down��ֵ
	void change_d(int type,int dx, int dy);			//�߶˵�ֵλ�ƣ�type=1ʱ���ı�left��up��ֵ��type=2ʱ�ı�right��down��ֵ
	void deleteline();
	std::string onSave();
	int onRead(std::ifstream &in);

private:
	void init(int Angle, int Length);	//��ʼ��
	void getTwoPoint();	//�����ͷ���������˵㣬�洢��lx,ly,rx,ry��
	bool onTheLine(int x1, int y1, int x2, int y2, int px, int py);
};