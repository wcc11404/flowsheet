#pragma once
#include "stdafx.h"

class toolbar
{
public:
	int barx;
	int bary;
	int barwidth;
	int barhight;
	CPen barpen;
	CBrush barbrush;

	int buttonwidth;
	int buttonhight;
	CPen buttonpen;
	CBrush buttonbrush;
	toolbar(int x, int y);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onRelease(int x, int y);
};