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

guiHcLight::guiHcLight(SDL_Renderer *renderer, char* name, int index) {
	// TODO Auto-generated constructor stub

	_Name = (char*) malloc(strlen(name) + 10);
	_index = index;
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

guiHcLight::~guiHcLight() {
	// TODO Auto-generated destructor stub
}

void guiHcLight::render(SDL_Renderer *renderer) {
	computeClipping(renderer);

	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,0xFF, 0xFF, 0xFF);


	_textSize.x = 25;
	_textSize.y = _absWndRect.y;
	SDL_RenderCopy(renderer, _textAlbum, NULL, &_textSize);

}

void guiHcLight::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnOn->isClicked())
	{

		hcSetLight(_index,true);
	}
	if (wndBtnOff->isClicked())
	{

		hcSetLight(_index,false);
	}

}
