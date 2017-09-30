/*
 * guiHcRadiateur.h
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_HOMECONTROL_GUIHCRADIATEUR_H_
#define SRC_GUI_HOMECONTROL_GUIHCRADIATEUR_H_

#include <guiListItem.h>

class guiHcRadiateur: public guiListItem {
public:
	guiHcRadiateur(SDL_Renderer *renderer,char* name,int index);
	virtual ~guiHcRadiateur();

	void render(SDL_Renderer *renderer);

	char* 	_Name;
	int 	_index;

	SDL_Texture * _textAlbum;
	SDL_Rect  _textSize;
};

#endif /* SRC_GUI_HOMECONTROL_GUIHCRADIATEUR_H_ */
