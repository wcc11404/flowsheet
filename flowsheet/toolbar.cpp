#include "stdafx.h"
#include "toolbar.h"

toolbar::toolbar(int x, int y) {
	barx = x;
	bary = y;
	barwidth = 80;
	barhight = 400;
	buttonwidth = 30;
	buttonhight = 16;
	maxtool = 6;

	barpen.CreatePen(PS_SOLID, 5, RGB(240, 240, 240));
	barbrush.CreateSolidBrush(RGB(240, 240, 240));
	buttonpen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	buttonbrush.CreateSolidBrush(RGB(255, 255, 255));
	intervalpen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
}

void toolbar::onDraw(CDC* pDC) {
	pDC->SelectObject(barpen);
	pDC->SelectObject(barbrush);
	pDC->Rectangle(barx, bary, barx + barwidth, bary + barhight);

	double d = barhight*1.0 / maxtool;
	double y = bary;
	int left ,up ,right,down;
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->SelectObject(buttonbrush);
	//����ʼ��ť
	pDC->SelectObject(buttonpen);
	left = barx + barwidth / 2 - buttonwidth / 2;
	up = y + d / 4;
	right = barx + barwidth / 2 + buttonwidth / 2;
	down = y + d / 4 + buttonhight;

	pDC->RoundRect(left, up, right, down, 12, 12);
	pDC->DrawTextA("��ʼ��", &CRect(barx, down+5, barx+barwidth, down + 5+20), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
	pDC->SelectObject(intervalpen);
	y += d;
	pDC->MoveTo(barx, y);
	pDC->LineTo(barx + barwidth, y);

	//��������ť
	pDC->SelectObject(buttonpen);
	left = barx + barwidth / 2 - buttonwidth / 2;
	up = y + d / 4;
	right = barx + barwidth / 2 + buttonwidth / 2;
	down = y + d / 4 + buttonhight;

	pDC->RoundRect(left, up, right, down, 12, 12);
	pDC->DrawTextA("������", &CRect(barx, down + 5, barx + barwidth, down + 5 + 20), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
	pDC->SelectObject(intervalpen);
	y += d;
	pDC->MoveTo(barx, y);
	pDC->LineTo(barx + barwidth, y);

	//�������ť
	pDC->SelectObject(buttonpen);
	left = barx + barwidth / 2 - buttonwidth / 2;
	up = y + d / 4;
	right = barx + barwidth / 2 + buttonwidth / 2;
	down = y + d / 4 + buttonhight;

	pDC->MoveTo(left, up + (down - up) / 3);
	pDC->LineTo(left, down);
	pDC->LineTo(right, down);
	pDC->LineTo(right, up);
	pDC->LineTo(left, up + (down - up) / 3);
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->FloodFill(left + 4, down-4, RGB(0, 0, 0));
	pDC->DrawTextA("�����", &CRect(barx, down + 5, barx + barwidth, down + 5 + 20), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	pDC->SelectObject(intervalpen);
	y += d;
	pDC->MoveTo(barx, y);
	pDC->LineTo(barx + barwidth, y);

	//�������ť
	pDC->SelectObject(buttonpen);
	left = barx + barwidth / 2 - buttonwidth / 2;
	up = y + d / 4;
	right = barx + barwidth / 2 + buttonwidth / 2;
	down = y + d / 4 + buttonhight;

	pDC->Ellipse(barx + barwidth / 2 - buttonwidth / 2, y + d / 4, barx + barwidth / 2 + buttonwidth / 2, y + d / 4 + buttonhight);
	pDC->DrawTextA("�����", &CRect(barx, down + 5, barx + barwidth, down + 5 + 20), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	pDC->SelectObject(intervalpen);
	y += d;
	pDC->MoveTo(barx, y);
	pDC->LineTo(barx + barwidth, y);

	//�������ť
	pDC->SelectObject(buttonpen);
	left = barx + barwidth / 2 - buttonwidth / 2;
	up = y + d / 4;
	right = barx + barwidth / 2 + buttonwidth / 2;
	down = y + d / 4 + buttonhight;

	pDC->Rectangle(left, up, right, down);
	pDC->DrawTextA("�����", &CRect(barx, down + 5, barx + barwidth, down + 5 + 20), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	pDC->SelectObject(intervalpen);
	y += d;
	pDC->MoveTo(barx, y);
	pDC->LineTo(barx + barwidth, y);

	//���жϿ�ť
	pDC->SelectObject(buttonpen);
	left = barx + barwidth / 2 - buttonwidth / 2;
	up = y + d / 4;
	right = barx + barwidth / 2 + buttonwidth / 2;
	down = y + d / 4 + buttonhight;

	pDC->MoveTo((left + right) / 2, up);
	pDC->LineTo(left, (up + down) / 2);
	pDC->LineTo((left + right) / 2, down);
	pDC->LineTo(right, (up + down) / 2);
	pDC->LineTo((left + right) / 2, up);
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->FloodFill(left + 4, (down+up)/2, RGB(0, 0, 0));
	pDC->DrawTextA("�жϿ�", &CRect(barx, down + 5, barx + barwidth, down + 5 + 20), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int toolbar::onPress(int x, int y) {
	double d = barhight*1.0 / maxtool;
	double yy = bary;
	int re = 0;
	if (x >= barx && x <= barx + barwidth&&y > bary&&y < bary + barhight) {
		for (int i = 0; i < maxtool; i++) {
			if (y >= (int)yy&&y <= (int)(yy + d)) {
				re = i + 1;
				break;
			}
			yy += d;
		}
	}
	return re;		//0����û�е㵽�κΰ�ť���������ִ���������re��ͼԪ��ť
}

int toolbar::onRelease(int x, int y) {
	return 0;
}