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


	SDL_Rect _relWndRect;
	SDL_Rect _absWndRect;

	void AddChild(guiBase * pWin);
	guiBase * GetFirstChild();
	guiBase * GetNextChild(guiBase * pC);


	virtual void render(SDL_Renderer *renderer);

	virtual void event(int x,int y,int button);

private:
	guiBase * _pParent;
	guiBase * _pFirstChild;
	guiBase * _pPrevWnd;
	guiBase * _pNextWnd;

};

#endif /* SRC_GUIBASE_H_ */
