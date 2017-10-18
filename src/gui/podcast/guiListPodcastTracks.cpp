/*
 * guiListPodcastTracks.cpp
 *
 *  Created on: 13 sept. 2017
 *      Author: Bertrand
 */

#include <podcast/guiListPodcastTracks.h>
#include "guiAlbumFilter.h"
#include "guiItemPodcast.h"
#include "guiManager.h"
#include "tools.h"
#include "podcastManager.h"

guiListPodcastTracks::guiListPodcastTracks() {
	// TODO Auto-generated constructor stub
	guiBase * pTemp;
	std::list<guiBase*>::iterator it;

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, 600, 924);

	wndBtnBack = new guiButton(0, 0, 100, 100, "res/back.png");

	AddChild(wndBtnBack);
	AddChild(wndLstAlb);
	_pPodcast=NULL;
}
guiListPodcastTracks::guiListPodcastTracks(peePodcast* pPodcast) {
	// TODO Auto-generated constructor stub
	guiBase * pTemp;
	std::list<guiBase*>::iterator it;

	wndLstAlb = new guiList();
	wndLstAlb->setRect(0, 100, 600, 924);

	wndBtnBack = new guiButton(0, 0, 100, 100, "res/back.png");

	AddChild(wndBtnBack);
	AddChild(wndLstAlb);

	_pPodcast=pPodcast;

	_sortName=pPodcast->_titleUTF8;

	pTemp = wndLstAlb->GetFirstChild(&it);
	while (pTemp) {

		pTemp = wndLstAlb->GetNextChild(&it);
	}
}


guiListPodcastTracks::~guiListPodcastTracks() {
	// TODO Auto-generated destructor stub
}

void guiListPodcastTracks::update() {

	if (lockPodcast(NULL)) {
		unsigned int ii;

		for (ii = 0; ii < _pPodcast->GetNbrTracks(); ii++) {
				guiBase * pTemp;
				std::list<guiBase*>::iterator it;
				bool skip = false;
				pTemp = wndLstAlb->GetFirstChild(&it);
				while (pTemp) {
					if(strcmp(_pPodcast->GetTracksAt(ii)->_title,((guiItemPodcastTracks*)pTemp)->_title)==0)
						skip=true;
					pTemp = wndLstAlb->GetNextChild(&it);
				}
				if (!skip)
					wndLstAlb->AddChild(new guiItemPodcastTracks(&(_pPodcast->GetTracksAt(ii)->_date),_pPodcast->GetTracksAt(ii)->_title,_pPodcast->GetTracksAt(ii)->_size,_pPodcast->GetTracksAt(ii)->_localPath));

		}

		releasePodcast();

		wndLstAlb->sortReverse();
	}

}

void guiListPodcastTracks::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();

}

