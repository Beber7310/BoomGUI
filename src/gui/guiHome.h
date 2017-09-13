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


class guiHome : public guiBase{
public:
	guiHome();
	guiHome(SDL_Renderer *renderer);
	virtual ~guiHome();
	void event(int x, int y, int button);

	guiButton* butAlbum;
	guiButton* butplaylist;
	guiButton* butHomeControl;

	guiListAlbum*   wndAlbum;
};

#endif /* SRC_GUI_GUIHOME_H_ */
