/*
 * guiList.cpp
 *
 *  Created on: 8 sept. 2017
 *      Author: Bertrand
 */

#include "guiList.h"

guiList::guiList ()
{
  // TODO Auto-generated constructor stub

}

guiList::~guiList ()
{
  // TODO Auto-generated destructor stub
}

void
guiList::render (SDL_Renderer *renderer)
{
  guiBase * pTemp;
  int lastAbsPosY=0;

  SDL_RenderSetClipRect (renderer, &_absWndRect);

  boxRGBA (renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
  rectangleRGBA (renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

  pTemp = _pFirstChild;
  while (pTemp)
	{
	  SDL_RenderSetClipRect (renderer, &_absWndRect);

	  pTemp->_relWndRect.y=lastAbsPosY;
	  lastAbsPosY=pTemp->_relWndRect.y+pTemp->_relWndRect.h;

	  pTemp->_absWndRect.x=_absWndRect.x;
	  pTemp->_absWndRect.y=_absWndRect.y+pTemp->_relWndRect.y;
	  pTemp->_absWndRect.w=_relWndRect.w;
	  pTemp->_absWndRect.h=pTemp->_relWndRect.h;

	  pTemp->render (renderer);
	  pTemp = pTemp->_pNextWnd;
	}

  SDL_RenderSetClipRect (renderer, NULL);
}
