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

class guiHomeControl: public guiBase {
public:
	guiHomeControl();
	guiHomeControl(SDL_Renderer * renderer);
	virtual ~guiHomeControl();
	void event(int x, int y, int button);

	guiButton* 		wndBtnBack;
};

#endif /* SRC_GUI_HOMECONTROL_GUIHOMECONTROL_H_ */
