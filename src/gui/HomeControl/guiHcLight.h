/*
 * guiHcLight.h
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_HOMECONTROL_guiHcLight_H_
#define SRC_GUI_HOMECONTROL_guiHcLight_H_

#include <guiListItem.h>
#include <guiButton.h>

class guiHcLight: public guiListItem {
public:
	guiHcLight(SDL_Renderer *renderer,char* name,int index);
	virtual ~guiHcLight();

	void render(SDL_Renderer *renderer);
	void event(int x, int y, int button);
	char* 	_Name;
	int 	_index;

	SDL_Texture * _textAlbum;
	SDL_Rect  _textSize;


	guiButton* 		wndBtnOn;
	guiButton* 		wndBtnOff;
};

#endif /* SRC_GUI_HOMECONTROL_guiHcLight_H_ */
