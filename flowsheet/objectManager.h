#pragma once
#include "stdafx.h"
#include "object.h"

class objectManager
{
public:
	std::vector<object*> unitArray;
	std::vector<arrowline*> lineArray;
	const int start_ID = 1;
	const int end_ID = 2;
	const int arrowline_ID = 3;
	
	objectManager();

	void onDraw(CDC* pDC);
	int onPress(int x, int y);		//  鼠标按下
	int onMove(int dx, int dy);		//  鼠标移动
	int onRelease(int x, int y);		//  鼠标释放
	int onKey(int ch);
	int findCurse(int &id);
	void deleteobject(int ID);
	void deleteline(int ID);
	//std::string onSave() { return ""; }

	object* onCreate(int object_ID, int x = 0, int y = 0, int w = 0, int h = 0, int color = RGB(0, 0, 0), int width = 1);
private:
	int current_ID;			//下一个应该被创建的ID号
	bool line_establish;	//是否有连接线正在被创建

	//连接图元o的op[opid]和连接线l的lpid端,lpid=1时代表连接线的入端，2代表出端
	void connectOToL(object* o, int opid, arrowline* l, int lpid);	
};