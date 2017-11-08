#pragma once
#include "stdafx.h"
#include "object.h"

class objectManager
{
public:
	std::vector<object*> unitArray;
	std::vector<object*> lineArray;
	const int start_ID = 1;
	const int end_ID = 2;
	const int arrowline_ID = 3;

	objectManager();

	void onDraw(CDC* pDC);
	int  onPress(int x, int y);		//  ��갴��
	int  onMove(int dx, int dy);		//  ����ƶ�
	void  onRelease(int x, int y);		//  ����ͷ�
	//std::string onSave() { return ""; }

	object* onCreate(int object_ID, int x, int y, int w, int h, int color, int width);
};