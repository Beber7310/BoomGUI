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

guiHcRadiateur::guiHcRadiateur(SDL_Renderer *renderer, char* name, int index) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	_index = index;
	sprintf(_Name, "%s", name);

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 200;
	_targetTemp = 0;

	wndBtnPlus = new guiButton(renderer, 200, 100, 100, 100, "res/plus.png");
	AddChild(wndBtnPlus);

	wndBtnMinus = new guiButton(renderer, 0, 100, 100, 100, "res/minus.png");
	AddChild(wndBtnMinus);

	SDL_Color couleurTexte = { 255, 255, 255, 255 };
	SDL_Surface* texteAlb = TTF_RenderText_Blended_Wrapped(_police2, _Name,
			couleurTexte, 500);
	_textAlbum = SDL_CreateTextureFromSurface(renderer, texteAlb);
	SDL_FreeSurface(texteAlb);
	SDL_QueryTexture(_textAlbum, NULL, NULL, &_textSize.w, &_textSize.h);
}

guiHcRadiateur::~guiHcRadiateur() {
	// TODO Auto-generated destructor stub
}

void guiHcRadiateur::render(SDL_Renderer *renderer) {
	guiBase * pTemp;

	computeClipping(renderer);
	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp) {
		pTemp->_absWndRect.x = _absWndRect.x + pTemp->_relWndRect.x;
		pTemp->_absWndRect.y = _absWndRect.y + pTemp->_relWndRect.y;
		pTemp->_absWndRect.w = pTemp->_relWndRect.w;
		pTemp->_absWndRect.h = pTemp->_relWndRect.h;

		pTemp->render(renderer);
		pTemp = GetNextChild(&it);
	}
	computeClipping(renderer);
	char szTmp[32];
	sprintf(szTmp, "%3.1f", hcGetTemp(_index));
	stringRGBA(renderer, 500, _absWndRect.y + 20, szTmp, 0xFF, 0xFF, 0xFF,
			0xFF);

	_targetTemp = hcGetTargetTemp(_index);
	sprintf(szTmp, "%3.1f", _targetTemp);
	stringRGBA(renderer, 100, _absWndRect.y + 100, szTmp, 0xFF, 0xFF, 0xFF,
			0xFF);

	_textSize.x = 25;
	_textSize.y = _absWndRect.y;
	SDL_RenderCopy(renderer, _textAlbum, NULL, &_textSize);

	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,
			0xFF, 0xFF, 0xFF);
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
