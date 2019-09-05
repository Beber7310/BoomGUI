/*
 * guiPee.cpp
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#include <stdlib.h>
#include <configuration.h>
#include <guiPee.h>
#include "tools.h"


guiPee::guiPee()
{

	int stdwidth = SCREEN_WIDTH / 4;
	int stdspace = SCREEN_WIDTH / 8;

	// TODO Auto-generated constructor stub
	wndBtnBack = new guiButton(0, 0, 100, 100, "res/back.png");
 	butDeezer = new guiButton((SCREEN_WIDTH/2)-50, (SCREEN_HEIGHT/2)-50, 100, 100, "res/deezer.png");

 	AddChild(butDeezer);
	AddChild(wndBtnBack);


}

void guiPee::render()
{

	guiBase * pTemp;

	computeClipping();

	boxRGBA(_renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);

	_texSize.x = _absWndRect.x;
	_texSize.y = _absWndRect.y;

	SDL_RenderCopy(_renderer, _textWallPaper, NULL, NULL);

	std::list<guiBase*>::iterator it;
	pTemp = GetFirstChild(&it);
	while (pTemp)
	{
		pTemp->_absWndRect.x = _absWndRect.x + pTemp->_relWndRect.x;
		pTemp->_absWndRect.y = _absWndRect.y + pTemp->_relWndRect.y;
		pTemp->_absWndRect.w = pTemp->_relWndRect.w;
		pTemp->_absWndRect.h = pTemp->_relWndRect.h;

		pTemp->render();
		pTemp = GetNextChild(&it);
	}

	SDL_RenderSetClipRect(_renderer, NULL);
}

guiPee::~guiPee()
{
	// TODO Auto-generated destructor stub
}

void guiPee::event(int x, int y, int button)
{
	guiBase::event(x, y, button);


	if (butDeezer->isClicked())
	{
		system("mpc stop");
		exit(33);
		//system("./PeeDump");
	}
	if (wndBtnBack->isClicked())
		popActiveWindows();

}
