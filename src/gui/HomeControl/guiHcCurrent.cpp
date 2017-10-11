/*
 * guiHcCurrent.cpp
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <guiHcCurrent.h>
#include <SDL2_gfxPrimitives.h>
#include "homeControl.h"

guiHcCurrent::guiHcCurrent(char* name) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	sprintf(_Name, "%s", name);

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 100;

	wndBtnOn = new guiButton(200, 100, 100, 100, "res/back.png");
	AddChild(wndBtnOn);

	wndBtnOff = new guiButton(0, 100, 100, 100, "res/back.png");
	AddChild(wndBtnOff);

}

guiHcCurrent::~guiHcCurrent() {
	// TODO Auto-generated destructor stub
}

void guiHcCurrent::render() {
	computeClipping();
	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

	char szTmp[32];
	sprintf(szTmp, "%3.1f", hcGetCourant());
	//stringRGBA(_renderer, 500, _absWndRect.y + 20, szTmp, 0xFF, 0xFF, 0xFF, 0xFF);

	_font2->print(_Name,25,_absWndRect.y);
	_font2->print(szTmp,500,_absWndRect.y + 20);
}

void guiHcCurrent::event(int x, int y, int button) {
	guiBase::event(x, y, button);

}
