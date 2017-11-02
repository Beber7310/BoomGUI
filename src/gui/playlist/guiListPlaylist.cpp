/*
 * guiListPlaylist.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include <playlist/guiItemPlaylist.h>
#include "guiListPlaylist.h"
#include "guiAlbumFilter.h"
#include "guiManager.h"
#include "tools.h"
#include "configuration.h"

guiListPlaylist::guiListPlaylist() {
	// TODO Auto-generated constructor stub

	wndLstPlaylist = new guiList();
	wndLstPlaylist->setRect(0, 100, SCREEN_WIDTH, SCREEN_HEIGHT-100);
	toolsLoadPlaylist(_renderer, wndLstPlaylist);
	wndLstPlaylist->sort();

	wndBtnBack = new guiButton( 0, 0, 100, 100, "res/back.png");


	AddChild(wndBtnBack);
	AddChild(wndLstPlaylist);


}

guiListPlaylist::~guiListPlaylist() {
	// TODO Auto-generated destructor stub
}

void guiListPlaylist::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

}

