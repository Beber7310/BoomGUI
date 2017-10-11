/*
 * guiHcRadiateur.h
 *
 *  Created on: 29 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_HOMECONTROL_GUIHCRADIATEUR_H_
#define SRC_GUI_HOMECONTROL_GUIHCRADIATEUR_H_

#include <guiListItem.h>
#include <guiButton.h>

class guiHcRadiateur: public guiListItem {
public:
	guiHcRadiateur(char* name,int index);
	virtual ~guiHcRadiateur();

	void render( );
	void event(int x, int y, int button);
	char* 	_Name;
	int 	_index;

	float _targetTemp;

	guiButton* 		wndBtnPlus;
	guiButton* 		wndBtnMinus;
};

#endif /* SRC_GUI_HOMECONTROL_GUIHCRADIATEUR_H_ */
