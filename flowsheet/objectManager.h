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
	int  onPress(int x, int y);		//  鼠标按下
	int  onMove(int dx, int dy);		//  鼠标移动
	void  onRelease(int x, int y);		//  鼠标释放
	//std::string onSave() { return ""; }

	object* onCreate(int object_ID, int x = 0, int y = 0, int w = 0, int h = 0, int color = RGB(255, 255, 255), int width = 1);
};