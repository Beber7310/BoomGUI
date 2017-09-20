/*
 * guiManager.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifdef __RASP__
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <semaphore.h>
#include <linux/input.h>
#define EVENT_DEVICE    "/dev/input/event0"
#endif

#include "SDL2_gfxPrimitives.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL2_framerate.h"


#include "guiBase.h"
#include "guiList.h"
#include "guiItemAlbum.h"
#include "guiHome.h"

#include "tools.h"

#define WIDTH 600
#define HEIGHT 1024

Uint32 lastButton = 0;
guiBase *pActiveWnd;
std::list<guiBase*> lstWnd;

#ifdef __RASP__
void* guiMouseThread(void * p)
{
	int x=0,y=0,t=0;
	int rx=0,ry=0,rt=0;
	int error_read=0;
	struct input_event ev;
	int fd;
	char name[256] = "Unknown";
	bool update=false;

	/* Open Device */
	fd = open(EVENT_DEVICE, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "%s is not a vaild device\n", EVENT_DEVICE);
		pthread_exit(NULL);
		return 0;
	}

	/* Print Device Name */
	ioctl(fd, EVIOCGNAME(sizeof(name)), name);
	printf("Reading from:\n");
	printf("device file = %s\n", EVENT_DEVICE);
	printf("device name = %s\n", name);

	for (;;) {
		const ssize_t ev_size = sizeof(struct input_event);
		ssize_t size;

		/* TODO: use select() */

		size = read(fd, &ev, ev_size);
		if (size < ev_size) {
			fprintf(stderr, "Error size when reading\n");
			close(fd);
			sleep(1);
			fd = open(EVENT_DEVICE, O_RDONLY);
			error_read++;
			if(error_read>10)
			goto err;
		}
		else
		{
			error_read=0;
			if (ev.type == EV_ABS && ev.code == ABS_X) {
				/* TODO: convert value to pixels */
				//printf("X = %d\n", ev.value);
				x=ev.value;
				//update=true;
			}
			if (ev.type == EV_ABS && ev.code == ABS_Y) {
				/* TODO: convert value to pixels */
				//printf("Y = %d\n", ev.value);
				y=ev.value;
				update=true;
			}
			else if(ev.type == EV_KEY && (ev.code == BTN_TOUCH))
			{
				//printf("touch: %i\n", ev.value);
				t=ev.value;
				if(!t)
				update=true;
			}
			else
			{
				//printf("%x %x %x\n",ev.type, ev.code,ev.value);
			}
		}

		if(update)
		{
			update=false;

			rx=600-y; // swap on purpose !!!
			ry=x;// swap on purpose !!!
			rt=t;
			//pMouse->update++;
			SDL_Event e;

			e.type=SDL_MOUSEMOTION;
			e.motion.x=rx;
			e.motion.y=ry;
			e.motion.state=t;

			SDL_PushEvent(&e);
			//printf("%3.3i %3.3i %1.1i\n",pMouse->x, pMouse->y,pMouse->t);

		}
	}
	printf("Endof mousse thread!\n");
	return 0;

	err:
	printf("Fuck! error in mousse thread!\n");
	close(fd);
	return 0;
}
#endif

int mousseMgt(guiBase* mainWin) {
	SDL_Event e;
	static int firstX,firstY;

	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			return -1;

		if (e.type == SDL_MOUSEMOTION) {

			if (e.motion.state > 0 && lastButton == 0) {
				mainWin->event(e.motion.x, e.motion.y, 1);
				firstX=e.motion.x;
				firstY=e.motion.y;
			}
			if (e.motion.state > 0 && lastButton > 0) {
				mainWin->event(e.motion.x, e.motion.y, 2);
			}
			if (e.motion.state == 0 && lastButton > 0) {
				mainWin->event(e.motion.x, e.motion.y, 3);
				if((abs(firstX-e.motion.x)<100) &&(abs(firstY-e.motion.y)<100))
				{
					mainWin->event(e.motion.x, e.motion.y, 4);
				}
			}

			lastButton = e.motion.state;
#ifdef __RASP__
			SDL_WarpMouseInWindow(NULL, e.motion.x, e.motion.y);
#endif

		}

	}
	return 0;
}

int rendertask() {

#ifdef __RASP__
	pthread_t my_mouseThread;
	SDL_ShowCursor(SDL_DISABLE);
#endif

	if (SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}

	if (!IMG_Init(IMG_INIT_JPG)) {
		printf("IMG_Init Error: %s", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2_gfx test", 100, 100, WIDTH,
	HEIGHT, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		SDL_Quit();
		return 2;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return 3;
	}

	if(TTF_Init())
	{
	    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
	    exit(EXIT_FAILURE);
	}
/*
	SDL_Surface *texte = NULL;
	TTF_Font *police = TTF_OpenFont("res/font1.otf", 65);
	if(!police)
	{
		printf("TTF_OpenFont Error: %s\n", SDL_GetError());
		 exit(EXIT_FAILURE);
	}

	SDL_Color couleurBlanc = {128, 128, 255,128};
	texte = TTF_RenderText_Blended(police, "Salut les Zér0s !", couleurBlanc);
	SDL_Texture * texture=SDL_CreateTextureFromSurface(renderer, texte);
	SDL_FreeSurface(texte);
*/

#ifdef __RASP__
	int ret = pthread_create(&my_mouseThread, NULL, &guiMouseThread, NULL);
	if(ret != 0) {
		printf("Error: pthread_create() failed\n");
	}
#endif

	guiHome::staticInit();
	guiHome mainHome(renderer);
	setActiveWindows(&mainHome);

	guiBase *localpActiveWnd = pActiveWnd;
	while (!mousseMgt(localpActiveWnd)) {
		localpActiveWnd = pActiveWnd;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		localpActiveWnd->render(renderer);

		SDL_RenderPresent(renderer);
	}

	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}

void setActiveWindows(guiBase* pWin) {
	pActiveWnd = pWin;
	lstWnd.push_front(pActiveWnd);
}

void popActiveWindows() {
	lstWnd.pop_front();
	pActiveWnd = lstWnd.front();

}
