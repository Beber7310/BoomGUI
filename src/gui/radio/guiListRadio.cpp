/*
 * guiListRadio.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include <radio/guiItemRadio.h>
#include "guiListRadio.h"
#include "guiAlbumFilter.h"
#include "guiManager.h"
#include "tools.h"
#include "configuration.h"

guiListRadio::guiListRadio() {
	// TODO Auto-generated constructor stub

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, SCREEN_WIDTH, SCREEN_HEIGHT-100);
	//toolsLoadAlbum(_renderer, wndLstAlb, wndAlbFlt);
	toolsLoadRadio(_renderer, wndLstAlb);
	wndLstAlb->sort();

	wndBtnBack = new guiButton( 0, 0, 100, 100, "res/back.png");

	AddChild(wndBtnBack);
	AddChild(wndLstAlb);
}

guiListRadio::~guiListRadio() {
	// TODO Auto-generated destructor stub
}

void guiListRadio::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

}


