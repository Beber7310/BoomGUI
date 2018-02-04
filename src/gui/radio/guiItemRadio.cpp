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

guiItemRadio::guiItemRadio(char* fileName) {
	char filePath[512];
	char str[512];

	char str_artiste[512];
	char str_album[512];
	char str_cover[512];
	char str_genre[512];

	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = SCREEN_WIDTH;
	_relWndRect.h = 200;

/*

	// texCover = IMG_LoadTexture(renderer,"cover.jpeg");

	sprintf(filePath, "%s/%s", ALBUM_DIR, fileName);
	std::ifstream infile(filePath);
	std::string line;

	while (!infile.eof()) {
		infile.getline(str, 500);

		if (strstr(str, "<ARTISTE>") != NULL) {
			strcpy(str_artiste, &str[strlen("<ARTISTE>")]);
			_Artiste = (char*) malloc(strlen(str_artiste) + 1);
			strcpy(_Artiste, str_artiste);
		} else if (strstr(str, "<ALBUM>") != NULL) {
			strcpy(str_album, &str[strlen("<ALBUM>")]);
			_AlbumName = (char*) malloc(strlen(str_album) + 1);
			strcpy(_AlbumName, str_album);
		} else if (strstr(str, "<GENRE>") != NULL) {
			strcpy(str_genre, &str[strlen("<GENRE>")]);
			_pGenre = wndFilter->AddFilter(str_genre);
		} else if (strstr(str, "<COVER>") != NULL) {
			//strcpy(str_cover, &str[strlen("<COVER>")]);
			sprintf(str_cover,"%s/%s",BASE_DIR,&str[strlen("<COVER>")]);
			SDL_Surface * image = IMG_Load(str_cover);
			_texCover = SDL_CreateTextureFromSurface(_renderer, image);
			SDL_FreeSurface(image);
		} else {
			if (strlen(str) > 10) //FIXME add keyword
				_TrackList->AddChild(new guiItemTrack(str));
		}

	}
*/


	_sortName = (char*) malloc(strlen(str_artiste) + strlen(str_album) + 10);
	sprintf(_sortName, "%s_%s", str_artiste, str_album);
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

 	rectangleRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y;
	coverRect.w = _absWndRect.h;
	coverRect.h = _absWndRect.h;

	SDL_RenderCopy(_renderer, _texCover, NULL, &coverRect);

	char str_tmp[1024];
	sprintf(str_tmp, "%s\n%s", _AlbumName, _Artiste);
	_font2->print(str_tmp,215,_absWndRect.y);

}

void guiItemRadio::play() {
	guiBase * pTemp;
	char szCmd[256];
	system("mpc clear");
/*
	std::list<guiBase*>::iterator it;
	pTemp = _TrackList->GetFirstChild(&it);
	while (pTemp) {
		sprintf(szCmd, "mpc add %s", ((guiItemTrack*) pTemp)->_szPath);
		printf("%s\n", szCmd);
		system(szCmd);
		pTemp = _TrackList->GetNextChild(&it);

	}

	*/
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
