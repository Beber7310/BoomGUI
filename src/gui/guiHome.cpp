/*
 * guiHome.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#include <configuration.h>
#include <guiHome.h>
#include <guiListAlbum.h>
#include "tools.h"



guiHome::guiHome() {

	// TODO Auto-generated constructor stub
	butAlbum = new guiButton( 75, 75, 150, 150, "res/album.png");
	butplaylist = new guiButton( 375, 75, 150, 150, "res/playlist.png");
	butPlayer = new guiButton( 75, 375, 150, 150, "res/player.png");
	butPodcast = new guiButton( 375, 375, 150, 150, "res/podcast.png");
	butHomeControl = new guiButton( 75, 800, 150, 150, "res/homecontrol.png");

	AddChild(butAlbum);
	AddChild(butplaylist);
	AddChild(butPlayer);
	AddChild(butPodcast);

	AddChild(butHomeControl);

	wndAlbum = new guiListAlbum();
	wndAlbum->setRect(0, 0, 600, 1024);

	wndPlaylist = new guiListPlaylist();
	wndPlaylist->setRect(0, 0, 600, 1024);

	wndPodcast = new guiListPodcast();
	wndPodcast->setRect(0, 0, 600, 1024);


	wndHomeControl = new guiHomeControl();
	wndHomeControl->setRect(0, 0, 600, 1024);

	wndPlayer = new guiPlayer();
	wndPlayer->setRect(0, 0, 600, 1024);

	_gblPlayer = wndPlayer;



	SDL_QueryTexture(_textWallPaper, NULL, NULL, &_texSize.w, &_texSize.h);

	SDL_SetTextureBlendMode(_textWallPaper, SDL_BLENDMODE_BLEND);

}

void guiHome::render() {


	guiBase * pTemp;

	computeClipping();

	boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);

	_texSize.x = _absWndRect.x;
	_texSize.y = _absWndRect.y;

	SDL_RenderCopy(_renderer, _textWallPaper, NULL, NULL);


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

	if (butPodcast->isClicked())
	{
		wndPodcast->update();
		setActiveWindows(wndPodcast);
	}

	if (butHomeControl->isClicked())
		setActiveWindows(wndHomeControl);

	if (butPlayer->isClicked())
		setActiveWindows(wndPlayer);
}
