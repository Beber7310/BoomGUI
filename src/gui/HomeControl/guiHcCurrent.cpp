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

guiHcCurrent::guiHcCurrent(SDL_Renderer *renderer, char* name) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	sprintf(_Name, "%s", name);

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 200;

	wndBtnOn = new guiButton(renderer, 200, 100, 100, 100, "res/back.png");
	AddChild(wndBtnOn);

	wndBtnOff = new guiButton(renderer, 0, 100, 100, 100, "res/back.png");
	AddChild(wndBtnOff);

	SDL_Color couleurTexte = { 255, 255, 255, 255 };
	SDL_Surface* texteAlb = TTF_RenderText_Blended_Wrapped(_police2, _Name,
			couleurTexte, 500);
	_textAlbum = SDL_CreateTextureFromSurface(renderer, texteAlb);
	SDL_FreeSurface(texteAlb);
	SDL_QueryTexture(_textAlbum, NULL, NULL, &_textSize.w, &_textSize.h);
}

guiHcCurrent::~guiHcCurrent() {
	// TODO Auto-generated destructor stub
}

void guiHcCurrent::render(SDL_Renderer *renderer) {
	computeClipping(renderer);
	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,0xFF, 0xFF, 0xFF);

	char szTmp[32];
	sprintf(szTmp,"%3.1f",hcGetCourant());
	stringRGBA(renderer,500,_absWndRect.y+20,szTmp,0xFF,0xFF,0xFF,0xFF);

	_textSize.x = 25;
	_textSize.y = _absWndRect.y;
	SDL_RenderCopy(renderer, _textAlbum, NULL, &_textSize);

}

void guiHcCurrent::event(int x, int y, int button) {
	guiBase::event(x, y, button);



}
