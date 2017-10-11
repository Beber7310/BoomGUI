/*
 * guiListPodcast.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include <podcast/guiListPodcast.h>
#include "guiAlbumFilter.h"
#include "guiItemPodcast.h"
#include "guiManager.h"
#include "tools.h"

guiListPodcast::guiListPodcast() {
	// TODO Auto-generated constructor stub
	guiBase * pTemp;
	std::list<guiBase*>::iterator it;

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, 600, 924);

	wndBtnBack = new guiButton(0, 0, 100, 100, "res/back.png");

	AddChild(wndBtnBack);
	AddChild(wndLstAlb);



	toolsGetPodcast(_renderer, this);

	pTemp = wndLstAlb->GetFirstChild(&it);
	while (pTemp) {
		toolsUpdateUserPodcastTracks((guiItemPodcast*) pTemp);
		pTemp = wndLstAlb->GetNextChild(&it);
	}
}

guiListPodcast::~guiListPodcast() {
	// TODO Auto-generated destructor stub
}

void guiListPodcast::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

}

