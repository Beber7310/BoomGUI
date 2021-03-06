/*
 * guiItemRadio.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_guiItemRadio_H_
#define SRC_guiItemRadio_H_

#include "SDL.h"
#include <SDL_image.h>
#include "guiBase.h"
#include "guiListItem.h"
#include "guiList.h"
#include "SDL2_gfxPrimitives.h"

class guiItemRadio: public guiListItem {
public:
	guiItemRadio(char* mp3,char* NiceName,char* cover);

	virtual
	~guiItemRadio();

	void render();
	void event(int x, int y, int button);

	void play();

	SDL_Texture * _texCover;
	char* _mp3;
	char* _NiceName;
	char* _cover;


};
#endif /* SRC_guiItemRadio_H_ */
