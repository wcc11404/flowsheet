#include "stdafx.h"
#include "object.h"
#include <sstream>

objectpoint::objectpoint(int x, int y) {
	this->x = x;
	this->y = y;
	al = NULL;
	toward = 0;
	radius = 8;		//�ڵ㸽���뾶Ϊr������������
}

int objectpoint::onPress(int x, int y) {
	int dx = x - this->x;;
	int dy = y - this->y;

	double r = sqrt(dx*dx + dy*dy);

	if (r <= radius) {
		return 1;
	}
	return 0;
}

int objectpoint::onRelease(int x, int y) {
	return onPress(x, y);
}

void objectpoint::offset(int dx, int dy) {
	x += dx;
	y += dy;

	if(al!=NULL) al->change_d(toward, dx, dy);
}

void objectpoint::onDraw(CDC* pDC) {
	pDC->SelectObject(new CPen(PS_SOLID, 1, RGB(0,0,0)));
	pDC->Rectangle(x - 3, y - 3, x + 3, y + 3);
}
/******************************     object     *********************************************/
object::object(int ID, int Left, int Up, int Right, int Down, int color, int width) {
	this->ID = ID;
	this->width = width;
	this->color = color;
	pen.CreatePen(PS_SOLID, width, color);
	cursepen.CreatePen(PS_SOLID, width + 1, RGB(34, 177, 76));
	errorpen.CreatePen(PS_SOLID, width + 1, RGB(255, 0, 0));
	runpen.CreatePen(PS_SOLID, width + 1, RGB(141, 254, 29));
	left = Left;
	up = Up;
	right = Right;
	down = Down;
	hold = false;
	curse = false;
	error = false;
	run = false;
	
	op[0] = new objectpoint((Left + Right) / 2, Up);
	op[1] = new objectpoint(Left, (Up + Down) / 2);
	op[2] = new objectpoint((Left + Right) / 2, Down);
	op[3] = new objectpoint(Right, (Up + Down) / 2);
}

void object::onSize(int l, int r, int u, int d) {
	left += l;
	up += u;
	right += r;
	down += d;
}

void object::offset(int dx, int dy) {
	left += dx;		right += dx;
	up += dy;		down += dy;
}

void object::onDraw(CDC* pDC) {
	if (error) {
		pDC->SelectObject(errorpen);
	}
	else if (run) {
		pDC->SelectObject(runpen);
	}
	else if (curse && !hold) {
		pDC->SelectObject(cursepen);
	}
	else {
		pDC->SelectObject(pen);
	}
}

/******************************     start      *********************************************/
start_box::start_box(int ID, int x, int y, int color, int width) 
	:object(ID, x-50, y-25, x + 50, y + 25, color, width) {
	type = START;
}
start_box::start_box(int ID, int Left, int Up, int Width, int Height, int color, int width) 
	:object(ID, Left, Up, Left + Width, Up + Height, color, width){
	type = START;
}

void start_box::onDraw(CDC *pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//͸�����
	pDC->RoundRect(left, up, right, down, (down - up) , (down - up) );

	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("�� ʼ", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	op[2]->onDraw(pDC);
}

int start_box::onPress(int x, int y) {
	curse = false;							//ʧȥ����

	if (op[2]->onPress(x,y)) return 4;		//�㵽���ӵ�
	else if(x >= left&&x <= right&&y >= up&&y <= down){		//�ھ�����
		curse = true;						//��ý���
		hold = true;						//�����϶�ͼԪ
		return 1;
	}
	return 0;
}

int start_box::onMove(int dx, int dy) {
	if (hold) {						//���ͼԪ�ɱ��϶�
		//curse = false;				//ʧȥ����
		offset(dx, dy);				//�ƶ�ͼԪ
		op[2]->offset(dx, dy);		//�ƶ����ӵ�
		return 1;
	}
	return 0;
}

int start_box::onRelease(int x, int y) {
	hold = false;
	return op[2]->onRelease(x, y)==1?2+1:0;		//�ͷŵ����ӵ��򷵻����ӵ��±�+1
}

int start_box::onBuild(std::queue<object*>* q, Analyze* analyze) {
	//error = false;

	if (op[2]->toward == 1) {
		q->push(op[2]->al->o_out);
		return 0;
	}
	else {
		if (op[2]->toward == 2)
			op[2]->al->error = true;
		error = true;
		return 1;
	}
		
}

int start_box::onRuning(object** obj, Analyze* analyze) {
	*obj = op[2]->al->o_out;
	op[2]->al->run = true;
	run = true;
	return 0;
}

std::string start_box::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	str = ss.str();
	return str;
}

/******************************     end      *********************************************/
end_box::end_box(int ID, int x, int y, int color, int width) 
	:object(ID, x - 50, y - 25, x + 50, y + 25, color, width) {
	type = END;
}
end_box::end_box(int ID, int Left, int Up, int Width, int Height, int color, int width) 
	:object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	type = END;
}

