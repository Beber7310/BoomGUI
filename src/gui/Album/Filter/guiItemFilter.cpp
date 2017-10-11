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


}

void guiItemFilter::render() {
	SDL_Rect coverRect;

	// SDL_RenderSetClipRect (renderer, &_absWndRect);

	boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);
	if (_selected)
		stringRGBA(_renderer, _absWndRect.x + 500, _absWndRect.y + _absWndRect.h / 4, _szGenre, 0xFF, 0xFF, 0xFF, 0xFF);
	else
		stringRGBA(_renderer, _absWndRect.x + 500, _absWndRect.y + _absWndRect.h / 4, _szGenre, 0x80, 0x80, 0x80, 0xFF);

	_font2->print(_szGenre, 15, _absWndRect.y);

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
