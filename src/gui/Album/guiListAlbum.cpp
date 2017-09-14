/*
 * guiListAlbum.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include "guiListAlbum.h"
#include "guiManager.h"
#include "tools.h"

guiListAlbum::guiListAlbum(SDL_Renderer *renderer) {
	// TODO Auto-generated constructor stub

	wndLstAlb=new guiList();
	wndLstAlb->setRect(0,100,600,942);
	toolsLoadAlbum (renderer, wndLstAlb);
	wndLstAlb->sort();

	wndBtnBack=new guiButton(renderer,0,0,100,100,"back.jpg");
	AddChild(wndBtnBack);
	AddChild(wndLstAlb);
}

guiListAlbum::~guiListAlbum() {
	// TODO Auto-generated destructor stub
}

void guiListAlbum::event(int x, int y, int button) {
	guiBase::event(x,y,button);

	if(wndBtnBack->_click==3)
		popActiveWindows();
	wndBtnBack->_click=0;
}
