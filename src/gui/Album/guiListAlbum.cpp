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

guiListAlbum::guiListAlbum(SDL_Renderer *renderer) {
	// TODO Auto-generated constructor stub

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, 600, 924);
	wndAlbFlt = new guiAlbumFilter(renderer);
	toolsLoadAlbum(renderer, wndLstAlb, wndAlbFlt);
	wndLstAlb->sort();

	wndBtnBack = new guiButton(renderer, 0, 0, 100, 100, "res/back.png");
	wndBtnFilter = new guiButton(renderer, 500, 0, 100, 100, "res/filter.png");

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

