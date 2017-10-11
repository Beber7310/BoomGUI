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
	guiButton(int x,int y,int w,int h,char* szImg);
	virtual ~guiButton();
	void render ();
	void event(int x, int y, int button);
	SDL_Texture * _texButton;
	bool isClicked();
	bool enable(bool on);
private:
	int _click;
	bool _enabled;
};

#endif /* SRC_GUI_GUIBUTTON_H_ */
