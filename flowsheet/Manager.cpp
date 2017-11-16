#include "stdafx.h"
#include "Manager.h"
#include "unit.h"
#include <set>
#include <queue>
#include <sstream>

Manager::Manager() :tb(0, 80) {
	line_establish = false;
	current_ID = 0;
}

void Manager::onDraw(CDC* pDC) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		temp->onDraw(pDC);
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		temp->onDraw(pDC);
	}

	tb.onDraw(pDC);
}

int Manager::onPress(int x, int y) {
	int retu = 0;

	int re = tb.onPress(x, y);
	if (re != 0) {
		int tempid = IDARRAY[re - 1];		//ȡ��re��ͼԪ��ť����Ӧ��ͼԪ����ID
		re = addobject(tempid, x, y);
		if (re == 1) {						//�����ɹ�
			unitArray.back()->hold = true;	//������ק
			unitArray.back()->curse = true;	//ӵ�н���
			retu = 1;
		}
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		int re = temp->onPress(x, y);
		if(re!=0) retu = re;
	}

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int re = temp->onPress(x, y);
		if (re == 0) {				//ɶ��û�㵽
			continue;
		}
		else if (re == 1) {			//�㵽ͼ��
			retu = 1;
		}
		else {						//�㵽���ӵ�,re-2����㵽op[re-2]���ӵ�
			if (temp->op[re - 2]->toward == 0) {		//֮ǰ������ӵ�û������������
				//ǿ�ƶ���
				addline(temp->op[re - 2]->x, temp->op[re - 2]->y);
				
				connectOToL(temp, re - 2, lineArray.back(), 1);
				line_establish = true;
				retu = re;
			}
		}
	}

	return retu;
}

int Manager::onMove(int dx, int dy) {
	/*for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		int r = temp->onMove(x, y);
		if (r) return 1;
	}*/
	if (line_establish) {			//��ǰ�����ڱ������е�����
		lineArray.back()->change_d(2,dx, dy);			//�ı���޸����ߵ�λ��
		return 1;					//���»���
	}

	int re = 0;
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->onMove(dx, dy))
			re = 1;		//���»���
			
	}

	return re;
}

int Manager::onRelease(int x,int y) {
	bool judge = false;		//�ж��ͷ��ͷ������ӵ���

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int re=temp->onRelease(x,y);
		if (re != 0) {		//����ͷŵ�λ����objectpoint,re-1�����ͷŵ�λ����op[re-1]���ӵ�
			//ǿ�ƶ���
			lineArray.back()->change(2, temp->op[re - 1]->x, temp->op[re - 1]->y);
			
			if (temp->op[re - 1]->toward == 0) {
				connectOToL(temp, re - 1, lineArray.back(), 2);
				judge = true;
			}
		}
	}

	if (line_establish) {
		arrowline* altemp = lineArray.back();
		altemp->curse = true;
		if (altemp->o_in->op[altemp->num_in]->onRelease(x,y)) {
			deleteline(current_ID - 1);		//ɾ�����ڴ�����������
		}
		else if (judge==false) {			//������ʱ��û����������ͼԪ��ȡ������
			deleteline(current_ID - 1);		//ɾ�����ڴ�����������
		}
		line_establish = false;
	}

	
	return 1;								//���»���

	/*for (std::vector<object*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		object* temp = *it;
		temp->onRelease(x,y);
	}*/
}

int Manager::onDBclick(int x, int y) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		temp->onDBclick(x, y);
	}
	return 0;
}

int Manager::onBuild() {
	onClearBuild();
	bool pass = true;

	bool startexist = false;
	//bool endexist = false;
	object* start;
	/*object* end;*/
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->type == START_ID) {
			if (!startexist) {
				startexist = true;
				start = temp;
			}
			else {
				pass = false;
			}
		}
		/*else if (temp->type == END_ID) {
			if (!endexist) {
				endexist = true;
				end = temp;
			}
			else {
				pass = false;
			}
		}*/
	}

	if (!pass) {					//����һ����ʼ��
		for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
			object* temp = *it;
			if (temp->type == START_ID) {
				temp->error = true;
			}
		}
		return 1;
	}
	if (!startexist) return 1;	//û�п�ʼ��

	
	std::set<int> idset;
	std::queue<object*> Queue;
	//if (end->onBuild(&Queue)) return 1;		//������������
	Queue.push(start);
	while (Queue.size() != 0) {
		object* temp = Queue.front();
		Queue.pop();
		if (idset.find(temp->getID()) == idset.end()) {
			idset.insert(temp->getID());
			if (temp->onBuild(&Queue,&analyze)) {		//���������
				pass = false;
			}
		}
		
	}

	if (!pass) return 1;		//�������
	return 0;				//����ͨ��
}

int Manager::onClearBuild() {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		temp->error = false;
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		temp->error = false;
	}
	return 0;
}

int Manager::onRuning() {
	onClearRuning();

	if (onBuild())
		return 1;

	object* obj;
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->type == START_ID) {
			obj = temp;
			break;
		}
	}

	while (obj != NULL) {
		object* temp;
		obj->onRuning(&temp,&analyze);
		obj = temp;
	}
	return 0;
}

int Manager::onClearRuning() {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if ((*it)->type == OUTPUT_ID) {
			((output_box*)(*it))->show = false;
		}
		temp->error = false;
		temp->run = false;
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		temp->error = false;
		temp->run = false;
	}

	Analyze::identable.clear();
	return 0;
}

