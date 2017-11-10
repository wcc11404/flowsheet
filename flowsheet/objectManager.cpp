#include "stdafx.h"
#include "objectManager.h"

objectManager::objectManager() {
	unitArray.push_back(onCreate(1, 50, 50, 50, 50));
	unitArray.push_back(onCreate(2, 150, 150, 50, 50));

	line_establish = false;
	current_ID = 0;
}

void objectManager::onDraw(CDC* pDC) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		temp->onDraw(pDC);
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		temp->onDraw(pDC);
	}
}

int objectManager::onPress(int x, int y) {
	/*for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		int r = temp->onPress(x, y);
		if (r) return 1;
	}*/

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int re = temp->onPress(x, y);
		if (re == 0) {				//啥都没点到
			continue;
		}
		else if (re == 1) {			//点到图形
			return 1;
		}
		else {						//点到连接点,re-2代表点到op[re-2]连接点
			if (temp->op[re - 2]->toward == 0) {		//之前这个连接点没有连接线连接
				//强制对齐
				lineArray.push_back((arrowline*)onCreate(3, temp->op[re - 2]->x, temp->op[re - 2]->y, temp->op[re - 2]->x, temp->op[re - 2]->y));//创建出一条线
				
				connectOToL(temp, re - 2, lineArray.back(), 1);
				line_establish = true;
				return re;
			}
		}
	}

	return 0;
}

int objectManager::onMove(int dx, int dy) {
	/*for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		int r = temp->onMove(x, y);
		if (r) return 1;
	}*/
	if (line_establish) {			//当前有正在被创建中的连线
		lineArray[lineArray.size() - 1]->change(2,dx, dy);			//改变待修改连线的位置
		return 1;					//更新画面
	}

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int r = temp->onMove(dx, dy);
		if (r) return 1;			//更新画面
	}

	return 0;
}

int objectManager::onRelease(int x,int y) {
	bool judge = false;		//判断释放释放在连接点上

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int re=temp->onRelease(x,y);
		if (re != 0) {		//如果释放的位置是objectpoint,re-1代表释放的位置是op[re-1]连接点
			//强制对齐
			lineArray.back()->change(2, temp->op[re - 1]->x - lineArray.back()->right, temp->op[re - 1]->y - lineArray.back()->down);
			
			connectOToL(temp, re - 1, lineArray.back(), 2);
			judge = true;
		}
	}

	if (line_establish) {
		arrowline* altemp = lineArray.back();
		if (altemp->o_in->op[altemp->num_in]->onRelease(x,y)) {
			deleteline(current_ID - 1);		//删除正在创建的连接线
		}
		else if (judge==false) {			//创建线时，没有连接两个图元，取消创建
			deleteline(current_ID - 1);		//删除正在创建的连接线
		}
		line_establish = false;
		return 1;							//更新画面
	}
	return 0;

	/*for (std::vector<object*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		object* temp = *it;
		temp->onRelease(x,y);
	}*/
}

int objectManager::findCurse(int &id) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		if (temp->curse) {
			id = temp->getID();
			return 1;	//找到的是图元
		}
	}

	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		if (temp->curse) {
			id = temp->getID();
			return 2;	//找到的是连接线
		}
	}

	return 0;			//没找到
}

int objectManager::onKey(int ch) {
	switch (ch) {
	case 46:
		int id;
		int type=findCurse(id);
		if (type == 1) deleteobject(id);
		else if (type == 2)deleteline(id);
		else break;
		return 1;			//需要更新画面
	}
	return 0;
}

void objectManager::deleteobject(int ID) {		//删除指定ID的图元
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

void objectManager::deleteline(int ID) {		//删除指定ID的连接线
	for (std::vector<arrowline*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		arrowline* temp = *it;
		if (temp->getID() == ID) {
			temp->deleteline();					//删除指定连接线两段图元的4个连接点的相关信息
			it = lineArray.erase(it);
			return;
		}
	}
}

void objectManager::connectOToL(object* o, int opid, arrowline* l, int lpid) {
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

object* objectManager::onCreate(int object_ID, int x, int y, int w, int h, int color, int width) {
	switch (object_ID) {
	case 1:
		return new start(current_ID++,x, y, w, h, color, width);
	case 2:
		return new end(current_ID++, x, y, w, h, color, width);
	case 3:
		return new arrowline(current_ID++, x, y, w, h, 30, 12, color, width);
	}
}
