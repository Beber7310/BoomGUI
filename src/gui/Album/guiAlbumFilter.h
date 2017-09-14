/*
 * guiAlbumFilter.h
 *
 *  Created on: Sep 14, 2017
 *      Author: dosdab
 */

#ifndef SRC_GUI_ALBUM_GUIALBUMFILTER_H_
#define SRC_GUI_ALBUM_GUIALBUMFILTER_H_

#include <guiBase.h>
#include <guiList.h>
#include <guiButton.h>

class guiAlbumFilter: public guiBase {
public:
	guiAlbumFilter();
	guiAlbumFilter(SDL_Renderer *renderer);
	virtual ~guiAlbumFilter();

	void event(int x, int y, int button);

	guiList* wndLstFlt;
	guiButton* wndBtnBack;
};

#endif /* SRC_GUI_ALBUM_GUIALBUMFILTER_H_ */
