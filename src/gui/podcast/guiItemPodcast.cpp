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
#include "guiItemPodcastTracks.h"
#include "tools.h"

guiItemPodcast::guiItemPodcast() {

}

guiItemPodcast::guiItemPodcast(char* title,peePodcast* pPodcast) {
	char filePath[512];
	char str[512];

	char str_artiste[512];
	char str_album[512];
	char str_cover[512];
	char str_genre[512];

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 100;

	_TrackList = new guiList();

	_coverHtmplPath = NULL;
	_htmlSource = NULL;
	_titleUTF8 = NULL;

	_titleUTF8 = (char*) malloc(strlen(title) + 1);
	strcpy(_titleUTF8, title);

	_wndPodcastTracks=new guiListPodcastTracks(pPodcast);

	_texCover = NULL;

	_minLength = 10;

	_directory = NULL;

	_sortName = _titleUTF8;
}

guiItemPodcast::~guiItemPodcast() {
	// TODO Auto-generated destructor stub
}

void guiItemPodcast::render() {
	SDL_Rect coverRect;
	computeClipping();
	// SDL_RenderSetClipRect (renderer, &_absWndRect);

	//boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y;
	coverRect.w = _absWndRect.h;
	coverRect.h = _absWndRect.h;

	if (_texCover)
		if (SDL_RenderCopy(_renderer, _texCover, NULL, &coverRect)) {
			printf("Error when rendering texture %s %s\n", _directory, SDL_GetError());
			SDL_ClearError();
			_texCover = NULL;
		}

	_font2->print(_titleUTF8, 215, _absWndRect.y+20);
}


void guiItemPodcast::event(int x, int y, int button) {
	guiBase::event(x, y, button);
	if (button == 4) {
		_wndPodcastTracks->update();
		setActiveWindows(_wndPodcastTracks);
	}
}

void guiItemPodcast::setTitle(const char* title) {
	_titleUTF8 = (char*) malloc(strlen(title) + 1);
	strcpy(_titleUTF8, title);

	_directory = (char*) malloc(strlen(title) + 1);
	strcpy(_directory, title);

	toolsCleanUTF8(_directory);

}

void guiItemPodcast::setImage(const char* img) {
	char szTemp[1024];

	_coverHtmplPath = (char*) malloc(strlen(img) + 1);
	strcpy(_coverHtmplPath, img);

	sprintf(szTemp, "%s/%s/cover.jpg", PODCAST_DIR, _directory);

	if (!toolsDownloadExist(szTemp)) {
		sprintf(szTemp, "wget \"%s\" -O \"%s/%s/cover.jpg\" -q --limit-rate=100k", _coverHtmplPath, PODCAST_DIR, _directory);
		printf("%s\n", szTemp);
		system(szTemp);
	}

	sprintf(szTemp, "%s/%s/cover.jpg", PODCAST_DIR, _directory);
	_texCover = IMG_LoadTexture(_renderer, szTemp);
	if (!_texCover) {
		printf("Error when loading texture %s: %s\n", szTemp, SDL_GetError());
		SDL_ClearError();
	} else {
		SDL_SetTextureBlendMode(_texCover, SDL_BLENDMODE_BLEND);
	}
}

guiItemPodcastTracks* guiItemPodcast::GetTrackByTitle(const char* title) {

	//BUGGY

	guiBase * pTemp;
	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp) {
		if (strcmp(((guiItemPodcastTracks*) pTemp)->_title, title) == 0) {
			return (guiItemPodcastTracks*) pTemp;
		}
		pTemp = GetNextChild(&it);
	}

	return NULL;
}
