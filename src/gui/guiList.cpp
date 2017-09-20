/*
 * guiList.cpp
 *
 *  Created on: 8 sept. 2017
 *      Author: Bertrand
 */

#include "guiList.h"

guiList::guiList() {
	// TODO Auto-generated constructor stub
	_offset1 = 0;
	_offset2 = 0;
	_contentHeight = 0;
	_firstYmousse = 0;
}

guiList::~guiList() {
	// TODO Auto-generated destructor stub
}

void guiList::render(SDL_Renderer *renderer) {
	guiBase * pTemp;
	int lastAbsPosY = _offset1 + _offset2;

	SDL_RenderSetClipRect(renderer, &_absWndRect);

	boxRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0,
			0x0, 0x00, 0xFF);
	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,
			0xFF, 0xFF, 0xFF);
	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	_contentHeight = 0;
	SDL_RenderSetClipRect(renderer, &_absWndRect);
	while (pTemp) {

		pTemp->_relWndRect.y = lastAbsPosY;
		lastAbsPosY = pTemp->_relWndRect.y + pTemp->_relWndRect.h;

			pTemp->_absWndRect.x = _absWndRect.x;
			pTemp->_absWndRect.y = _absWndRect.y + pTemp->_relWndRect.y;
			pTemp->_absWndRect.w = _relWndRect.w;
			pTemp->_absWndRect.h = pTemp->_relWndRect.h;
			_contentHeight += pTemp->_relWndRect.h;
			pTemp->render(renderer);

		pTemp = GetNextChild(&it);
	}

	if (_offset1 < -(_contentHeight - _relWndRect.h))
		_offset1 = -(_contentHeight - _relWndRect.h);
	if (_offset1 > 0)
		_offset1 = 0;


	SDL_RenderSetClipRect(renderer, NULL);
}

void guiList::event(int x, int y, int button) {
	if (button == 1) {
		_firstYmousse = y;
	}
	if (button == 2) {
		_offset2 = y - _firstYmousse;
	}
	if (button == 3) {
		_offset1 += _offset2;
		_offset2 = 0;
	}

	guiBase * pTemp;
	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp) {
		if (x > pTemp->_relWndRect.x && y > pTemp->_relWndRect.y
				&& x < (pTemp->_relWndRect.x + pTemp->_relWndRect.w)
				&& y < (pTemp->_relWndRect.y + pTemp->_relWndRect.h)) {
			pTemp->event(x - pTemp->_relWndRect.x, y - pTemp->_relWndRect.y,
					button);
		}
		pTemp = GetNextChild(&it);
	}
}
