/*
 * guiItemAlbum.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUIITEMALBUM_H_
#define SRC_GUIITEMALBUM_H_

#include "SDL.h"
#include <SDL_image.h>
#include "guiBase.h"
#include "guiListItem.h"
#include "guiList.h"
#include "guiAlbumFilter.h"
#include "SDL2_gfxPrimitives.h"

class guiItemAlbum: public guiListItem {
public:
	guiItemAlbum(char* fileName, guiAlbumFilter* wndFilter);
	virtual
	~guiItemAlbum();

	void render();
	void event(int x, int y, int button);

	void play();

	SDL_Texture * _texCover;
	char* _Artiste;
	char* _AlbumName;
	guiItemFilter* _pGenre;
	guiList* _TrackList;
};
#endif /* SRC_GUIITEMALBUM_H_ */
