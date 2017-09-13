#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



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
#include "SDL2_framerate.h"

#include "guiBase.h"
#include "guiList.h"
#include "guiItemAlbum.h"
#include "guiHome.h"

#include "tools.h"

#define WIDTH 600
#define HEIGHT 1024

Uint32 lastButton=0;

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
				update=true;
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
			ry=x; // swap on purpose !!!
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


int
mousseMgt (guiBase* mainWin) {
  SDL_Event e;

  if (SDL_PollEvent (&e)) {
	if (e.type == SDL_QUIT) return -1;

	if (e.type == SDL_MOUSEMOTION) {

	  if (e.motion.state > 0 && lastButton == 0) {
		mainWin->event (e.motion.x, e.motion.y, 1);
	  }
	  if (e.motion.state > 0 && lastButton > 0) {
		mainWin->event (e.motion.x, e.motion.y, 2);
	  }
	  if (e.motion.state == 0 && lastButton > 0) {
		mainWin->event (e.motion.x, e.motion.y, 3);
	  }

	  lastButton = e.motion.state;
	}
  }
  return 0;
}



int main (int argc, char* argv[]) {

#ifdef __RASP__
  pthread_t my_mouseThread;
  SDL_ShowCursor(SDL_DISABLE);
#endif

  if (SDL_Init (SDL_INIT_VIDEO)) {
	printf ("SDL_Init Error: %s", SDL_GetError ());
	return 1;
  }

  if (!IMG_Init (IMG_INIT_JPG)) {
	printf ("IMG_Init Error: %s", SDL_GetError ());
	return 1;
  }

  SDL_Window *window = SDL_CreateWindow ("SDL2_gfx test", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL) {
	printf ("SDL_CreateWindow Error: %s", SDL_GetError ());
	SDL_Quit ();
	return 2;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
	SDL_DestroyWindow (window);
	printf ("SDL_CreateRenderer Error: %s", SDL_GetError ());
	SDL_Quit ();
	return 3;
  }

#ifdef __RASP__
  int ret =  pthread_create(&my_mouseThread, NULL, &guiMouseThread, NULL);
  	if(ret != 0) {
  		printf("Error: pthread_create() failed\n");
  	}
#endif

  FPSmanager manager;

  //Initialisation
  SDL_initFramerate (&manager);
  SDL_setFramerate (&manager, 50);

  guiList mainWin;
  toolsLoadAlbum (renderer, &mainWin);
  mainWin.sort();

  guiHome mainHome(renderer);

  int renderingTime = 0;
  char szFPS[64];

  while (!mousseMgt (&mainHome)) {

	SDL_SetRenderDrawColor (renderer, 0, 0, 0, 0);
	SDL_RenderClear (renderer);

	//SDL_RenderCopy(renderer, texture, NULL, NULL);
	//mainWin.render (renderer);
	mainHome.render(renderer);
	if (renderingTime) sprintf (szFPS, "%f", 1000.0f / renderingTime);
	else sprintf (szFPS, "NA");
	stringRGBA (renderer, 16, 16, szFPS, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderPresent (renderer);

	//renderingTime = SDL_framerateDelay (&manager);

  }

  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
  IMG_Quit ();
  SDL_Quit ();
  return 0;
}

