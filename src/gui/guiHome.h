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


class guiHome : public guiBase{
public:
	guiHome();
	guiHome(SDL_Renderer *renderer);
	virtual ~guiHome();

	guiButton* butAlbum;
	guiButton* butplaylist;
	guiButton* butHomeControl;
};

#endif /* SRC_GUI_GUIHOME_H_ */
