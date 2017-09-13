/*
 * guiBase.cpp
 *
 *  Created on: 5 sept. 2017
 *      Author: Bertrand
 */

#include <stdio.h>
#include "string.h"
#include "guiBase.h"

SDL_Renderer *guiBase::_renderer;

guiBase::guiBase() {
	_pParent = NULL;

	_relWndRect.x = 0;
	_relWndRect.y = 0;
	_relWndRect.w = 600;
	_relWndRect.h = 1024;

	_absWndRect.x = 0;
	_absWndRect.y = 0;
	_absWndRect.w = 600;
	_absWndRect.h = 1024;
	_sortName = NULL;
}

guiBase::guiBase(int x, int y, int w, int h) {
	_pParent = NULL;

	_relWndRect.x = x;
	_relWndRect.y = y;
	_relWndRect.w = w;
	_relWndRect.h = h;

	_absWndRect.x = 0;
	_absWndRect.y = 0;
	_absWndRect.w = 200;
	_absWndRect.h = 200;
	_sortName = NULL;
}

void guiBase::setRect(int x, int y, int w, int h) {
	_relWndRect.x = x;
	_relWndRect.y = y;
	_relWndRect.w = w;
	_relWndRect.h = h;
}

guiBase::~guiBase() {
	// TODO Auto-generated destructor stub
}

void guiBase::sort() {
	// TODO Auto-generated destructor stub
	_lstWnd.sort(
			[](const guiBase* a, const guiBase* b) {return (strcmp( a->_sortName, b->_sortName)<0);});

}

void guiBase::AddChild(guiBase * pWin) {
	pWin->_pParent = this;
	_lstWnd.push_back(pWin);
}

guiBase *
guiBase::GetFirstChild(std::list<guiBase*>::iterator* it) {
	*it = _lstWnd.begin();
	return _lstWnd.front();
}
guiBase *
guiBase::GetNextChild(std::list<guiBase*>::iterator* it) {
	(*it)++;
	if ((*it) != _lstWnd.end())
		return (guiBase*) ((**it));
	else
		return NULL;
}

void guiBase::render(SDL_Renderer *renderer) {
	guiBase * pTemp;

	SDL_RenderSetClipRect(renderer, &_absWndRect);

	boxRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0,
			0x0, 0x00, 0xFF);
	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,
			0xFF, 0xFF, 0xFF);

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


}

void guiBase::event(int x, int y, int button) {

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
