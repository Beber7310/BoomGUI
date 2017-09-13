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
}

guiHome::guiHome(SDL_Renderer *renderer) {

	_renderer = renderer;
	// TODO Auto-generated constructor stub
	butAlbum 		= new guiButton(_renderer, 75		,  75		, 150, 150, "res/album.jpg");
	butplaylist 	= new guiButton(_renderer, 375	,  75		, 150, 150, "res/k7.jpg");
	butHomeControl 	= new guiButton(_renderer, 75		,  800		, 150, 150, "truc.jpeg");

	AddChild(butAlbum);
	AddChild(butplaylist);
	AddChild(butHomeControl);

	wndAlbum=new guiListAlbum(renderer);
	wndAlbum->setRect(0,0,600,1024);

	//wndAlbum->sort();

}

guiHome::~guiHome() {
	// TODO Auto-generated destructor stub
}

void guiHome::event(int x, int y, int button) {
	guiBase::event(x,y,button);

	if(butAlbum->_click==3)
		setActiveWindows(wndAlbum);
	butAlbum->_click=0;
}
