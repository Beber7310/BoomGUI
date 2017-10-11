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
	guiItemPlaylist(char* fileName);
	virtual
	~guiItemPlaylist();

	void render();
	void event(int x, int y, int button);

	void play();

	SDL_Texture * _texCover;
	char* _PlaylistName;


	guiList* _TrackList;

};
#endif /* SRC_guiItemPlaylist_H_ */
