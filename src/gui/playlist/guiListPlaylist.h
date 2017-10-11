/*
 * guiListPlaylist.h
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_ALBUM_guiListPlaylist_H_
#define SRC_GUI_ALBUM_guiListPlaylist_H_

#include <guiList.h>
#include <guiButton.h>
#include <guiAlbumFilter.h>

class guiListPlaylist: public guiBase {
public:
	guiListPlaylist();
	virtual ~guiListPlaylist();
	void event(int x, int y, int button);
	void parseGenre();

	guiList* 		wndLstPlaylist;
	guiButton* 		wndBtnBack;

};

#endif /* SRC_GUI_ALBUM_guiListPlaylist_H_ */
