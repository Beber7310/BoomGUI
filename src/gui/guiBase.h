/*
 * guiBase.h
 *
 *  Created on: 5 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUIBASE_H_
#define SRC_GUIBASE_H_

class guiBase;

#include "SDL2_gfxPrimitives.h"
#include <SDL_image.h>
#include <list>
#include "guiManager.h"
#include <stdio.h>
#include <SDL_ttf.h>

class guiBase {
public:
	guiBase();
	guiBase(int x, int y, int w, int h);

	virtual ~guiBase();

	SDL_Rect _relWndRect;
	SDL_Rect _absWndRect;
	std::list<guiBase*> _lstWnd;
	char* _sortName;

	void AddChild(guiBase * pWin);
	guiBase * GetFirstChild(std::list<guiBase*>::iterator* it);
	guiBase * GetNextChild(std::list<guiBase*>::iterator* it);
	void sort();
	virtual void render(SDL_Renderer *renderer);
	virtual void event(int x, int y, int button);
	void setRect(int x, int y, int w, int h);
	static void staticInit(void);

	static guiBase * _gblPlayer;

private:
	guiBase * _pParent;

protected:
	static SDL_Renderer *_renderer;
	static TTF_Font *_police1;
	static TTF_Font *_police2;
	static TTF_Font *_police3;


};

#endif /* SRC_GUIBASE_H_ */
