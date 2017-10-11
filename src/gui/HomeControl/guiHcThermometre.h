/*
 * guiHcThermometre.h
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_HOMECONTROL_guiHcThermometre_H_
#define SRC_GUI_HOMECONTROL_guiHcThermometre_H_

#include <guiListItem.h>

class guiHcThermometre: public guiListItem {
public:
	guiHcThermometre(char* name,int index);
	virtual ~guiHcThermometre();

	void render();

	char* 	_Name;
	int 	_index;

};

#endif /* SRC_GUI_HOMECONTROL_guiHcThermometre_H_ */
