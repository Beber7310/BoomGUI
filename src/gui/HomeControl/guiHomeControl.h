/*
 * guiHomeControl.h
 *
 *  Created on: 20 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUI_HOMECONTROL_GUIHOMECONTROL_H_
#define SRC_GUI_HOMECONTROL_GUIHOMECONTROL_H_

#include <guiBase.h>
#include <guiButton.h>
#include <guiList.h>
#include <guiHcRadiateur.h>
#include <guiHcThermometre.h>
#include <guiHcLight.h>
#include <guiHcCurrent.h>

#include "homeControl.h"


class guiHomeControl: public guiBase {
public:
	guiHomeControl();
	virtual ~guiHomeControl();
	void event(int x, int y, int button);

	guiList* 		wndLstHc;
	guiButton* 		wndBtnBack;

};

#endif /* SRC_GUI_HOMECONTROL_GUIHOMECONTROL_H_ */
