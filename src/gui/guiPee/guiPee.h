/*
 * guiPee.h
 *
 *  Created on: Sep 13, 2017
 *      Author: dosdab
 */

#ifndef SRC_GUI_guiPee_H_
#define SRC_GUI_guiPee_H_

#include <guiBase.h>
#include <guiButton.h>
#include <guiList.h>
#include <guiPlayer.h>

class guiPee: public guiBase {
public:
	guiPee();

	virtual ~guiPee();
	void event(int x, int y, int button);
	void render();

	guiButton* wndBtnBack;

	guiButton* butDeezer;





	SDL_Rect _texSize;
};

#endif /* SRC_GUI_guiPee_H_ */
