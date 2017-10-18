/*
 * guiListAlbum.h
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_ALBUM_guiListPodcastTracks_H_
#define SRC_GUI_ALBUM_guiListPodcastTracks_H_

#include <guiBase.h>
#include <guiList.h>
#include <guiButton.h>
#include <guiAlbumFilter.h>
#include <peePodcast.h>

class guiListPodcastTracks: public guiListItem {
public:
	guiListPodcastTracks(peePodcast* pPodcast);
	guiListPodcastTracks();


	virtual ~guiListPodcastTracks();
	void event(int x, int y, int button);
	void parseGenre();
	void update();

	guiList* 		wndLstAlb;
	guiButton* 		wndBtnBack;
	peePodcast* 	_pPodcast;

};

#endif /* SRC_GUI_ALBUM_guiListPodcastTracks_H_ */
