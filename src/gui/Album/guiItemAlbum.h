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
#include "guiAlbumFilter.h"
#include "SDL2_gfxPrimitives.h"

class guiItemAlbum: public guiListItem {
public:
	guiItemAlbum();
	guiItemAlbum(SDL_Renderer * renderer, char* fileName,guiAlbumFilter* wndFilter);
	virtual
	~guiItemAlbum();

	void render(SDL_Renderer *renderer);
	void event(int x, int y, int button);

	void play();

	SDL_Texture * texCover;
	char* _Artiste;
	char* _AlbumName;
	guiItemFilter* _pGenre;
	guiList* _TrackList;
	SDL_Texture * _textAlbum;
	SDL_Rect  _textSize;
};
#endif /* SRC_GUIITEMALBUM_H_ */
