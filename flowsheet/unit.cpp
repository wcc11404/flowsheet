#include "stdafx.h"
#include "unit.h"
#include <sstream>

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
	//pDC->Rectangle(left, up, right, down);
	pDC->MoveTo(left, up + (down - up) / 3);
	pDC->LineTo(left, down);
	pDC->LineTo(right, down);
	pDC->LineTo(right, up);
	pDC->LineTo(left, up + (down - up) / 3);

	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	if (iden.size() == 0) {
		pDC->DrawTextA("输入框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	else {
		char temp[80];
		for (std::map<std::string, double>::iterator it = iden.begin(); it != iden.end(); it++) {
			sprintf(temp, "%s=%g", it->first.c_str(), it->second);
		}
		CString stemp(temp);
		pDC->DrawTextA(stemp, &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	

	for (int i = 0; i < 4; i++) {
		op[i]->onDraw(pDC);
	}
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

int input_box::onBuild(std::queue<object*>* q, Analyze* analyze) {
	//error = false;

	int innum = 0;
	//int outnum = 0;
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		/*else if (op[i]->toward == 2)
			outnum++;*/
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

	/*if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}*/
	
	if (error) return 1;

	if (iden.size() == 0) {
		error = true;
		return 1;
	}
		
	return 0;
}

int input_box::onRuning(object** obj, Analyze* analyze) {
	Analyze::identify(&iden);
	
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1) {
			*obj = op[i]->al->o_out;
			op[i]->al->run = true;
			break;
		}
	}

	run = true;

	return 0;
}

std::string input_box::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	ss << iden.size() << std::endl;
	for (std::map<std::string, double>::iterator it = iden.begin(); it != iden.end(); it++) {
		ss << it->first << " " << it->second << std::endl;
	}
	str = ss.str();
	return str;
}

int input_box::onRead(std::ifstream &in) {
	char temp[80];
	in.getline(temp, sizeof(temp));
	std::stringstream ss(temp);
	int size = 0;
	ss >> size;
	while (size--) {
		std::string name;
		double value;
		in.getline(temp, sizeof(temp));
		std::stringstream ss1(temp);
		ss1 >> name >> value;
		iden[name] = value;
	}
	return 0;
}

/************************************         输出框         **********************************************/
output_box::output_box(int ID, int x, int y, int color, int width)
	: object(ID, x - 50, y - 25, x + 50, y + 25, color, width) {
	str = "";
	type = OUTPUT;
	show = false;
	value = 0;
}
output_box::output_box(int ID, int Left, int Up, int Width, int Height, int color, int width)
	: object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	str = "";
	type = OUTPUT;
	show = false;
	value = 0;
}

void output_box::onDraw(CDC* pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	//pDC->Rectangle(left, up, right, down);
	pDC->Ellipse(left, up, right, down);

	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	if(str=="")
		pDC->DrawTextA("输出框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	else {
		CString temp;
		if (show)
			temp.Format("%s=%g", str.c_str(), value);
		else
			temp.Format("%s", str.c_str());
		pDC->DrawTextA(temp, &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}

	for (int i = 0; i < 4; i++) {
		op[i]->onDraw(pDC);
	}
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
		output.value = &value;
		output.show = &show;
		output.DoModal();
		return 1;
	}
	return 0;
}

int output_box::onBuild(std::queue<object*>* q, Analyze* analyze) {
	//error = false;

	int innum = 0;
	/*int outnum = 0;*/
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		/*else if (op[i]->toward == 2)
			outnum++;*/
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

	/*if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}*/

	if (error) return 1;

	if (str == "") {
		error = true;
		return 1;
	}
		
	return 0;
}

int output_box::onRuning(object** obj, Analyze* analyze) {
	double num=Analyze::findIdenValue(str);
	value = num;
	show = true;
	
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1) {
			*obj = op[i]->al->o_out;
			op[i]->al->run = true;
			break;
		}
	}

	run = true;

	return 0;
}

std::string output_box::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	if (this->str == "")
		ss << "-1";
	else
		ss << this->str ;
	ss << std::endl;
	str = ss.str();
	return str;
}

int output_box::onRead(std::ifstream &in) {
	char temp[80];
	in.getline(temp, sizeof(temp));
	std::string tem= temp;
	if (tem != "-1")
		this->str = tem;
	return 0;
}

/************************************         处理框         **********************************************/
process_box::process_box(int ID, int x, int y, int color, int width)
	:object(ID, x - 60, y - 30, x + 60, y + 30, color, width) {
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
	if (str == "")
		pDC->DrawTextA("处理框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	else {
		pDC->DrawTextA(str.c_str(), &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	

	for (int i = 0; i < 4; i++) {
		op[i]->onDraw(pDC);
	}
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

int process_box::onBuild(std::queue<object*>* q, Analyze* analyze) {
	//error = false;

	int innum = 0;
	/*int outnum = 0;*/
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		/*else if (op[i]->toward == 2)
			outnum++;*/
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

	/*if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}*/

	if (error) return 1;

	//处理代码
	int re = analyze->inspectStr(str);
	if (re > 0) {
		error = true;
		return re;
	}
	
	return 0;
}

int process_box::onRuning(object** obj, Analyze* analyze) {
	analyze->inspectStr(str);
	analyze->calculate();

	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1) {
			*obj = op[i]->al->o_out;
			op[i]->al->run = true;
			break;
		}
	}

	run = true;

	return 0;
}

std::string process_box::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	if (this->str == "")
		ss << "-1";
	else
		ss << this->str;
	ss << std::endl;
	str = ss.str();
	return str;
}

