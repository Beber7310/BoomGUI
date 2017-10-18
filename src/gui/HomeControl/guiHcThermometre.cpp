/*
 * guiHcRadiateur.cpp
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <guiHcThermometre.h>
#include <SDL2_gfxPrimitives.h>
#include "homeControl.h"

guiHcThermometre::guiHcThermometre(char* name,int index) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	_index=index;
	sprintf(_Name, "%s", name);

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 100;

}

guiHcThermometre::~guiHcThermometre() {
	// TODO Auto-generated destructor stub
}


void guiHcThermometre::render() {
	SDL_Rect coverRect;

	computeClipping();

	//boxRGBA(_renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0,0x0, 0x00, 0xFF);
	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,0xFF, 0xFF, 0xFF);

	char szTmp[32];
	sprintf(szTmp,"%3.1f",hcGetTemp(_index));
	stringRGBA(_renderer,500,_absWndRect.y+20,szTmp,0xFF,0xFF,0xFF,0xFF);
	_font2->print(szTmp,300,_absWndRect.y);

	_font2->print(_Name,25,_absWndRect.y);

}
