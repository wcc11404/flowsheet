#include "stdafx.h"
#include "unit.h"

/************************************         �����         **********************************************/
input_box::input_box(int ID, int x, int y, int color, int width)
	: object(ID, x - 50, y - 25, x + 50, y + 25, color, width) {
	type = INPUT;
}
input_box::input_box(int ID, int Left, int Up, int Width, int Height, int color, int width)
	: object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	type = INPUT;
}

void input_box::onDraw(CDC* pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//͸�����
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("�����", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int input_box::onPress(int x, int y) {
	curse = false;							//ʧȥ����

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//�ھ�����
		curse = true;						//��ý���
		hold = true;						//�����϶�ͼԪ
		return 1;
	}
	return 0;
}

int input_box::onMove(int dx, int dy) {
	if (hold) {						//���ͼԪ�ɱ��϶�
		//curse = false;				//ʧȥ����
		offset(dx, dy);				//�ƶ�ͼԪ	
		for (int i = 0; i < 4; i++) {	//�ƶ����ӵ�
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int input_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//�ͷŵ����ӵ��򷵻����ӵ��±�+1
	}
	return 0;
}

int input_box::onDBclick(int x, int y) {
	if (x >= left&&x <= right&&y >= up&&y <= down) {
		input_dlg input;
		input.init(&iden);
		input.DoModal();
		return 1;
	}
	return 0;
}

int input_box::onBuild(std::queue<object*>* q) {
	//error = false;

	int innum = 0;
	int outnum = 0;
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		else if (op[i]->toward == 2)
			outnum++;
	}

	if (innum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				op[i]->al->error = true;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				q->push(op[i]->al->o_out);
		}
	}

	if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}
	
	if (error) return 1;
	return 0;
}

/************************************         �����         **********************************************/
output_box::output_box(int ID, int x, int y, int color, int width)
	: object(ID, x - 50, y - 25, x + 50, y + 25, color, width) {
	str = "";
	type = OUTPUT;
}
output_box::output_box(int ID, int Left, int Up, int Width, int Height, int color, int width)
	: object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	str = "";
	type = OUTPUT;
}

void output_box::onDraw(CDC* pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//͸�����
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("�����", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int output_box::onPress(int x, int y) {
	curse = false;							//ʧȥ����

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//�ھ�����
		curse = true;						//��ý���
		hold = true;						//�����϶�ͼԪ
		return 1;
	}
	return 0;
}

int output_box::onMove(int dx, int dy) {
	if (hold) {						//���ͼԪ�ɱ��϶�
		//curse = false;				//ʧȥ����
		offset(dx, dy);				//�ƶ�ͼԪ
		for (int i = 0; i < 4; i++) {	//�ƶ����ӵ�
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int output_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//�ͷŵ����ӵ��򷵻����ӵ��±�+1
	}
	return 0;
}

int output_box::onDBclick(int x, int y) {
	if (x >= left&&x <= right&&y >= up&&y <= down) {
		output_dlg output;
		output.str = &str;
		output.DoModal();
		return 1;
	}
	return 0;
}

int output_box::onBuild(std::queue<object*>* q) {
	//error = false;

	int innum = 0;
	int outnum = 0;
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		else if (op[i]->toward == 2)
			outnum++;
	}

	if (innum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				op[i]->al->error = true;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				q->push(op[i]->al->o_out);
		}
	}

	if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}

	if (error) return 1;
	return 0;
}

/************************************         �����         **********************************************/
process_box::process_box(int ID, int x, int y, int color, int width)
	:object(ID, x - 50, y - 25, x + 50, y + 25, color, width) {
	str = "";
	type = PROCESS;
}
process_box::process_box(int ID, int Left, int Up, int Width, int Height, int color, int width)
	: object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	str = "";
	type = PROCESS;
}

void process_box::onDraw(CDC* pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//͸�����
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("�����", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int process_box::onPress(int x, int y) {
	curse = false;							//ʧȥ����

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//�ھ�����
		curse = true;						//��ý���
		hold = true;						//�����϶�ͼԪ
		return 1;
	}
	return 0;
}

int process_box::onMove(int dx, int dy) {
	if (hold) {							//���ͼԪ�ɱ��϶�
		//curse = false;				//ʧȥ����
		offset(dx, dy);					//�ƶ�ͼԪ
		for (int i = 0; i < 4; i++) {	//�ƶ����ӵ�
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int process_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//�ͷŵ����ӵ��򷵻����ӵ��±�+1
	}
	return 0;
}

int process_box::onDBclick(int x, int y) {
	if (x >= left&&x <= right&&y >= up&&y <= down) {
		process_dlg process;
		process.str = &str;
		process.DoModal();
		return 1;
	}
	return 0;
}

int process_box::onBuild(std::queue<object*>* q) {
	//error = false;

	int innum = 0;
	int outnum = 0;
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		else if (op[i]->toward == 2)
			outnum++;
	}

	if (innum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				op[i]->al->error = true;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				q->push(op[i]->al->o_out);
		}
	}

	if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}

	if (error) return 1;
	return 0;
}

/************************************        �жϿ�         **********************************************/
decision_box::decision_box(int ID, int x, int y, int color, int width)
	:object(ID, x - 50, y - 25, x + 50, y + 25, color, width) {
	str = "";
	type = DECISION;
}
decision_box::decision_box(int ID, int Left, int Up, int Width, int Height, int color, int width)
	: object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	str = "";
	type = DECISION;
}

void decision_box::onDraw(CDC* pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//͸�����
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "����");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("�жϿ�", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int decision_box::onPress(int x, int y) {
	curse = false;							//ʧȥ����

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//�ھ�����
		curse = true;						//��ý���
		hold = true;						//�����϶�ͼԪ
		return 1;
	}
	return 0;
}

int decision_box::onMove(int dx, int dy) {
	if (hold) {						//���ͼԪ�ɱ��϶�
		//curse = false;				//ʧȥ����
		offset(dx, dy);				//�ƶ�ͼԪ
		for (int i = 0; i < 4; i++) {	//�ƶ����ӵ�
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int decision_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//�ͷŵ����ӵ��򷵻����ӵ��±�+1
	}
	return 0;
}

int decision_box::onDBclick(int x, int y) {
	if (x >= left&&x <= right&&y >= up&&y <= down) {
		decision_dlg decision;
		decision.str = &str;
		decision.DoModal();
		return 1;
	}
	return 0;
}

int decision_box::onBuild(std::queue<object*>* q) {
	//error = false;

	int innum = 0;
	int outnum = 0;
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		else if (op[i]->toward == 2)
			outnum++;
	}

	if (innum != 2) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				op[i]->al->error = true;
		}
		if (innum == 1) {
			for (int i = 0; i < 4; i++) {
				if (op[i]->toward == 1)
					q->push(op[i]->al->o_out);
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 1)
				q->push(op[i]->al->o_out);
		}
	}

	if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}

	if (error) return 1;
	return 0;
}