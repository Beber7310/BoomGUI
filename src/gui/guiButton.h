/*
 * guiButton.h
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#ifndef SRC_GUI_GUIBUTTON_H_
#define SRC_GUI_GUIBUTTON_H_

#include <guiBase.h>

class guiButton: public guiBase {
public:
	guiButton();
	guiButton(SDL_Renderer * renderer,int x,int y,int w,int h,char* szImg);
	virtual ~guiButton();
	void render (SDL_Renderer *renderer);
	void event(int x, int y, int button);
	SDL_Texture * _texButton;
	int _click;
};

#endif /* SRC_GUI_GUIBUTTON_H_ */
