/*
 * guiItemPodcastTracks.cpp
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
#include <podcast/guiItemPodcastTracks.h>
#include <stdlib.h>
#include "string.h"
#include "guiList.h"
#include "guiItemTrack.h"
#include "guiAlbumFilter.h"
#include "guiPlayer.h"
#include "tools.h"

guiItemPodcastTracks::guiItemPodcastTracks() {
	_title = NULL;

}

guiItemPodcastTracks::guiItemPodcastTracks(tm* date, const char* title, int size,char* localPath,SDL_Texture * 	texCover) {
	// TODO Auto-generated constructor stub
	char szTmpTitle[512];

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 100;

	memcpy(&_date, date, sizeof(tm));

	_title = (char*) malloc(strlen(title) + 1);
	strcpy(_title, title);

	_size = size;

	char strtime[128];
	strftime(strtime, sizeof(strtime), "%Y-%m-%d", &_date);
	_strtime = (char*) malloc(strlen(strtime) + 1);
	strcpy(_strtime, strtime);

	_localPath = (char*) malloc(strlen(localPath) + 20);
	sprintf(_localPath,"podcast/%s", localPath);

	_sortName = _strtime;
	_downloaded = false;
	_texCover=texCover;

}

guiItemPodcastTracks::~guiItemPodcastTracks() {
	// TODO Auto-generated destructor stub
}

void guiItemPodcastTracks::render() {
	SDL_Rect coverRect;
	computeClipping();
	// SDL_RenderSetClipRect (renderer, &_absWndRect);

	//boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y;
	coverRect.w = _absWndRect.h;
	coverRect.h = _absWndRect.h;

	_font2->print(_title, 15, _absWndRect.y+20);
	_font2->print(_strtime, 400, _absWndRect.y + 60);
}

void guiItemPodcastTracks::event(int x, int y, int button) {
	guiBase::event(x, y, button);
	if (button == 4) {
		char szCmd[256];
		system("mpc clear");

		sprintf(szCmd, "mpc add \"%s\"", _localPath);
		printf("%s\n", szCmd);
		system(szCmd);

		system("mpc play");

		((guiPlayer*) _gblPlayer)->_texCover = _texCover;
		setActiveWindows(_gblPlayer);

	}
}
