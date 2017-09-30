/*
 * guiHome.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#include <guiHome.h>
#include <guiListAlbum.h>
#include "tools.h"

guiHome::guiHome() {
	_renderer = NULL;
	butAlbum = NULL;
	butplaylist = NULL;
	butHomeControl = NULL;
	butPlayer = NULL;
}

guiHome::guiHome(SDL_Renderer *renderer) {

	_renderer = renderer;
	// TODO Auto-generated constructor stub
	butAlbum = new guiButton(_renderer, 75, 75, 150, 150, "res/album.png");
	butplaylist = new guiButton(_renderer, 375, 75, 150, 150, "res/playlist.png");
	butPlayer = new guiButton(_renderer, 75, 375, 150, 150, "res/player.png");
	butHomeControl = new guiButton(_renderer, 75, 800, 150, 150, "res/homecontrol.png");

	AddChild(butAlbum);
	AddChild(butplaylist);
	AddChild(butPlayer);
	AddChild(butHomeControl);

	wndAlbum = new guiListAlbum(renderer);
	wndAlbum->setRect(0, 0, 600, 1024);

	wndPlaylist = new guiListPlaylist(renderer);
	wndPlaylist->setRect(0, 0, 600, 1024);

	wndHomeControl = new guiHomeControl(renderer);
	wndHomeControl->setRect(0, 0, 600, 1024);

	wndPlayer = new guiPlayer(renderer);
	wndPlayer->setRect(0, 0, 600, 1024);

	_gblPlayer = wndPlayer;

	//wndAlbum->sort();
}

guiHome::~guiHome() {
	// TODO Auto-generated destructor stub
}

void guiHome::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (butAlbum->isClicked())
		setActiveWindows(wndAlbum);

	if (butplaylist->isClicked())
		setActiveWindows(wndPlaylist);

	if (butHomeControl->isClicked())
		setActiveWindows(wndHomeControl);

	if (butPlayer->isClicked())
		setActiveWindows(wndPlayer);
}
