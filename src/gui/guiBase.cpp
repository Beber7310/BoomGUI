/*
 * guiBase.cpp
 *
 *  Created on: 5 sept. 2017
 *      Author: Bertrand
 */

#include <stdio.h>


#include "guiBase.h"

guiBase::guiBase ()
{
  _pParent = NULL;
  _pFirstChild = NULL;
  _pPrevWnd = NULL;
  _pNextWnd = NULL;

  _relWndRect.x = 0;
  _relWndRect.y = 0;
  _relWndRect.w = 600;
  _relWndRect.h = 1024;

  _absWndRect.x = 0;
  _absWndRect.y = 0;
  _absWndRect.w = 600;
  _absWndRect.h = 1024;
}

guiBase::guiBase (int x, int y, int w, int h)
{
  _pParent = NULL;
  _pFirstChild = NULL;
  _pPrevWnd = NULL;
  _pNextWnd = NULL;

  _relWndRect.x = x;
  _relWndRect.y = y;
  _relWndRect.w = w;
  _relWndRect.h = h;

  _absWndRect.x = 0;
  _absWndRect.y = 0;
  _absWndRect.w = 200;
  _absWndRect.h = 200;
}

guiBase::~guiBase ()
{
  // TODO Auto-generated destructor stub
}

void
guiBase::AddChild (guiBase * pWin)
{
  guiBase * pTemp;
  if (_pFirstChild == NULL)
	{
	  _pFirstChild = pWin;
	}
  else
	{
	  pTemp = _pFirstChild;
	  while (pTemp->_pNextWnd)
		{
		  pTemp = pTemp->_pNextWnd;
		}
	  pTemp->_pNextWnd = pWin;
	  pWin->_pPrevWnd = pTemp;
	}

  pWin->_pParent = this;
}

guiBase * guiBase::GetFirstChild()
{
	return _pFirstChild;
}
guiBase * guiBase::GetNextChild(guiBase * pC)
{
	if(pC)
		return pC->_pNextWnd;
	else
		return NULL;
}

void
guiBase::render (SDL_Renderer *renderer)
{
  guiBase * pTemp;


  SDL_RenderSetClipRect (renderer, &_absWndRect);

  boxRGBA (renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
  rectangleRGBA (renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

  pTemp = _pFirstChild;
  while (pTemp)
	{
	  SDL_RenderSetClipRect (renderer, &_absWndRect);

	  pTemp->_absWndRect.x=_absWndRect.x+pTemp->_relWndRect.x;
	  pTemp->_absWndRect.y=_absWndRect.y+pTemp->_relWndRect.y;
	  pTemp->_absWndRect.w=pTemp->_relWndRect.w;
	  pTemp->_absWndRect.h=pTemp->_relWndRect.h;

	  pTemp->render (renderer);
	  pTemp = pTemp->_pNextWnd;
	}

  SDL_RenderSetClipRect (renderer, NULL);
}


void guiBase::event(int x,int y,int button)
{
  guiBase * pTemp;
  pTemp = _pFirstChild;
   while (pTemp)
 	{

 	  pTemp->event (x,y,button);
 	  pTemp = pTemp->_pNextWnd;
 	}
}
