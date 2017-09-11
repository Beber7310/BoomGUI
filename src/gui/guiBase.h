/*
 * guiBase.h
 *
 *  Created on: 5 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUIBASE_H_
#define SRC_GUIBASE_H_

#include "SDL2_gfxPrimitives.h"

class guiBase {
public:
	guiBase();
	guiBase(int x,int y, int w ,int h);

	virtual ~guiBase();

	guiBase * _pParent;
	guiBase * _pFirstChild;
	guiBase * _pPrevWnd;
	guiBase * _pNextWnd;

	SDL_Rect _relWndRect;
	SDL_Rect _absWndRect;


	virtual void render(SDL_Renderer *renderer);
	void AddChild(guiBase * pWin);
	virtual void event(int x,int y,int button);
};

#endif /* SRC_GUIBASE_H_ */
