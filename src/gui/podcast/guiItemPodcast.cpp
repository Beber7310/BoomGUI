/*
 * guiItemPodcast.cpp
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
#include <podcast/guiItemPodcast.h>
#include <stdlib.h>
#include "string.h"
#include "guiList.h"
#include "guiItemTrack.h"
#include "guiAlbumFilter.h"
#include "guiPlayer.h"

guiItemPodcast::guiItemPodcast() {

}

guiItemPodcast::guiItemPodcast(SDL_Renderer * renderer, char* htmlSource) {
	char filePath[512];
	char str[512];

	char str_artiste[512];
	char str_album[512];
	char str_cover[512];
	char str_genre[512];

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 200;

	_TrackList = new guiList();

	_htmlSource = (char*) malloc(strlen(htmlSource) + 1);
	strcpy(_htmlSource, htmlSource);

	_texCover = NULL;
	_textAlbum = NULL;
	_titleUTF8 = NULL;
}

guiItemPodcast::~guiItemPodcast() {
	// TODO Auto-generated destructor stub
}

void guiItemPodcast::render() {
	SDL_Rect coverRect;
	computeClipping();
	// SDL_RenderSetClipRect (renderer, &_absWndRect);

	boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y;
	coverRect.w = _absWndRect.h;
	coverRect.h = _absWndRect.h;

	SDL_RenderCopy(_renderer, _texCover, NULL, &coverRect);


	_font2->print(_titleUTF8,215,_absWndRect.y);
}

void guiItemPodcast::play() {
	guiBase * pTemp;
	char szCmd[256];
	system("mpc clear");

	std::list<guiBase*>::iterator it;
	pTemp = _TrackList->GetFirstChild(&it);
	while (pTemp) {
		sprintf(szCmd, "mpc add %s", ((guiItemTrack*) pTemp)->_szPath);
		printf("%s\n", szCmd);
		system(szCmd);
		pTemp = _TrackList->GetNextChild(&it);
	}
	system("mpc play");
}

void guiItemPodcast::event(int x, int y, int button) {
	guiBase::event(x, y, button);
	if (button == 4) {
		play();
		((guiPlayer*) _gblPlayer)->_texCover = _texCover;
		setActiveWindows(_gblPlayer);
	}
}

void guiItemPodcast::setTitle(const char* title) {
	_titleUTF8 = (char*) malloc(strlen(title) + 1);
	strcpy(_titleUTF8, title);

}

void guiItemPodcast::setImage(const char* img) {
	_coverHtmplPath = (char*) malloc(strlen(img) + 1);
	strcpy(_coverHtmplPath, img);
}
