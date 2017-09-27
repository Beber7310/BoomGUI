/*
 * guiItemPlaylist.cpp
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
#include "guiItemPlaylist.h"
#include "guiItemTrack.h"
#include "guiAlbumFilter.h"
#include "guiPlayer.h"

guiItemPlaylist::guiItemPlaylist() {

}

guiItemPlaylist::guiItemPlaylist(SDL_Renderer * renderer, char* fileName) {
	char filePath[512];
	char str[512];

	char str_artiste[512];
	char str_album[512];
	char str_cover[512];


	_relWndRect.x = 10;
	_relWndRect.y = 10;
	_relWndRect.w = 600;
	_relWndRect.h = 200;



	_TrackList = new guiList();

	// texCover = IMG_LoadTexture(renderer,"cover.jpeg");

	sprintf(filePath, "%s/%s", PLAYLIST_DIR, fileName);
	std::ifstream infile(filePath);
	std::string line;

	while (!infile.eof()) {
		infile.getline(str, 500);

		if (strstr(str, "<PLAYLIST>") != NULL) {
			strcpy(str_artiste, &str[strlen("<PLAYLIST>")]);
			_PlaylistName = (char*) malloc(strlen(str_artiste) + 1);
			strcpy(_PlaylistName, str_artiste);
		}  else if (strstr(str, "<COVER>") != NULL) {
			strcpy(str_cover, &str[strlen("<COVER>")]);
			SDL_Surface * image = IMG_Load(str_cover);
			_texCover = SDL_CreateTextureFromSurface(renderer, image);
			SDL_FreeSurface(image);
		} else {
			if (strlen(str) > 10) //FIXME add keyword
				_TrackList->AddChild(new guiItemTrack(str));
		}

	}

	char str_tmp[1024];
	SDL_Color couleurTexte = { 255, 255, 255, 255 };
	sprintf(str_tmp, "%s", _PlaylistName);
	SDL_Surface* texteAlb = TTF_RenderUTF8_Blended_Wrapped(_police2, str_tmp,couleurTexte, 370);
	_textAlbum = SDL_CreateTextureFromSurface(renderer, texteAlb);
	SDL_FreeSurface(texteAlb);
	SDL_QueryTexture(_textAlbum, NULL, NULL, &_textSize.w, &_textSize.h);

	_sortName = (char*) malloc(strlen(str_artiste) + strlen(str_album) + 10);
	sprintf(_sortName, "%s_%s", str_artiste, str_album);
}

guiItemPlaylist::~guiItemPlaylist() {
	// TODO Auto-generated destructor stub
}

void guiItemPlaylist::render(SDL_Renderer *renderer) {
	SDL_Rect coverRect;

	boxRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0,
			0x0, 0x00, 0xFF);
	rectangleRGBA(renderer, _absWndRect.x, _absWndRect.y,
			_absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF,
			0xFF, 0xFF, 0xFF);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y;
	coverRect.w = _absWndRect.h;
	coverRect.h = _absWndRect.h;

	SDL_RenderCopy(renderer, _texCover, NULL, &coverRect);

	_textSize.x = 215;
	_textSize.y = _absWndRect.y;
	SDL_RenderCopy(renderer, _textAlbum, NULL, &_textSize);
}

void guiItemPlaylist::play() {
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

void guiItemPlaylist::event(int x, int y, int button) {
	guiBase::event(x, y, button);
	if (button == 4) {
		play();
		((guiPlayer*)_gblPlayer)->_texCover=_texCover;
		setActiveWindows(_gblPlayer);
	}
}
