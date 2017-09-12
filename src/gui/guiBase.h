/*
 * guiBase.h
 *
 *  Created on: 5 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUIBASE_H_
#define SRC_GUIBASE_H_

#include "SDL2_gfxPrimitives.h"
#include <list>

class guiBase {
public:
	guiBase();
	guiBase(int x,int y, int w ,int h);

	virtual ~guiBase();


	SDL_Rect _relWndRect;
	SDL_Rect _absWndRect;
	std::list<guiBase*> _lstWnd;
	char* _sortName;

	void AddChild(guiBase * pWin);
	guiBase * GetFirstChild(std::list<guiBase*>::iterator* it);
	guiBase * GetNextChild(std::list<guiBase*>::iterator* it);
	void sort ();
	virtual void render(SDL_Renderer *renderer);

	virtual void event(int x,int y,int button);

private:
	guiBase * _pParent;

	/*guiBase * _pFirstChild1;
	guiBase * _pPrevWnd1;
	guiBase * _pNextWnd1;
	*/


};

#endif /* SRC_GUIBASE_H_ */