int Manager::onSave(std::ofstream& out) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		out << temp->onSave() ;
	}
	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		out << temp->onSave() ;
	}
	return 0;
}

int Manager::onOpen(std::ifstream& in) {
	onClear();

	int maxid = 0;
	while (!in.eof()) {
		char temp[80];
		in.getline(temp, sizeof(temp));
		if (strcmp(temp, "") == 0) {
			break;
		}
		std::stringstream ss(temp);
		int type, id, l, u, r, d, c, w;
		ss >> type >> id >> l >> u >> r >> d >> c >> w;
		maxid = maxid < id ? id : maxid;
		object* t;
		switch (type) {
		case START_ID:
			t = new start_box(id, l, u, r - l, d - u, c, w);
			t->onRead(in);
			unitArray.push_back(t);
			break;
		case END_ID:
			t = new end_box(id, l, u, r - l, d - u, c, w);
			t->onRead(in);
			unitArray.push_back(t);
			break;
		case INPUT_ID:
			t = new input_box(id, l, u, r - l, d - u, c, w);
			t->onRead(in);
			unitArray.push_back(t);
			break;
		case OUTPUT_ID:
			t = new output_box(id, l, u, r - l, d - u, c, w);
			t->onRead(in);
			unitArray.push_back(t);
			break;
		case PROCESS_ID:
			t = new process_box(id, l, u, r - l, d - u, c, w);
			t->onRead(in);
			unitArray.push_back(t);
			break;
		case DECISION_ID:
			t = new decision_box(id, l, u, r - l, d - u, c, w);
			t->onRead(in);
			unitArray.push_back(t);
			break;
		case ARROWLINE_ID:
			arrowline* a = new arrowline(id, l, u, r, d, c, w);
			lineArray.push_back(a);
			int id1, id2, op1, op2;

			in.getline(temp, sizeof(temp));
			std::stringstream ss1(temp);
			ss1 >> id1 >> op1;
			object* o1 = findID(id1);
			connectOToL(o1, op1, a, 1);

			in.getline(temp, sizeof(temp));
			std::stringstream ss2(temp);
			ss2 >> id2 >> op2;
			object* o2 = findID(id2);
			connectOToL(o2, op2, a, 2);

			break;
		}
	}
	return 0;
}

int Manager::onClear() {
	unitArray.clear();
	lineArray.clear();
	current_ID = 0;
	line_establish = false;
	return 0;
}

int Manager::findCurse(int &id) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->curse) {
			id = temp->getID();
			return 1;	//�ҵ�����ͼԪ
		}
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		if (temp->curse) {
			id = temp->getID();
			return 2;	//�ҵ�����������
		}
	}

	return 0;			//û�ҵ�
}

object* Manager::findID(int id) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->getID() == id)
			return temp;
	}
	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		if (temp->getID() == id)
			return temp;
	}
	return NULL;
}

int Manager::onKey(int ch) {
	switch (ch) {
	case 46:
		int id;
		int type=findCurse(id);
		if (type == 1) deleteobject(id);
		else if (type == 2)deleteline(id);
		else break;
		return 1;			//��Ҫ���»���
	}
	return 0;
}

int Manager::addobject(int object_ID, int x, int y, int color, int width) {
	object* temp = onCreate(object_ID, x, y, color, width);
	if (temp != NULL) {
		unitArray.push_back(temp);
		return 1;
	}
	return 0;
}

int Manager::addline(int x1, int y1, int color, int width) {
	arrowline* temp=(arrowline*)onCreate(ARROWLINE_ID, x1, y1, color, width);//������һ����
	if (temp != NULL) {
		lineArray.push_back(temp);
		return 1;
	}
	return 0;
}

void Manager::deleteobject(int ID) {		//ɾ��ָ��ID��ͼԪ
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->getID()==ID) {
			for (int i = 0; i < 4; i++) {
				if(temp->op[i]->al!=NULL)
					deleteline(temp->op[i]->al->getID());
			}
			it = unitArray.erase(it);
			return;
		}
	}
}

void Manager::deleteline(int ID) {		//ɾ��ָ��ID��������
	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		if (temp->getID() == ID) {
			temp->deleteline();					//ɾ��ָ������������ͼԪ��4�����ӵ�������Ϣ
			it = lineArray.erase(it);
			return;
		}
	}
}

void Manager::connectOToL(object* o, int opid, arrowline* l, int lpid) {
	o->op[opid]->al = l;
	o->op[opid]->toward = lpid;

	if (lpid == 1) {
		l->o_in = o;
		l->num_in = opid;
	}
	else if (lpid == 2) {
		l->o_out = o;
		l->num_out = opid;
	}
}

object* Manager::onCreate(int object_ID, int x, int y, int color, int width) {
	switch (object_ID) {
	case START_ID:
		return new start_box(current_ID++, x, y, color, width);
	case END_ID:
		return new end_box(current_ID++, x, y, color, width);
	case INPUT_ID:
		return new input_box(current_ID++, x, y, color, width);
	case OUTPUT_ID:
		return new output_box(current_ID++, x, y, color, width);
	case PROCESS_ID:
		return new process_box(current_ID++, x, y, color, width);
	case DECISION_ID:
		return new decision_box(current_ID++, x, y, color, width);
	case ARROWLINE_ID:
		return new arrowline(current_ID++, x, y, x+1, y+1, color, width);
	}
	return NULL;
}
