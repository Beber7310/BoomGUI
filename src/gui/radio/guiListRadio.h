/*
 * guiListRadio.h
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_ALBUM_guiListRadio_H_
#define SRC_GUI_ALBUM_guiListRadio_H_

#include <guiList.h>
#include <guiButton.h>
#include <guiAlbumFilter.h>

class guiListRadio: public guiBase {
public:
	guiListRadio();
	virtual ~guiListRadio();
	void event(int x, int y, int button);
	void parseGenre();
	//void render();

	guiList* 		wndLstAlb;
	guiButton* 		wndBtnBack;
};

#endif /* SRC_GUI_ALBUM_guiListRadio_H_ */
