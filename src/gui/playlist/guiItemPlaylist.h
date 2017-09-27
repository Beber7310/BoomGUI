/*
 * guiItemPlaylist.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_guiItemPlaylist_H_
#define SRC_guiItemPlaylist_H_

#include "SDL.h"
#include <SDL_image.h>
#include "guiBase.h"
#include "guiListItem.h"
#include "guiList.h"
#include "guiAlbumFilter.h"
#include "SDL2_gfxPrimitives.h"

class guiItemPlaylist: public guiListItem {
public:
	guiItemPlaylist();
	guiItemPlaylist(SDL_Renderer * renderer, char* fileName);
	virtual
	~guiItemPlaylist();

	void render(SDL_Renderer *renderer);
	void event(int x, int y, int button);

	void play();

	SDL_Texture * _texCover;
	char* _PlaylistName;


	guiList* _TrackList;
	SDL_Texture * _textAlbum;
	SDL_Rect  _textSize;
};
#endif /* SRC_guiItemPlaylist_H_ */
