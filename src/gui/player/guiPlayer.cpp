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
#include "guiManager.h"
#include "configuration.h"

void* guiPLayerThread(void * p)
{
	FILE *in;
	guiPlayer* pPlay = (guiPlayer*) p;
	char buff[512];
	bool goodTrack = false;

	while (1)
	{
		if (goodTrack)
			system("mpc idle");
		goodTrack = false;
		if (!(in = popen("mpc current", "r")))
		{
			//return;
			printf("guiPLayerThread error while popen\n");
		}
		else
		{
			while (fgets(buff, sizeof(buff), in) != NULL)
			{

				int ii = 0;
				while (buff[ii] != '\0')
				{
					if (buff[ii] == '-')
					{
						buff[ii] = '\n';
						goodTrack = true;
					}
					ii++;
				}
				pthread_mutex_lock(&pPlay->my_mutex);
				sprintf(pPlay->szCurrent, "%s", buff);
				pPlay->update = true;
				pthread_mutex_unlock(&pPlay->my_mutex);
			}
			pclose(in);
			refresh();
		}
		sleep(1);
	}
}

guiPlayer::guiPlayer()
{

#ifdef __RASP__
	pthread_t my_PLayerThread;
#endif

	// TODO Auto-generated constructor stub
	wndBtnBack = new guiButton(0, 0, 100, 100, "res/back.png");
	AddChild(wndBtnBack);

	wndBtnPrev = new guiButton(125, SCREEN_HEIGHT - 100, 100, 100, "res/prev.png");
	AddChild(wndBtnPrev);

	wndBtnPlay = new guiButton(250, SCREEN_HEIGHT - 100, 100, 100, "res/play.png");
	AddChild(wndBtnPlay);

	wndBtnPause = new guiButton(250, SCREEN_HEIGHT - 100, 100, 100, "res/play.png");
	AddChild(wndBtnPause);
	wndBtnPause->enable(false);

	wndBtnNext = new guiButton(375, SCREEN_HEIGHT - 100, 100, 100, "res/next.png");
	AddChild(wndBtnNext);

	wndBtnRandom = new guiButton(0, SCREEN_HEIGHT - 200, 100, 100, "res/shuffle.png");
	AddChild(wndBtnRandom);
	wndBtnRandom->enable(false);

	wndBtnNoRandom = new guiButton(0, SCREEN_HEIGHT - 200, 100, 100, "res/shuffle_no.png");
	AddChild(wndBtnNoRandom);

	_texCover = NULL;

	_mpcRandom = false;
	_mpcPause = false;

#ifdef __RASP__
	pthread_mutex_init (&my_mutex, NULL);
	int ret = pthread_create(&my_PLayerThread, NULL, &guiPLayerThread, this);
	if(ret != 0)
	{
		printf("Error: pthread_create() failed\n");
	}
#endif

}

guiPlayer::~guiPlayer()
{
	// TODO Auto-generated destructor stub
}

void guiPlayer::render()
{
	SDL_Rect coverRect;
	guiBase * pTemp;

	computeClipping();

	SDL_RenderCopy(_renderer, _textWallPaper, NULL, NULL);

	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp)
	{
		pTemp->_absWndRect.x = _absWndRect.x + pTemp->_relWndRect.x;
		pTemp->_absWndRect.y = _absWndRect.y + pTemp->_relWndRect.y;
		pTemp->_absWndRect.w = pTemp->_relWndRect.w;
		pTemp->_absWndRect.h = pTemp->_relWndRect.h;

		pTemp->render();
		pTemp = GetNextChild(&it);
	}

	computeClipping();
	coverRect.x = _absWndRect.x;
	coverRect.y = _absWndRect.y + 100;
	coverRect.w = _absWndRect.w;
	coverRect.h = _absWndRect.w;

	if (_texCover)
		SDL_RenderCopy(_renderer, _texCover, NULL, &coverRect);

#ifdef __RASP__
	pthread_mutex_lock (&my_mutex);
#endif

	if (update)
	{
		update = false;
	}

	if (szCurrent)
	{
		_font2->print(szCurrent, 100, 750);
	}
#ifdef __RASP__
	pthread_mutex_unlock (&my_mutex);
#endif

}

void guiPlayer::event(int x, int y, int button)
{
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

	if (wndBtnPrev->isClicked())
		system("mpc prev");

	if (wndBtnPlay->isClicked())
	{
		system("mpc play");
		wndBtnPlay->enable(false);
		wndBtnPause->enable(true);
	}

	if (wndBtnPause->isClicked())
	{
		system("mpc pause");
		wndBtnPause->enable(false);
		wndBtnPlay->enable(true);
	}

	if (wndBtnNext->isClicked())
		system("mpc next");

	if (wndBtnRandom->isClicked())
	{
		system("mpc random off");
		wndBtnRandom->enable(false);
		wndBtnNoRandom->enable(true);
	}
	if (wndBtnNoRandom->isClicked())
	{
		system("mpc random on");
		wndBtnRandom->enable(true);
		wndBtnNoRandom->enable(false);
	}

}
