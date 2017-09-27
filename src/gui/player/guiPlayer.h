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

#ifdef __RASP__
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <semaphore.h>

#endif

class guiPlayer: public guiBase {
public:
	guiPlayer();
	guiPlayer(SDL_Renderer * renderer);
	char szCurrent[512];

	virtual ~guiPlayer();
	void render(SDL_Renderer *renderer);
	void event(int x, int y, int button);
	guiItemAlbum* _pCurrentAlbum;
	guiButton* wndBtnBack;
	guiButton* wndBtnPrev;
	guiButton* wndBtnNext;
	guiButton* wndBtnPlay;

	SDL_Texture * _textSong;

	SDL_Rect  _textSize;
	SDL_Texture * _texCover;
	bool	update;
	#ifdef __RASP__
	pthread_mutex_t my_mutex;
	#endif
};

#endif /* SRC_GUI_GUIPLAYER_H_ */