void end_box::onDraw(CDC *pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//͸�����
	//pDC->Ellipse(left, up, right, down);
	pDC->RoundRect(left, up, right, down, (down - up), (down - up));

	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("�� ��", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	op[0]->onDraw(pDC);
}

int end_box::onPress(int x, int y) {
	curse = false;							//ʧȥ����

	if (op[0]->onPress(x, y)) return 2;		//�㵽���ӵ�
	else if (x >= left&&x <= right&&y >= up&&y <= down) {		//�ھ�����
		curse = true;						//��ý���
		hold = true;						//�����϶�ͼԪ
		return 1;
	}
	return 0;
}

int end_box::onMove(int dx, int dy) {
	if (hold) {						//���ͼԪ�ɱ��϶�
		//curse = false;				//ʧȥ����
		offset(dx, dy);				//�ƶ�ͼԪ
		op[0]->offset(dx, dy);		//�ƶ����ӵ�
		return 1;
	}
	return 0;
}

int end_box::onRelease(int x, int y) {
	hold = false;
	return op[0]->onRelease(x, y)==1?0+1:0;		//�ͷŵ����ӵ��򷵻����ӵ��±�+1
}

int end_box::onBuild(std::queue<object*>* q, Analyze* analyze) {
	//error = false;

	if (op[0]->toward == 2)
		return 0;
	else {
		error = true;
		return 1;
	}
		
}

int end_box::onRuning(object** obj, Analyze* analyze) {
	*obj = NULL;
	run = true;
	return 0;
}

std::string end_box::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	str = ss.str();
	return str;
}

/************************************         ��ͷ         **********************************************/
void arrowline::init(int Angle,int Length) {
	angle = Angle;
	length = Length;
	lx = ly = rx = ry = 0;
	getTwoPoint();

	o_in = NULL;
	num_in = -1;
	o_out = NULL;
	num_out = -1;

	type = ARROWLINE;
}
arrowline::arrowline(int ID, int x1, int y1, int x2, int y2, int color, int width) 
	:object(ID, x1, y1, x2, y2, color, width) {
	init(30, 12);
}
arrowline::arrowline(int ID, int x1, int y1, int x2, int y2, int Angle, int Length, int color, int width) 
	:object(ID,x1, y1, x2, y2, color, width) {
	init(Angle, Length);
}

void arrowline::onDraw(CDC *pDC) {
	object::onDraw(pDC);

	pDC->MoveTo(left, up);
	pDC->LineTo(right, down);

	pDC->MoveTo(right, down);
	pDC->LineTo(lx, ly);
	pDC->MoveTo(right, down);
	pDC->LineTo(rx, ry);
}

int arrowline::onPress(int x, int y) {
	if (onTheLine(left, up, right, down, x, y)) {
		curse = true;
		//hold= true;
		return 1;
	}
	else if (onTheLine(lx, ly, right, down, x, y)) {
		curse = true;
		//hold = true;
		return 1;
	}
	else if (onTheLine(rx, ry, right, down, x, y)) {
		curse = true;
		//hold = true;
		return 1;
	}
	curse = false;
	return 0;
}

int arrowline::onMove(int dx, int dy) {
	if (hold) {
		//curse = false;
		offset(dx, dy);
		getTwoPoint();
		return 1;
	}
	return 0;
}

int arrowline::onRelease(int x, int y) {
	hold = false;
	return 0;
}

std::string arrowline::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	if (o_in != NULL) {
		ss << o_in->getID() << " " << num_in << std::endl;
	}
	else {
		ss << "-1" << std::endl;
	}
	if (o_out != NULL) {
		ss << o_out->getID() << " " << num_out << std::endl;
	}
	else {
		ss << "-1" << std::endl;
	}
	str = ss.str();
	return str;
}

int arrowline::onRead(std::ifstream &in) {
	return 0;
}

void arrowline::change(int type, int x, int y) {
	if (type == 1) {
		left = x;
		up = y;
	}
	else if (type == 2) {
		right = x;
		down = y;
	}
	else return;
	getTwoPoint();
}

void arrowline::change_d(int type,int dx, int dy) {
	if (type == 1) {
		left += dx;
		up += dy;
	}
	else if (type == 2) {
		right += dx;
		down += dy;
	}
	else return;
	getTwoPoint();
}

void arrowline::getTwoPoint() {
	//double length = sqrt((right - (double)left)*(right - left) + (down - (double)up)*(down - up)) / scale;

	double theta = 3.1415926535*angle / 180;//ת��Ϊ����
	double Px, Py, P1x, P1y, P2x, P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px = left - right;
	Py = up - down;
	//����P��תtheta�ǵõ�����P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//�����������ƶ�����
	double x11, x22;
	x11 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x11;
	P1y = P1y*length / x11;
	x22 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x22;
	P2y = P2y*length / x22;
	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x = P1x + right;
	P1y = P1y + down;
	P2x = P2x + right;
	P2y = P2y + down;

	lx = P1x;
	ly = P1y;
	rx = P2x;
	ry = P2y;
}

bool arrowline::onTheLine(int x1, int y1, int x2, int y2, int px, int py) {
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);

	if (dy > dx) {
		double xtemp = (py - (double)y2)*(x1 - x2) / (y1 - y2) + x2;

		if (px >= xtemp - width / 2 && px <= xtemp + width / 2) {
			return true;
		}
	}
	else {
		double ytemp = (y1 - y2)*(px - (double)x2) / (x1 - x2) + y2;

		if (py >= ytemp - width / 2 && py <= ytemp + width / 2) {
			return true;
		}
	}

	return false;
}

void arrowline::deleteline() {
	if (o_in != NULL) {
		o_in->op[num_in]->al = NULL;
		o_in->op[num_in]->toward = 0;
	}
	if (o_out != NULL) {
		o_out->op[num_out]->al = NULL;
		o_out->op[num_out]->toward = 0;
	}
}