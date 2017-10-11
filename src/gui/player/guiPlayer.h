/*
 * guiPlayer.h
 *
 *  Created on: 16 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_GUIPLAYER_H_
#define SRC_GUI_GUIPLAYER_H_

class guiBase;
#include "guiItemAlbum.h"

//#ifdef __RASP__
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <semaphore.h>

//#endif

class guiPlayer: public guiBase {
public:
	guiPlayer();

	char szCurrent[512];

	virtual ~guiPlayer();
	void render();
	void event(int x, int y, int button);
	//guiItemAlbum* _pCurrentAlbum;
	guiButton* wndBtnBack;
	guiButton* wndBtnPrev;
	guiButton* wndBtnNext;
	guiButton* wndBtnPlay;
	guiButton* wndBtnRandom;
	guiButton* wndBtnNoRandom;

	SDL_Texture * _texCover;
	bool	update;

	bool	_mpcRandom;
	bool	_mpcPause;

	pthread_mutex_t my_mutex;


};

#endif /* SRC_GUI_GUIPLAYER_H_ */
