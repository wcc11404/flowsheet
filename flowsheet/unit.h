#pragma once
#include "object.h"

class input_box : public object
{
public:
	input_box(int ID, int x, int y, int color, int width);		//x,y为图元中点
	input_box(int ID, int Left, int Up, int Width, int Height, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
};

class output_box : public object
{
public:
	output_box(int ID, int x, int y, int color, int width);		//x,y为图元中点
	output_box(int ID, int Left, int Up, int Width, int Height, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
};

class process_box : public object
{
public:
	process_box(int ID, int x, int y, int color, int width);		//x,y为图元中点
	process_box(int ID, int Left, int Up, int Width, int Height, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
};

class decision_box : public object
{
public:
	decision_box(int ID, int x, int y, int color, int width);		//x,y为图元中点
	decision_box(int ID, int Left, int Up, int Width, int Height, int color, int width);

	void onDraw(CDC* pDC);
	int onPress(int x, int y);
	int onMove(int dx, int dy);
	int onRelease(int x, int y);
};