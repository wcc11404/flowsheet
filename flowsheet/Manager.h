#pragma once
#include "stdafx.h"
#include "object.h"
#include "toolbar.h"

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
	/*const int start_ID = 1;
	const int end_ID = 2;
	const int input_ID = 3;
	const int output_ID = 4;
	const int process_ID = 5;
	const int decision_ID = 6;
	const int arrowline_ID = 10;*/

	toolbar tb;
	
	Manager();

	void onDraw(CDC* pDC);
	int onPress(int x, int y);		//  ��갴��
	int onMove(int dx, int dy);		//  ����ƶ�
	int onRelease(int x, int y);	//  ����ͷ�
	int onKey(int ch);				//  ��������
	int onDBclick(int x, int y);	//  ���˫��
	int findCurse(int &id);
	
	//std::string onSave() { return ""; }

	int addobject(int object_ID, int x, int y, int color = RGB(0, 0, 0), int width = 1);
	int addline(int x1 = 0, int y1 = 0,int color = RGB(0, 0, 0), int width = 1);
	void deleteobject(int ID);
	void deleteline(int ID);

	object* onCreate(int object_ID, int x = 0, int y = 0, int color = RGB(0, 0, 0), int width = 1);
private:
	int current_ID;			//��һ��Ӧ�ñ�������ID��
	bool line_establish;	//�Ƿ������������ڱ�����

	//����ͼԪo��op[opid]��������l��lpid��,lpid=1ʱ���������ߵ���ˣ�2��������
	void connectOToL(object* o, int opid, arrowline* l, int lpid);	
};