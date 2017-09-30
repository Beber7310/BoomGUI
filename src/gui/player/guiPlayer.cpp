/*
 * guiPlayer.cpp
 *
 *  Created on: 16 sept. 2017
 *      Author: Bertrand
 */

#include <guiPlayer.h>
#include <guiButton.h>
#include <stdlib.h>
#include <unistd.h>


void* guiPLayerThread(void * p) {
	FILE *in;
	guiPlayer* pPlay=(guiPlayer*)p;
	char buff[512];
	bool goodTrack=false;

	while (1) {
		if(goodTrack)
		system("mpc idle");
		goodTrack=false;
		if (!(in = popen("mpc current", "r"))) {
			//return;
		}
		while (fgets(buff, sizeof(buff), in) != NULL) {

			int ii=0;
			while (buff[ii] != '\0') {
				if (buff[ii] == '-') {
					buff[ii]='\n';
					goodTrack=true;
				}
				ii++;
			}
			pthread_mutex_lock (&pPlay->my_mutex);
			sprintf(pPlay->szCurrent,"%s",buff);
			pPlay->update=true;
			pthread_mutex_unlock (&pPlay->my_mutex);
		}
		pclose(in);
		sleep(1);
	}
}


guiPlayer::guiPlayer() {

}

guiPlayer::guiPlayer(SDL_Renderer * renderer) {

#ifdef __RASP__
	pthread_t my_PLayerThread;
#endif

	// TODO Auto-generated constructor stub
	wndBtnBack = new guiButton(renderer, 0, 0, 100, 100, "res/back.png");
	AddChild(wndBtnBack);

	wndBtnPrev = new guiButton(renderer, 125, 924, 100, 100, "res/prev.png");
	AddChild(wndBtnPrev);

	wndBtnPlay = new guiButton(renderer, 250, 924, 100, 100, "res/play.png");
	AddChild(wndBtnPlay);

	wndBtnNext = new guiButton(renderer, 375, 924, 100, 100, "res/next.png");
	AddChild(wndBtnNext);

	_texCover = NULL;
	;

#ifdef __RASP__
	pthread_mutex_init (&my_mutex, NULL);
	int ret = pthread_create(&my_PLayerThread, NULL, &guiPLayerThread, this);
	if(ret != 0) {
		printf("Error: pthread_create() failed\n");
	}
#endif

}

guiPlayer::~guiPlayer() {
	// TODO Auto-generated destructor stub
}

void guiPlayer::render(SDL_Renderer *renderer) {
	SDL_Rect coverRect;
	guiBase::render(renderer);

	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y + 100;
	coverRect.w = _absWndRect.w;
	coverRect.h = _absWndRect.w;
	if (_texCover)
		SDL_RenderCopy(renderer, _texCover, NULL, &coverRect);

#ifdef __RASP__
	pthread_mutex_lock (&my_mutex);
#endif

	if (update) {
		if (_textSong)
			SDL_DestroyTexture(_textSong);

		if (szCurrent) {
			SDL_Color couleurTexte = { 255, 255, 255, 255 };
			SDL_Surface* texteAlb = TTF_RenderUTF8_Blended_Wrapped(_police2, szCurrent, couleurTexte, 600);
			_textSong = SDL_CreateTextureFromSurface(renderer, texteAlb);
			SDL_FreeSurface(texteAlb);
			SDL_QueryTexture(_textSong, NULL, NULL, &_textSize.w, &_textSize.h);
		}
		update = false;
	}

	//stringRGBA(renderer, 100,750, szCurrent, 0xFF, 0xFF, 0xFF,0xFF);
	_textSize.x = 300 - _textSize.w / 2;
	_textSize.y = 750;
	SDL_RenderCopy(renderer, _textSong, NULL, &_textSize);

#ifdef __RASP__
	pthread_mutex_unlock (&my_mutex);
#endif

}

void guiPlayer::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

	if (wndBtnPrev->isClicked())
		system("mpc prev");

	if (wndBtnPlay->isClicked())
		system("mpc play");

	if (wndBtnNext->isClicked())
		system("mpc next");
}
