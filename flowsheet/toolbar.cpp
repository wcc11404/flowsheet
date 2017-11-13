#include "stdafx.h"
#include "toolbar.h"

toolbar::toolbar(int x, int y) {
	barx = x;
	bary = y;
	barwidth = 50;
	barhight = 300;
	buttonwidth = 30;
	buttonhight = 16;

	barpen.CreatePen(PS_SOLID, 5, RGB(240, 240, 240));
	barbrush.CreateSolidBrush(RGB(240, 240, 240));
	buttonpen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	buttonbrush.CreateSolidBrush(RGB(255, 255, 255));
}

void toolbar::onDraw(CDC* pDC) {
	pDC->SelectObject(barpen);
	pDC->SelectObject(barbrush);
	//pDC->Draw3dRect(x, y, 50, 300, RGB(200, 200, 200), RGB(200, 200, 200));
	pDC->Rectangle(barx, bary, barx + barwidth, bary + barhight);

	pDC->SelectObject(buttonpen);
	pDC->SelectObject(buttonbrush);

	//画开始框按钮
	int y = 20;
	pDC->RoundRect(barx + barwidth / 2 - buttonwidth / 2, y, barx + barwidth / 2 + buttonwidth / 2, y + buttonhight, 12, 12);
	y += buttonhight;

	//画结束框按钮
	y += 20;
	pDC->RoundRect(barx + barwidth / 2 - buttonwidth / 2, y, barx + barwidth / 2 + buttonwidth / 2, y + buttonhight, 12, 12);
	y += buttonhight;

	//画输入框按钮
	y += 20;
	pDC->Rectangle(barx + barwidth / 2 - buttonwidth / 2, y, barx + barwidth / 2 + buttonwidth / 2, y + buttonhight);
	y += buttonhight;

	//画输出框按钮
	y += 20;
	pDC->Rectangle(barx + barwidth / 2 - buttonwidth / 2, y, barx + barwidth / 2 + buttonwidth / 2, y + buttonhight);
	y += buttonhight;

	//画处理框按钮
	y += 20;
	pDC->Rectangle(barx + barwidth / 2 - buttonwidth / 2, y, barx + barwidth / 2 + buttonwidth / 2, y + buttonhight);
	y += buttonhight;

	//画判断框按钮
	y += 20;
	pDC->Rectangle(barx + barwidth / 2 - buttonwidth / 2, y, barx + barwidth / 2 + buttonwidth / 2, y + buttonhight);
	y += buttonhight;
}

int toolbar::onPress(int x, int y) {
	int re = 0;
	if (x >= barx + barwidth / 2 - buttonwidth / 2 && x <= barx + barwidth / 2 + buttonwidth / 2) {
		int yy = 20;
		for (int i = 0; i < 6; i++) {
			if (y >= yy&&y <= yy + buttonhight) {
				re = i+1;
				break;
			}
			yy += buttonhight;
			yy += 20;
		}
	}
	return re;		//0代表没有点到任何按钮，其他数字代表点击到第re个图元按钮
}

int toolbar::onRelease(int x, int y) {
	return 0;
}