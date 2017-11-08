#include "stdafx.h"
#include "objectManager.h"

objectManager::objectManager() {
	
}

void objectManager::onDraw(CDC* pDC) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		temp->onDraw(pDC);
	}

	for (std::vector<object*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		object* temp = *it;
		temp->onDraw(pDC);
	}
}

int objectManager::onPress(int x, int y) {
	for (std::vector<object*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		object* temp = *it;
		int r = temp->onPress(x, y);
		if (r) return 1;
	}

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int r = temp->onPress(x, y);
		if (r) return 1;
	}

	return 0;
}

int objectManager::onMove(int x, int y) {
	for (std::vector<object*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		object* temp = *it;
		int r = temp->onMove(x, y);
		if (r) return 1;
	}

	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		int r = temp->onMove(x, y);
		if (r) return 1;
	}

	return 0;
}

void objectManager::onRelease(int x,int y) {
	for (std::vector<object*>::iterator it = unitArray.begin(); it != unitArray.end(); it++) {
		object* temp = *it;
		temp->onRelease(x,y);
	}

	for (std::vector<object*>::iterator it = lineArray.begin(); it != lineArray.end(); it++) {
		object* temp = *it;
		temp->onRelease(x,y);
	}
}

object* objectManager::onCreate(int object_ID,int x=0,int y=0,int w=0,int h=0,int color= RGB(255, 255, 255),int width=1) {
	switch (object_ID) {
	case 1:
		return new start(x, y, w, h, color, width);
	case 2:
		return new end(x, y, w, h, color, width);
	case 3:
		return new arrowline(x, y, w, h, 30, 5, color, width);
	}
}
