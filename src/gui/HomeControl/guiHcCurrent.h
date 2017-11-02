/*
 * guiHcCurrent.h
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_HOMECONTROL_guiHcCurrent_H_
#define SRC_GUI_HOMECONTROL_guiHcCurrent_H_

#include <guiListItem.h>
#include <guiButton.h>

class guiHcCurrent: public guiListItem {
public:
	guiHcCurrent(char* name);
	virtual ~guiHcCurrent();

	void render();
	void event(int x, int y, int button);
	char* 	_Name;

};

#endif /* SRC_GUI_HOMECONTROL_guiHcCurrent_H_ */
