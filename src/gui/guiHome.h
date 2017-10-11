/*
 * guiHome.h
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#ifndef SRC_GUI_GUIHOME_H_
#define SRC_GUI_GUIHOME_H_

#include <guiBase.h>
#include <guiButton.h>
#include <guiList.h>
#include <guiListAlbum.h>
#include <guiListPlaylist.h>
#include <guiListPodcast.h>
#include <guiHomeControl.h>
#include <guiPlayer.h>

class guiHome: public guiBase {
public:
	guiHome();

	virtual ~guiHome();
	void event(int x, int y, int button);
	void render();

	guiButton* butAlbum;
	guiButton* butplaylist;
	guiButton* butHomeControl;
	guiButton* butPlayer;
	guiButton* butPodcast;

	guiListAlbum* wndAlbum;
	guiListPlaylist* wndPlaylist;
	guiListPodcast* wndPodcast;
	guiHomeControl* wndHomeControl;
	guiPlayer* wndPlayer;


	SDL_Rect _texSize;
};

#endif /* SRC_GUI_GUIHOME_H_ */
