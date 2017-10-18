/*
 * guiItemPodcastTracks.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_guiItemPodcastTracks_H_
#define SRC_guiItemPodcastTracks_H_

#include "SDL.h"
#include <SDL_image.h>
#include <time.h>
#include "guiBase.h"
#include "guiListItem.h"
#include "guiList.h"
#include "guiAlbumFilter.h"
#include "SDL2_gfxPrimitives.h"


class guiItemPodcastTracks: public guiListItem {
public:
	guiItemPodcastTracks();
	guiItemPodcastTracks(tm* date, const char* title,int size,char* localPath);
	virtual	~guiItemPodcastTracks();

	void render();
	void event(int x, int y, int button);



	tm		_date;
	char*	_strtime;
	char*	_title;
	char* 	_localPath;
	bool 	_downloaded;
	int 	_size;

};
#endif /* SRC_guiItemPodcastTracks_H_ */
