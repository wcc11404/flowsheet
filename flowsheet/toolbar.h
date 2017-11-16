#pragma once
#include "stdafx.h"

class toolbar
{
public:
	int barx;
	int bary;
	int barwidth;
	int barhight;
	int maxtool;
	CPen barpen;
	CBrush barbrush;

	int buttonwidth;
	int buttonhight;
	CPen buttonpen;
	CPen intervalpen;
	CBrush buttonbrush;
	toolbar(int x, int y);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onRelease(int x, int y);
};