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
	int onPress(int x, int y);		//  ��갴��
	int onMove(int dx, int dy);		//  ����ƶ�
	int onRelease(int x, int y);		//  ����ͷ�
	int onKey(int ch);
	int findCurse(int &id);
	void deleteobject(int ID);
	void deleteline(int ID);
	//std::string onSave() { return ""; }

	object* onCreate(int object_ID, int x = 0, int y = 0, int w = 0, int h = 0, int color = RGB(0, 0, 0), int width = 1);
private:
	int current_ID;			//��һ��Ӧ�ñ�������ID��
	bool line_establish;	//�Ƿ������������ڱ�����

	//����ͼԪo��op[opid]��������l��lpid��,lpid=1ʱ���������ߵ���ˣ�2�������
	void connectOToL(object* o, int opid, arrowline* l, int lpid);	
};