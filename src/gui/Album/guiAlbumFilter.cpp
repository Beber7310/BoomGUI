/*
 * guiAlbumFilter.cpp
 *
 *  Created on: Sep 14, 2017
 *      Author: dosdab
 */

#include <guiAlbumFilter.h>

guiAlbumFilter::guiAlbumFilter(){

}

guiAlbumFilter::guiAlbumFilter(SDL_Renderer *renderer) {
	// TODO Auto-generated constructor stub
	wndLstFlt=new guiList();
	wndLstFlt->setRect(0,100,600,924);


	wndBtnBack=new guiButton(renderer,0,0,100,100,"back.jpg");

	AddChild(wndBtnBack);
	AddChild(wndLstFlt);
}

guiAlbumFilter::~guiAlbumFilter() {
	// TODO Auto-generated destructor stub
}

void guiAlbumFilter::event(int x, int y, int button) {
	guiBase::event(x,y,button);

	if(wndBtnBack->_click==3)
		popActiveWindows();
	wndBtnBack->_click=0;
}
