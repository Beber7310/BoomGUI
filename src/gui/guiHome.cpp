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

	int	stdwidth=SCREEN_WIDTH/4;
	int	stdspace=SCREEN_WIDTH/8;


	// TODO Auto-generated constructor stub
	butAlbum = new guiButton( stdspace, stdspace, stdwidth, stdwidth, "res/album.png");
	butplaylist = new guiButton( 2*stdwidth + stdspace, stdspace, stdwidth, stdwidth, "res/playlist.png");
	//butRadio = new guiButton( stdspace, 2*stdwidth + stdspace, stdwidth, stdwidth, "res/radio.png");
	butPlayer = new guiButton(  2*stdwidth + stdspace, SCREEN_HEIGHT-(stdspace+stdwidth), stdwidth, stdwidth, "res/player.png");

#ifdef	_CONF_PODCAST_EN
	butPodcast = new guiButton( 2*stdwidth + stdspace, 2*stdwidth + stdspace, stdwidth, stdwidth, "res/podcast.png");
	AddChild(butPodcast);
#endif

#ifdef _CONF_HOMECONTROL_EN
	butHomeControl = new guiButton( stdspace, SCREEN_HEIGHT-(stdspace+stdwidth), stdwidth, stdwidth, "res/homecontrol.png");
	AddChild(butHomeControl);
#endif

	AddChild(butAlbum);
	AddChild(butplaylist);
	AddChild(butPlayer);
	//AddChild(butRadio);



	wndAlbum = new guiListAlbum();
	wndAlbum->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	wndPlaylist = new guiListPlaylist();
	wndPlaylist->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

#ifdef	_CONF_PODCAST_EN
	wndPodcast = new guiListPodcast();
	wndPodcast->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

#ifdef _CONF_HOMECONTROL_EN
	wndHomeControl = new guiHomeControl();
	wndHomeControl->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

	wndPlayer = new guiPlayer();
	wndPlayer->setRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

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


#ifdef _CONF_PODCAST_EN
	if (butPodcast->isClicked())
	{
		wndPodcast->update();
		setActiveWindows(wndPodcast);
	}
#endif

#ifdef _CONF_HOMECONTROL_EN
	if (butHomeControl->isClicked())
		setActiveWindows(wndHomeControl);
#endif

	if (butPlayer->isClicked())
		setActiveWindows(wndPlayer);
}