int process_box::onRead(std::ifstream &in) {
	char temp[80];
	in.getline(temp, sizeof(temp));
	std::string tem = temp;
	if (tem != "-1")
		this->str = tem;
	return 0;
}

/************************************        判断框         **********************************************/
decision_box::decision_box(int ID, int x, int y, int color, int width)
	:object(ID, x - 70, y - 35, x + 70, y + 35, color, width) {
	str = "";
	type = DECISION;
	memset(judge, 0, sizeof(judge));
}
decision_box::decision_box(int ID, int Left, int Up, int Width, int Height, int color, int width)
	: object(ID, Left, Up, Left + Width, Up + Height, color, width) {
	str = "";
	type = DECISION;
	memset(judge, 0, sizeof(judge));
}

void decision_box::onDraw(CDC* pDC) {
	object::onDraw(pDC);
	//pDC->SelectStockObject(NULL_BRUSH);		//透明填充
	//pDC->Rectangle(left, up, right, down);
	pDC->MoveTo((left + right) / 2, up);
	pDC->LineTo(left, (up + down) / 2);
	pDC->LineTo((left + right) / 2, down);
	pDC->LineTo(right, (up + down) / 2);
	pDC->LineTo((left + right) / 2, up);

	pDC->SetBkMode(TRANSPARENT);
	CFont fontGrade;
	fontGrade.CreatePointFont(100, "宋体");
	pDC->SelectObject(&fontGrade);
	if (str == "")
		pDC->DrawTextA("判断框", &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	else {
		pDC->DrawTextA(str.c_str(), &CRect(left, up, right, down), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	CString temp[2];
	temp[0] = "否";
	temp[1] = "是";
	if (judge[0] != 0) {
		pDC->DrawTextA(temp[judge[0] - 1], &CRect(op[0]->x - 10, op[0]->y - 12 - 10, op[0]->x + 10, op[0]->y - 12 + 10), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	if (judge[1] != 0) {
		pDC->DrawTextA(temp[judge[1] - 1], &CRect(op[1]->x - 12 - 10, op[1]->y - 10, op[1]->x - 12 + 10, op[1]->y + 10), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	if (judge[2] != 0) {
		pDC->DrawTextA(temp[judge[2] - 1], &CRect(op[2]->x - 10, op[2]->y + 12 - 10, op[2]->x + 10, op[2]->y + 12 + 10), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	if (judge[3] != 0) {
		pDC->DrawTextA(temp[judge[3] - 1], &CRect(op[3]->x + 12 - 10, op[3]->y - 10, op[3]->x + 12 + 10, op[3]->y + 10), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	

	for (int i = 0; i < 4; i++) {
		op[i]->onDraw(pDC);
	}
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
		decision.judge = judge;
		decision.DoModal();
		return 1;
	}
	return 0;
}

int decision_box::onBuild(std::queue<object*>* q, Analyze* analyze) {
	//error = false;

	int innum = 0;
	/*int outnum = 0;*/
	for (int i = 0; i < 4; i++) {
		if (op[i]->toward == 1)
			innum++;
		/*else if (op[i]->toward == 2)
			outnum++;*/
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

	/*if (outnum != 1) {
		error = true;
		for (int i = 0; i < 4; i++) {
			if (op[i]->toward == 2)
				op[i]->al->error = true;
		}
	}*/

	if (error) return 1;

	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += judge[i];
	}
	if (sum != 3) {
		error = true;
		return 1;
	}

	int re=analyze->inspectStr(str);
	if (re > 0) {
		error = true;
		return re;
	}
	return 0;
}

int decision_box::onRuning(object** obj, Analyze* analyze) {
	analyze->inspectStr(str);
	int num=analyze->calculate()->num;

	for (int i = 0; i < 4; i++) {
		if (judge[i]==num+1) {
			*obj = op[i]->al->o_out;
			op[i]->al->run = true;
			break;
		}
	}

	run = true;

	return 0;
}

std::string decision_box::onSave() {
	std::string str = "";
	std::stringstream ss;
	ss << type << " " << getID() << " " << left << " " << up << " " << right << " " << down << " " << color << " " << width << std::endl;
	for (int i = 0; i < 4; i++) {
		ss << judge[i]<<" ";
	}
	ss << std::endl;
	if (this->str == "")
		ss << "-1";
	else
		ss << this->str;
	ss << std::endl;
	str = ss.str();
	return str;
}

int decision_box::onRead(std::ifstream &in) {
	char temp[80];
	in.getline(temp, sizeof(temp));
	std::stringstream ss(temp);
	for (int i = 0; i < 4; i++) {
		ss >> judge[i];
	}
	in.getline(temp, sizeof(temp));
	std::string tem = temp;
	if (tem != "-1")
		this->str = tem;
	return 0;
}
