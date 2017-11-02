/*
 * guiHcRadiateur.cpp
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <guiHcRadiateur.h>
#include <SDL2_gfxPrimitives.h>
#include "homeControl.h"

#include "configuration.h"

guiHcRadiateur::guiHcRadiateur( char* name, int index) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	_index = index;
	sprintf(_Name, "%s", name);

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = SCREEN_WIDTH;
	_relWndRect.h = 100;
	_targetTemp = 0;

	wndBtnPlus = new guiButton( SCREEN_WIDTH-100, 10, 80, 80, "res/plus.png");
	AddChild(wndBtnPlus);

	wndBtnMinus = new guiButton( SCREEN_WIDTH-200, 10, 80, 80, "res/minus.png");
	AddChild(wndBtnMinus);

}

guiHcRadiateur::~guiHcRadiateur() {
	// TODO Auto-generated destructor stub
}

void guiHcRadiateur::render() {
	guiBase * pTemp;
	char szTmp[32];

	computeClipping();
	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp) {
		pTemp->_absWndRect.x = _absWndRect.x + pTemp->_relWndRect.x;
		pTemp->_absWndRect.y = _absWndRect.y + pTemp->_relWndRect.y;
		pTemp->_absWndRect.w = pTemp->_relWndRect.w;
		pTemp->_absWndRect.h = pTemp->_relWndRect.h;

		pTemp->render();
		pTemp = GetNextChild(&it);
	}
	computeClipping();

	sprintf(szTmp, "%3.1f", hcGetTemp(_index));
	_font2->print(szTmp,SCREEN_WIDTH-300,_absWndRect.y);


	_targetTemp = hcGetTargetTemp(_index);
	sprintf(szTmp, "%3.1f", _targetTemp);
	_font2->print(szTmp,SCREEN_WIDTH-300,_absWndRect.y+30);

	_font2->print(_Name,25,_absWndRect.y);


	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);
}

void guiHcRadiateur::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnPlus->isClicked()) {
		_targetTemp += 1.0f;
		hcSetTargetTemp(_index, _targetTemp);
	}
	if (wndBtnMinus->isClicked()) {
		_targetTemp -= 1.0f;
		hcSetTargetTemp(_index, _targetTemp);
	}

}
