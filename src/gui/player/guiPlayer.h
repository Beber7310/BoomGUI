/*
 * guiPlayer.h
 *
 *  Created on: 16 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_GUIPLAYER_H_
#define SRC_GUI_GUIPLAYER_H_

#include "guiItemAlbum.h";

class guiPlayer {
public:
	guiPlayer();
	virtual ~guiPlayer();

	 guiItemAlbum* _pCurrentAlbum;
};

#endif /* SRC_GUI_GUIPLAYER_H_ */
