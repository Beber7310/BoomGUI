/*
 * guiListAlbum.h
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_ALBUM_GUILISTALBUM_H_
#define SRC_GUI_ALBUM_GUILISTALBUM_H_

#include <guiList.h>
#include <guiButton.h>
#include <guiAlbumFilter.h>

class guiListAlbum: public guiBase {
public:
	guiListAlbum();
	virtual ~guiListAlbum();
	void event(int x, int y, int button);
	void parseGenre();
	//void render();

	guiList* 		wndLstAlb;
	guiAlbumFilter* wndAlbFlt;
	guiButton* 		wndBtnBack;
	guiButton* 		wndBtnFilter;
};

#endif /* SRC_GUI_ALBUM_GUILISTALBUM_H_ */
