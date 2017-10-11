/*
 * guiHcLight.cpp
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <guiHcLight.h>
#include <SDL2_gfxPrimitives.h>
#include "homeControl.h"

guiHcLight::guiHcLight(char* name, int index) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	_index = index;
	sprintf(_Name, "%s", name);

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 100;

	wndBtnOn = new guiButton( 500, 10, 80, 80, "res/on.png");
	AddChild(wndBtnOn);

	wndBtnOff = new guiButton( 400, 10, 80, 80, "res/off.png");
	AddChild(wndBtnOff);

}

guiHcLight::~guiHcLight() {
	// TODO Auto-generated destructor stub
}

void guiHcLight::render() {
	guiBase * pTemp;

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

	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);


	_font2->print(_Name,25,_absWndRect.y+20);
}

void guiHcLight::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnOn->isClicked()) {

		hcSetLight(_index, true);
	}
	if (wndBtnOff->isClicked()) {

		hcSetLight(_index, false);
	}

}
