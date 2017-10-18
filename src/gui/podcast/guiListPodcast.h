/*
 * guiListAlbum.h
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_ALBUM_GUILISTPODCAST_H_
#define SRC_GUI_ALBUM_GUILISTPODCAST_H_

#include <guiBase.h>
#include <guiList.h>
#include <guiButton.h>
#include <guiAlbumFilter.h>

class guiListPodcast: public guiBase {
public:
	guiListPodcast();

	virtual ~guiListPodcast();
	void event(int x, int y, int button);
	void parseGenre();
	void update();

	guiList* 		wndLstAlb;
	guiButton* 		wndBtnBack;

};

#endif /* SRC_GUI_ALBUM_guiListPodcast_H_ */
