/*
 * guiItemPodcast.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_guiItemPodcast_H_
#define SRC_guiItemPodcast_H_

#include "SDL.h"
#include <SDL_image.h>
#include "guiBase.h"
#include "guiListItem.h"
#include "guiList.h"
#include "guiAlbumFilter.h"
#include "SDL2_gfxPrimitives.h"

class guiItemPodcast: public guiListItem {
public:
	guiItemPodcast();
	guiItemPodcast(SDL_Renderer * renderer, char* htmlSource);
	virtual
	~guiItemPodcast();

	void render();
	void event(int x, int y, int button);

	void play();

	void setTitle(const char* title);
	void setImage(const char* img);


	SDL_Texture * 	_texCover;

	char* 	_htmlSource;
	char* 	_titleUTF8;
	char* 	_coverHtmplPath;

	guiList* 		_TrackList;
	SDL_Texture * 	_textAlbum;
	SDL_Rect  		_textSize;
};
#endif /* SRC_guiItemPodcast_H_ */
