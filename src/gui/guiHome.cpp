/*
 * guiHome.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#include <guiHome.h>

guiHome::guiHome() {
	_renderer = NULL;
	butAlbum = NULL;
	butplaylist = NULL;
	butHomeControl = NULL;
}

guiHome::guiHome(SDL_Renderer *renderer) {

	_renderer = renderer;
	// TODO Auto-generated constructor stub
	butAlbum = new guiButton(_renderer, 10, 10, 100, 100, "truc.jpeg");
	butplaylist = new guiButton(_renderer, 10, 210, 100, 100, "truc.jpeg");
	butHomeControl = new guiButton(_renderer, 10, 410, 100, 100, "truc.jpeg");

	AddChild(butAlbum);
	AddChild(butplaylist);
	AddChild(butHomeControl);
}

guiHome::~guiHome() {
	// TODO Auto-generated destructor stub
}

