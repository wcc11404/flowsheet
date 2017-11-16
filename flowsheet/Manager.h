#pragma once
#include "stdafx.h"
#include "object.h"
#include "toolbar.h"
#include "analyze.h"
#include <fstream>

class Manager
{
public:
	std::vector<object*> unitArray;
	std::vector<arrowline*> lineArray;

	#define START_ID 1
	#define END_ID 2
	#define INPUT_ID 3
	#define OUTPUT_ID 4
	#define PROCESS_ID 5
	#define DECISION_ID 6
	#define ARROWLINE_ID 10

	const int IDARRAY[6] = { START_ID ,END_ID ,INPUT_ID ,OUTPUT_ID ,PROCESS_ID , DECISION_ID };

	toolbar tb;		//左上角画板
	Analyze analyze;	//分析器

	Manager();

	void onDraw(CDC* pDC);			//  画图
	int onPress(int x, int y);		//  鼠标按下
	int onMove(int dx, int dy);		//  鼠标移动
	int onRelease(int x, int y);	//  鼠标释放
	int onKey(int ch);				//  按键按下
	int onDBclick(int x, int y);	//  鼠标双击

	int onBuild();					//  生成解决方案
	int onClearBuild();				//	清理解决方案
	int onRuning();					//  运行
	int onClearRuning();			//  清理运行结果

	int onSave(std::ofstream& out);
	int onOpen(std::ifstream& in);
	int onClear();

	int findCurse(int &id);			//  查找拥有焦点的图元或者连线
	object* findID(int id);

	//添加图元或连线以及删除图元或连线
	int addobject(int object_ID, int x, int y, int color = RGB(0, 0, 0), int width = 2);
	int addline(int x1 = 0, int y1 = 0,int color = RGB(0, 0, 0), int width = 2);
	void deleteobject(int ID);
	void deleteline(int ID);

	//工厂模式建立各种图元以及连线
	object* onCreate(int object_ID, int x = 0, int y = 0, int color = RGB(0, 0, 0), int width = 2);		
private:
	int current_ID;			//下一个应该被创建的ID号
	bool line_establish;	//是否有连接线正在被创建

	//连接图元o的op[opid]和连接线l的lpid端,lpid=1时代表连接线的入端，2代表出端
	void connectOToL(object* o, int opid, arrowline* l, int lpid);	
};