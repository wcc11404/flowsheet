#include "stdafx.h"
#include "unit.h"

/************************************         输入框         **********************************************/
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
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("输入框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int input_box::onPress(int x, int y) {
	curse = false;							//失去焦点

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//在矩形内
		curse = true;						//获得焦点
		hold = true;						//鼠标可拖动图元
		return 1;
	}
	return 0;
}

int input_box::onMove(int dx, int dy) {
	if (hold) {						//如果图元可被拖动
		//curse = false;				//失去焦点
		offset(dx, dy);				//移动图元	
		for (int i = 0; i < 4; i++) {	//移动连接点
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int input_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//释放到连接点则返回连接点下标+1
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

/************************************         输出框         **********************************************/
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
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("输出框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int output_box::onPress(int x, int y) {
	curse = false;							//失去焦点

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//在矩形内
		curse = true;						//获得焦点
		hold = true;						//鼠标可拖动图元
		return 1;
	}
	return 0;
}

int output_box::onMove(int dx, int dy) {
	if (hold) {						//如果图元可被拖动
		//curse = false;				//失去焦点
		offset(dx, dy);				//移动图元
		for (int i = 0; i < 4; i++) {	//移动连接点
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int output_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//释放到连接点则返回连接点下标+1
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

/************************************         处理框         **********************************************/
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
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("处理框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int process_box::onPress(int x, int y) {
	curse = false;							//失去焦点

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//在矩形内
		curse = true;						//获得焦点
		hold = true;						//鼠标可拖动图元
		return 1;
	}
	return 0;
}

int process_box::onMove(int dx, int dy) {
	if (hold) {							//如果图元可被拖动
		//curse = false;				//失去焦点
		offset(dx, dy);					//移动图元
		for (int i = 0; i < 4; i++) {	//移动连接点
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int process_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//释放到连接点则返回连接点下标+1
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

/************************************        判断框         **********************************************/
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
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	pDC->Rectangle(left, up, right, down);
	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	pDC->DrawTextA("判断框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

int decision_box::onPress(int x, int y) {
	curse = false;							//失去焦点

	for (int i = 0; i < 4; i++) {
		if (op[i]->onPress(x, y)) return i + 2;
	}
	if (x >= left&&x <= right&&y >= up&&y <= down) {		//在矩形内
		curse = true;						//获得焦点
		hold = true;						//鼠标可拖动图元
		return 1;
	}
	return 0;
}

int decision_box::onMove(int dx, int dy) {
	if (hold) {						//如果图元可被拖动
		//curse = false;				//失去焦点
		offset(dx, dy);				//移动图元
		for (int i = 0; i < 4; i++) {	//移动连接点
			op[i]->offset(dx, dy);
		}
		return 1;
	}
	return 0;
}

int decision_box::onRelease(int x, int y) {
	hold = false;
	for (int i = 0; i < 4; i++) {
		if (op[i]->onRelease(x, y)) return i + 1;	//释放到连接点则返回连接点下标+1
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