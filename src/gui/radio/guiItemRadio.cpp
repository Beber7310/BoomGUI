/*
 * guiItemRadio.cpp
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#include "configuration.h"
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include "string.h"
#include "guiList.h"
#include "guiItemRadio.h"
#include "guiItemTrack.h"
#include "guiAlbumFilter.h"
#include "guiPlayer.h"

guiItemRadio::guiItemRadio(char* mp3, char* NiceName, char* cover) {
	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = SCREEN_WIDTH;
	_relWndRect.h = 200;

	_mp3 = (char*) malloc(strlen(mp3) + 1);
	strcpy(_mp3, mp3);

	_NiceName = (char*) malloc(strlen(NiceName) + 1);
	strcpy(_NiceName, NiceName);

	_cover = (char*) malloc(strlen(cover) + 1);
	strcpy(_cover, cover);

	_sortName = (char*) malloc(strlen(NiceName) + 10);
	sprintf(_sortName, "%s", NiceName);

	printf(">%s<\n",_mp3);
	printf(">%s<\n",_NiceName);
	printf(">%s<\n",_cover);
	printf(">%s<\n",_sortName);

	SDL_Surface * image = IMG_Load(_cover);
	_texCover = SDL_CreateTextureFromSurface(_renderer, image);
	SDL_FreeSurface(image);

}

guiItemRadio::~guiItemRadio() {
	// TODO Auto-generated destructor stub
}

void guiItemRadio::render() {
	SDL_Rect coverRect;
	/*
	 if (_pGenre != NULL) {
	 if (_pGenre->_selected) {
	 _relWndRect.h = 200;
	 } else {
	 _relWndRect.h = 0;
	 return;
	 }
	 }
	 */
	computeClipping();

	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,
			0xFF, 0xFF, 0xFF);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y;
	coverRect.w = _absWndRect.h;
	coverRect.h = _absWndRect.h;

	SDL_RenderCopy(_renderer, _texCover, NULL, &coverRect);

	char str_tmp[1024];
	sprintf(str_tmp, "%s\n", _NiceName);
	_font2->print(str_tmp, 215, _absWndRect.y);

}

void guiItemRadio::play() {
	guiBase * pTemp;
	char szCmd[256];
	system("mpc clear");
	sprintf(szCmd, "mpc add %s", _mp3);
	system(szCmd);
	system("mpc play");
}

void guiItemRadio::event(int x, int y, int button) {
	guiBase::event(x, y, button);
	if (button == 4) {
		play();
		((guiPlayer*) _gblPlayer)->_texCover = _texCover;
		setActiveWindows(_gblPlayer);
	}
}
