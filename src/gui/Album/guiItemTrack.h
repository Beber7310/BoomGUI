/*
 * guiItemTrack.h
 *
 *  Created on: 10 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_GUIITEMTRACK_H_
#define SRC_GUI_GUIITEMTRACK_H_

#include <guiListItem.h>

class guiItemTrack : public guiListItem {
  public:
	guiItemTrack ();
	guiItemTrack(char* name);
	virtual
	~guiItemTrack ();

	char* _szName;
	char* _szPath;
};

#endif /* SRC_GUI_GUIITEMTRACK_H_ */

