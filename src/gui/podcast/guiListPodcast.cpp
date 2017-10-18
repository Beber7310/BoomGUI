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
#include "podcastManager.h"

guiListPodcast::guiListPodcast() {
	// TODO Auto-generated constructor stub
	guiBase * pTemp;
	std::list<guiBase*>::iterator it;

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, 600, 924);

	wndBtnBack = new guiButton(0, 0, 100, 100, "res/back.png");

	AddChild(wndBtnBack);
	AddChild(wndLstAlb);

	pTemp = wndLstAlb->GetFirstChild(&it);
	while (pTemp) {

		pTemp = wndLstAlb->GetNextChild(&it);
	}
}

guiListPodcast::~guiListPodcast() {
	// TODO Auto-generated destructor stub
}

void guiListPodcast::update() {

	std::vector<peePodcast*>* pPodcast;
	if (lockPodcast(&pPodcast)) {
		unsigned int ii;

		for (ii = 0; ii < pPodcast->size(); ii++) {
			if (pPodcast->at(ii)->_titleUTF8) {
				guiBase * pTemp;
				std::list<guiBase*>::iterator it;
				bool skip = false;
				pTemp = wndLstAlb->GetFirstChild(&it);
				while (pTemp) {
					if(strcmp(pPodcast->at(ii)->_titleUTF8,pTemp->_sortName)==0)
						skip=true;
					pTemp = wndLstAlb->GetNextChild(&it);
				}
				if (!skip)
					wndLstAlb->AddChild(new guiItemPodcast(pPodcast->at(ii)->_titleUTF8,pPodcast->at(ii)));
			}
		}

		releasePodcast();

		wndLstAlb->sort();
	}

}

void guiListPodcast::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

}

