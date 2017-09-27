/*
 * guiItemFilter.cpp
 *
 *  Created on: 15 sept. 2017
 *      Author: Bertrand
 */


#include <string.h>
#include <stdlib.h>

#include "guiItemFilter.h"

guiItemFilter::guiItemFilter() {
	// TODO Auto-generated constructor stub
	_szGenre = NULL;
	_selected = true;
}

guiItemFilter::guiItemFilter(SDL_Renderer *renderer, char* genre) {
	// TODO Auto-generated constructor stub
	_szGenre = NULL;
	_selected = true;
	_click = 0;

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 100;

	if (genre) {
		_szGenre = (char*) malloc(strlen(genre) + 1);
		strcpy(_szGenre, genre);
	} else {
		_szGenre = (char*) malloc(strlen("TBD") + 1);
		strcpy(_szGenre, "TBD");
	}
	_sortName = (char*) malloc(strlen(_szGenre) + 1);
	strcpy(_sortName, genre);


	SDL_Color couleurTexte = { 255, 255, 255, 255 };
	SDL_Surface* texteFilt = TTF_RenderUTF8_Blended_Wrapped(_police2, _szGenre,couleurTexte, 600);
	_textFilter = SDL_CreateTextureFromSurface(renderer, texteFilt);
	SDL_FreeSurface(texteFilt);
	SDL_QueryTexture(_textFilter, NULL, NULL, &_textSize.w, &_textSize.h);
}

void guiItemFilter::render(SDL_Renderer *renderer) {
	SDL_Rect coverRect;

	// SDL_RenderSetClipRect (renderer, &_absWndRect);

	boxRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0,
			0x0, 0x00, 0xFF);
	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,
			0xFF, 0xFF, 0xFF);
	if (_selected)
		stringRGBA(renderer, _absWndRect.x + 500,
				_absWndRect.y + _absWndRect.h / 4, _szGenre, 0xFF, 0xFF, 0xFF,
				0xFF);
	else
		stringRGBA(renderer, _absWndRect.x + 500,
				_absWndRect.y + _absWndRect.h / 4, _szGenre, 0x80, 0x80, 0x80,
				0xFF);

	_textSize.x=15;
	_textSize.y=_absWndRect.y;
	SDL_RenderCopy(renderer, _textFilter, NULL, &_textSize);
}

guiItemFilter::~guiItemFilter() {
	// TODO Auto-generated destructor stub
}

void guiItemFilter::event(int x, int y, int button) {
	/*	if (button == 4)
	 _selected = !_selected;*/
	_click = button;
}

bool guiItemFilter::isClicked() {
	if (_click == 4) {
		_click = 0;
		return true;
	}
	return false;
}
