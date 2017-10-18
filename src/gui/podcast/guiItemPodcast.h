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
#include "guiItemPodcastTracks.h"
#include "guiListPodcastTracks.h"
#include "SDL2_gfxPrimitives.h"

class guiItemPodcast: public guiListItem {
public:
	guiItemPodcast();
	guiItemPodcast(char* title,peePodcast* pPodcast);
	virtual
	~guiItemPodcast();

	guiItemPodcastTracks* GetTrackByTitle(const char* title);

	void render();
	void event(int x, int y, int button);

	void play();

	void setTitle(const char* title);
	void setImage(const char* img);


	SDL_Texture * 	_texCover;

	char* 	_htmlSource;
	char* 	_titleUTF8;
	char* 	_directory;
	char* 	_coverHtmplPath;

	guiList* 		_TrackList;
	SDL_Rect  		_textSize;
	guiListPodcastTracks* _wndPodcastTracks;

};
#endif /* SRC_guiItemPodcast_H_ */
