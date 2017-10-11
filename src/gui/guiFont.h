/*
 * guiFont.h
 *
 *  Created on: 9 oct. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_GUIFONT_H_
#define SRC_GUI_GUIFONT_H_

#include <SDL.h>
#include <guiBase.h>
#include "SDL2_gfxPrimitives.h"
#include <SDL_image.h>
#include <list>
#include "guiManager.h"
#include <stdio.h>
#include <SDL_ttf.h>



class guiFont{
public:
	guiFont();

	guiFont(SDL_Renderer *renderer,char * font);


	virtual ~guiFont();
	void initFont();
	int computeTextureSize();

	int glyph2Index(char* pText,int* idx,int* offset);

	void print(char* str);
	void print(char* str,int x,int y);
	SDL_Rect _glyphSize[256];

	SDL_Texture *_textFont;
	TTF_Font *_police2;
	SDL_Renderer *_renderer2;
	int createGliph(char * str_tmp, int *lastX,int *lastY);
};

#endif /* SRC_GUI_GUIFONT_H_ */
