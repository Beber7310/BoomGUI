#include <stdio.h>
#include "SDL2_gfxPrimitives.h"
#include <SDL_image.h>
#include "SDL2_framerate.h"

#include "guiBase.h"
#include "guiList.h"
#include "guiItemAlbum.h"

#include "tools.h"

#define WIDTH 600
#define HEIGHT 1024

int main (int argc, char* argv[])
{

  if (SDL_Init (SDL_INIT_VIDEO))
	{
	  printf ("SDL_Init Error: %s", SDL_GetError ());
	  return 1;
	}

  if (!IMG_Init (IMG_INIT_JPG))
	{
	  printf ("IMG_Init Error: %s", SDL_GetError ());
	  return 1;
	}

  SDL_Window *window = SDL_CreateWindow ("SDL2_gfx test", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
  if (window == NULL)
	{
	  printf ("SDL_CreateWindow Error: %s", SDL_GetError ());
	  SDL_Quit ();
	  return 2;
	}

  SDL_Renderer *renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL)
	{
	  SDL_DestroyWindow (window);
	  printf ("SDL_CreateRenderer Error: %s", SDL_GetError ());
	  SDL_Quit ();
	  return 3;
	}

  FPSmanager manager;

  //Initialisation
  SDL_initFramerate(&manager);
  SDL_setFramerate(&manager,50);

  SDL_Event e;

  guiList mainWin;
/*
   mainWin.AddChild (new guiItemAlbum (renderer));
  mainWin.AddChild (new guiItemAlbum (renderer));
  mainWin.AddChild (new guiItemAlbum (renderer));
*/
  toolsLoadAlbum(renderer,&mainWin);

  int quit = 0;
  int renderingTime=0;
  char szFPS[64];

  while (!quit)
	{
	  if (SDL_PollEvent (&e))
		{
		  if (e.type == SDL_QUIT)
			quit = 1;
		}
	  SDL_SetRenderDrawColor (renderer, 0, 0, 0, 0);
	  SDL_RenderClear (renderer);


	  /*
	   thickLineColor(renderer, 0, 0, WIDTH, HEIGHT, 20, 0xFF00FFFF) ;
	   thickLineColor(renderer, 0, HEIGHT, WIDTH, 0, 20, 0xFF00FFFF) ;
	   stringRGBA(renderer,20,20,"This is a test",0xFF,0xFF,0xFF,0xFF);
	   */
	  //SDL_RenderCopy(renderer, texture, NULL, NULL);
	  mainWin.render (renderer);
	  if(renderingTime)
		sprintf(szFPS,"%f",1000.0f/renderingTime);
	  else
		sprintf(szFPS,"NA");
	  stringRGBA(renderer,16,16,szFPS,0xFF,0xFF,0xFF,0xFF);
	  SDL_RenderPresent (renderer);

	  renderingTime=SDL_framerateDelay(&manager);
	}

  SDL_DestroyRenderer (renderer);
  SDL_DestroyWindow (window);
  IMG_Quit();
  SDL_Quit ();
  return 0;
}
