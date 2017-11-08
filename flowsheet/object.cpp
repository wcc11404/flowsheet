#include "stdafx.h"
#include "object.h"

object::object(int l, int u, int r, int d, int color, int width) {
	this->width = width;
	this->color = color;
	pen.CreatePen(PS_DOT, width, color);
	left = l;
	up = u;
	right = r;
	down = d;
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

/******************************     start      *********************************************/
start::start(int x, int y, int w, int h, int color, int width) :object(x, y, x + w, y + h, color, width) {
	//establish = true;
	click = false;
}

void start::onDraw(CDC *pDC) {
	pDC->SelectObject(pen);
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	pDC->Ellipse(left, up, right, down);
}

int start::onPress(int x, int y) {
	int rx = right + left;
	rx /= 2;
	int ry = down + up;
	ry /= 2;			//求得圆心
	int rr = right - left;
	rr /= 2;			//求得半径

	double dx2 = (rx - x)*(rx - x);
	int dy2 = (ry - y)*(ry - y);
	double dx = sqrt(dx2 + dy2);	//点击位置距离圆心的长度

	if (dx <= rr + width / 2) {
		click = true;
		return 1;
	}
	return 0;
}

int start::onMove(int dx, int dy) {
	if (click) {
		offset(dx, dy);
		return 1;
	}
	return 0;
}

void start::onRelease(int x, int y) {
	click = false;
}

std::string start::onSave() {
	std::string str = "";
	/*stringstream ss;
	ss << "1 " << left << " " << up << " " << right << " " << down << " " << color << " " << width;
	str = ss.str();*/
	return str;
}

/******************************     end      *********************************************/
end::end(int x, int y, int w, int h, int color, int width) :object(x, y, x + w, y + h, color, width) {
	//establish = true;
	click = false;
}

void end::onDraw(CDC *pDC) {
	pDC->SelectObject(pen);
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	pDC->Ellipse(left, up, right, down);
}

int end::onPress(int x, int y) {
	int rx = right + left;
	rx /= 2;
	int ry = down + up;
	ry /= 2;			//求得圆心
	int rr = right - left;
	rr /= 2;			//求得半径

	double dx2 = (rx - x)*(rx - x);
	int dy2 = (ry - y)*(ry - y);
	double dx = sqrt(dx2 + dy2);	//点击位置距离圆心的长度

	if (dx <= rr + width / 2) {
		click = true;
		return 1;
	}
	return 0;
}

int end::onMove(int dx, int dy) {
	if (click) {
		offset(dx, dy);
		return 1;
	}
	return 0;
}

void end::onRelease(int x, int y) {
	click = false;
}

std::string end::onSave() {
	std::string str = "";
	/*stringstream ss;
	ss << "1 " << left << " " << up << " " << right << " " << down << " " << color << " " << width;
	str = ss.str();*/
	return str;
}

/************************************         箭头         **********************************************/
arrowline::arrowline(int x, int y, int w, int h, int a, int l, int color, int width) :object(x, y, w, h, color, width) {
	//establish = true;
	memset(click, 0, sizeof(click));
	angle = a;
	length = l;
	lx = ly = rx = ry = 0;
	getTwoPoint();
}

void arrowline::onDraw(CDC *pDC) {
	pDC->SelectObject(pen);
	pDC->MoveTo(left, up);
	pDC->LineTo(right, down);

	pDC->MoveTo(right, down);
	pDC->LineTo(lx, ly);
	pDC->MoveTo(right, down);
	pDC->LineTo(rx, ry);
}

int arrowline::onPress(int x, int y) {

	if (onTheLine(left, up, right, down, x, y)) {
		click[0] = true;
		return 1;
	}
	else if (onTheLine(lx, ly, right, down, x, y)) {
		click[1] = true;
		return 1;
	}
	else if (onTheLine(rx, ry, right, down, x, y)) {
		click[2] = true;
		return 1;
	}

	return 0;
}

int arrowline::onMove(int dx, int dy) {
	bool b = false;
	for (int i = 0; i < 3; i++) {
		if (click[i])
			b = true;
	}
	if (b) {
		offset(dx, dy);
		getTwoPoint();
		return 1;
	}
	return 0;
}

void arrowline::onRelease(int x, int y) {
	memset(click, 0, sizeof(click));
	/*if (establish) {
		int d = (right - left)*(right - left) + (down - up)*(down - up);
		if (d != 0)
			establish = false;
	}*/
}

std::string arrowline::onSave() {
	std::string str = "";
	/*stringstream ss;
	ss << "5 " << left << " " << up << " " << right << " " << down << " " << color << " " << width;
	str = ss.str();*/
	return str;
}

void arrowline::getTwoPoint() {
	//double length = sqrt((right - (double)left)*(right - left) + (down - (double)up)*(down - up)) / scale;

	double theta = 3.1415926535*angle / 180;//转换为弧度
	double Px, Py, P1x, P1y, P2x, P2y;
	//以P2为原点得到向量P2P1（P）
	Px = left - right;
	Py = up - down;
	//向量P旋转theta角得到向量P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//向量P旋转-theta角得到向量P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//伸缩向量至制定长度
	double x11, x22;
	x11 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x11;
	P1y = P1y*length / x11;
	x22 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x22;
	P2y = P2y*length / x22;
	//平移变量到直线的末端
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