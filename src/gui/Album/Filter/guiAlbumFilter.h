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
#include <guiItemFilter.h>

class guiAlbumFilter: public guiBase {
public:
	guiAlbumFilter();
	virtual ~guiAlbumFilter();
	void selectAll(bool sel);

	void event(int x, int y, int button);
	guiItemFilter* AddFilter(char* szGenre);
	guiList* wndLstFlt;
	guiButton* wndBtnBack;
};

#endif /* SRC_GUI_ALBUM_GUIALBUMFILTER_H_ */
