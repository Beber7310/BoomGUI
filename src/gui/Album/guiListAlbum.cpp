/*
 * guiListAlbum.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include "guiListAlbum.h"
#include "guiAlbumFilter.h"
#include "guiItemAlbum.h"
#include "guiManager.h"
#include "tools.h"

guiListAlbum::guiListAlbum() {
	// TODO Auto-generated constructor stub

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, 600, 924);
	wndAlbFlt = new guiAlbumFilter();
	toolsLoadAlbum(_renderer, wndLstAlb, wndAlbFlt);
	wndLstAlb->sort();

	wndBtnBack = new guiButton( 0, 0, 100, 100, "res/back.png");
	wndBtnFilter = new guiButton( 500, 0, 100, 100, "res/filter.png");

	AddChild(wndBtnBack);
	AddChild(wndBtnFilter);
	AddChild(wndLstAlb);

	wndAlbFlt->wndLstFlt->sort();
}

guiListAlbum::~guiListAlbum() {
	// TODO Auto-generated destructor stub
}

void guiListAlbum::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

	if (wndBtnFilter->isClicked())
		setActiveWindows(wndAlbFlt);

}
/*
void guiListAlbum::render() {
	guiBase * pTemp;

	computeClipping();
	SDL_RenderCopy(_renderer, _textWallPaper, NULL, NULL);
	//boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
	//rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,0xFF, 0xFF, 0xFF);

	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp) {
		pTemp->_absWndRect.x = _absWndRect.x + pTemp->_relWndRect.x;
		pTemp->_absWndRect.y = _absWndRect.y + pTemp->_relWndRect.y;
		pTemp->_absWndRect.w = pTemp->_relWndRect.w;
		pTemp->_absWndRect.h = pTemp->_relWndRect.h;

		pTemp->render();
		pTemp = GetNextChild(&it);
	}

	SDL_RenderSetClipRect(_renderer, NULL);
}*/

