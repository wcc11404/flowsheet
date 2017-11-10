#include "stdafx.h"
#include "object.h"

objectpoint::objectpoint(int x, int y) {
	this->x = x;
	this->y = y;
	al = NULL;
	toward = 0;
	r = 5;		//在点附近半径为r的区域点击都算
}

int objectpoint::onPress(int x, int y) {
	int dx = x - this->x;;
	int dy = y - this->y;

	double r = sqrt(dx*dx + dy*dy);

	if (r <= this->r) {
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

	al->change(toward, dx, dy);
}
/******************************     object     *********************************************/
object::object(int ID, int l, int u, int r, int d, int color, int width) {
	this->ID = ID;
	this->width = width;
	this->color = color;
	pen.CreatePen(PS_SOLID, width, color);
	left = l;
	up = u;
	right = r;
	down = d;
	hold = false;
	curse = false;
	
	op[0] = new objectpoint((l + r) / 2, u);
	op[1] = new objectpoint(l, (u + d) / 2);
	op[2] = new objectpoint((l + r) / 2, d);
	op[3] = new objectpoint(r, (u + d) / 2);
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

//void object::deleteobject() {
//	for (int i = 0; i < 4; i++) {
//		if (op[i] != NULL) {
//			if(op[i]->al!=NULL)
//				op[i]->al->deleteline();
//		}
//	}
//}

/******************************     start      *********************************************/
start::start(int ID, int x, int y, int w, int h, int color, int width) :object(ID, x, y, x + w, y + h, color, width){
	//op[2] = new objectpoint(x + w / 2, y + h);
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

	curse = false;
	if (op[2]->onPress(x,y)) {
		return 4;
	}
	else if(dx <= rr + width / 2) {
		curse = true;
		hold = true;
		return 1;
	}
	return 0;
}

int start::onMove(int dx, int dy) {
	if (hold) {
		curse = false;
		offset(dx, dy);
		op[2]->offset(dx, dy);
		return 1;
	}
	return 0;
}

int start::onRelease(int x, int y) {
	hold = false;
	return op[2]->onRelease(x, y)==1?2+1:0;
}

std::string start::onSave() {
	std::string str = "";
	/*stringstream ss;
	ss << "1 " << left << " " << up << " " << right << " " << down << " " << color << " " << width;
	str = ss.str();*/
	return str;
}

/******************************     end      *********************************************/
end::end(int ID, int x, int y, int w, int h, int color, int width) :object(ID,x, y, x + w, y + h, color, width) {
	//op[0] = new objectpoint(x + w / 2, y);
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

	curse = false;
	if (op[0]->onPress(x, y)) {
		return 2;
	}
	else if (dx <= rr + width / 2) {
		curse = true;
		hold = true;
		return 1;
	}
	return 0;
}

int end::onMove(int dx, int dy) {
	if (hold) {
		curse = false;
		offset(dx, dy);
		op[0]->offset(dx, dy);
		return 1;
	}
	return 0;
}

int end::onRelease(int x, int y) {
	hold = false;
	return op[0]->onRelease(x, y)==1?0+1:0;
}

std::string end::onSave() {
	std::string str = "";
	/*stringstream ss;
	ss << "1 " << left << " " << up << " " << right << " " << down << " " << color << " " << width;
	str = ss.str();*/
	return str;
}

/************************************         箭头         **********************************************/
arrowline::arrowline(int ID, int x, int y, int r, int d, int a, int l, int color, int width) :object(ID,x, y, r, d, color, width) {
	angle = a;
	length = l;
	lx = ly = rx = ry = 0;
	getTwoPoint();

	o_in = NULL;
	num_in = -1;
	o_out = NULL;
	num_out = -1;
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
		curse = true;
		hold= true;
		return 1;
	}
	curse = false;
	return 0;
}

int arrowline::onMove(int dx, int dy) {
	if (hold) {
		curse = false;
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
	/*stringstream ss;
	ss << "5 " << left << " " << up << " " << right << " " << down << " " << color << " " << width;
	str = ss.str();*/
	return str;
}

void arrowline::change(int type,int dx, int dy) {
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