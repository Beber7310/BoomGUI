/*
 * guiButton.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */
#include <stdio.h>
#include <string.h>
#include <guiButton.h>

guiButton::guiButton() {
	// TODO Auto-generated constructor stub

}

guiButton::guiButton(int x, int y, int w, int h, char *szImg) {
	// TODO Auto-generated constructor stub
	/*
	 SDL_Surface * image = IMG_Load(szImg);
	 _texButton = SDL_CreateTextureFromSurface(renderer, image);
	 SDL_FreeSurface(image);
	 */
	_texButton = IMG_LoadTexture(_renderer, szImg);

	SDL_SetTextureBlendMode(_texButton, SDL_BLENDMODE_BLEND);
	if (strlen(SDL_GetError()) > 3) {
		printf("Error catch in guiButton: %s\n", SDL_GetError());
		SDL_ClearError();
	}
	_relWndRect.x = x;
	_relWndRect.y = y;
	_relWndRect.w = w;
	_relWndRect.h = h;
	_click = 0;
	_enabled = true;
}

guiButton::~guiButton() {
	// TODO Auto-generated destructor stub
}

void guiButton::render() {
	if (_enabled) {
		computeClipping();
		SDL_RenderCopy(_renderer, _texButton, NULL, &_absWndRect);
	}
}

bool guiButton::enable(bool on) {
	_enabled = on;
	return false;
}

bool guiButton::isClicked() {
	if (_click == 4) {
		_click = 0;
		return true;
	}
	return false;
}

void guiButton::event(int x, int y, int button) {
	if (_enabled) {
		_click = button;
	} else {
		_click = 0;
	}
}
