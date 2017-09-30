/*
 * guiButton.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */
#include <stdio.h>
#include <guiButton.h>

guiButton::guiButton() {
	// TODO Auto-generated constructor stub

}

guiButton::guiButton(SDL_Renderer * renderer, int x, int y, int w, int h,
		char* szImg) {
	// TODO Auto-generated constructor stub
	SDL_Surface * image = IMG_Load(szImg);
	_texButton = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	_relWndRect.x = x;
	_relWndRect.y = y;
	_relWndRect.w = w;
	_relWndRect.h = h;
}

guiButton::~guiButton() {
	// TODO Auto-generated destructor stub
}

void guiButton::render(SDL_Renderer *renderer) {
	computeClipping(renderer);

	boxRGBA(renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0,0x0, 0x00, 0xFF);
	//rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,0xFF, 0xFF, 0xFF);

	SDL_RenderCopy(renderer, _texButton, NULL, &_absWndRect);

}

bool guiButton::isClicked()
{
	if(_click==4)
	{
		_click=0;
		return true;
	}
	return false;
}

void guiButton::event(int x, int y, int button) {
	_click=button;
}
