/*
 * guiItemFilter.h
 *
 *  Created on: 15 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_ALBUM_GUIITEMFILTER_H_
#define SRC_GUI_ALBUM_GUIITEMFILTER_H_

#include <guiBase.h>
#include <guiListItem.h>

class guiItemFilter: public guiListItem {
public:
	guiItemFilter();
	guiItemFilter(SDL_Renderer *renderer,char* genre);
	virtual ~guiItemFilter();
	void event(int x, int y, int button);
	void render(SDL_Renderer *renderer);
	bool isClicked();

	char* _szGenre;
	bool _selected;
	int _click;
	SDL_Texture * _textFilter;
	SDL_Rect _textSize;
};

#endif /* SRC_GUI_ALBUM_GUIITEMFILTER_H_ */
