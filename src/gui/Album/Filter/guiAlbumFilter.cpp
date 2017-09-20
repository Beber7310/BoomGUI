/*
 * guiAlbumFilter.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: dosdab
 */

#include <guiAlbumFilter.h>
#include <guiItemFilter.h>
#include <string.h>

guiAlbumFilter::guiAlbumFilter() {

}

guiAlbumFilter::guiAlbumFilter(SDL_Renderer *renderer) {
	// TODO Auto-generated constructor stub
	_renderer=renderer;

	wndLstFlt = new guiList();
	wndLstFlt->setRect(0, 100, 600, 924);

	wndBtnBack = new guiButton(renderer, 0, 0, 100, 100, "res/back.jpg");

	AddChild(wndBtnBack);
	AddChild(wndLstFlt);



}

guiAlbumFilter::~guiAlbumFilter() {
	// TODO Auto-generated destructor stub
}

void guiAlbumFilter::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

	guiBase * pTemp;
	std::list<guiBase*>::iterator it;
	pTemp = wndLstFlt->GetFirstChild(&it);
	while (pTemp) {
		if (((guiItemFilter*) pTemp)->isClicked()) {
			if (((guiItemFilter*) pTemp)->_selected) {
				selectAll(false);
				((guiItemFilter*) pTemp)->_selected = true;
			} else {
				selectAll(true);
			}
		}
		pTemp = wndLstFlt->GetNextChild(&it);
	}
}

void guiAlbumFilter::selectAll(bool sel) {

	guiBase * pTemp;
	std::list<guiBase*>::iterator it;
	pTemp = wndLstFlt->GetFirstChild(&it);
	while (pTemp) {
		((guiItemFilter*) pTemp)->_selected = sel;
		pTemp = wndLstFlt->GetNextChild(&it);
	}
}

guiItemFilter* guiAlbumFilter::AddFilter(char* szGenre) {
	guiItemFilter* pTemp;
	std::list<guiBase*>::iterator it;

	if (!szGenre) {
		printf("guiAlbumFilter szGenre==NULL\n");
		return NULL;
	}
	if (strcmp(szGenre, "(null)") == 0) {
		szGenre = "_NA";
	}
	if (strcmp(szGenre, "") == 0) {
		szGenre = "_NA";
	}

	pTemp = (guiItemFilter*) wndLstFlt->GetFirstChild(&it);
	while (pTemp) {
		if (strcmp(pTemp->_szGenre, szGenre) == 0)
			return pTemp;
		pTemp = (guiItemFilter*) wndLstFlt->GetNextChild(&it);
	}

	pTemp = new guiItemFilter(_renderer,szGenre);
	wndLstFlt->AddChild(pTemp);

	return pTemp;

}
