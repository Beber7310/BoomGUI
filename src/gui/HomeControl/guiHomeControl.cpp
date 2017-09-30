/*
 * guiHomeControl.cpp
 *
 *  Created on: 20 sept. 2017
 *      Author: Bertrand
 */

#include <guiHomeControl.h>
#include "homeControl.h"



guiHomeControl::guiHomeControl() {
	// TODO Auto-generated constructor stub
}

guiHomeControl::guiHomeControl(SDL_Renderer * renderer) {
	// TODO Auto-generated constructor stub
	wndBtnBack = new guiButton(renderer, 0, 0, 100, 100, "res/back.png");
	AddChild(wndBtnBack);

	wndLstHc = new guiList();
	AddChild(wndLstHc);
	wndLstHc->setRect(0, 100, 600, 924);

	wndLstHc->AddChild(new guiHcCurrent(renderer,"Courant"));

	wndLstHc->AddChild(new guiHcRadiateur(renderer,"Cuisine",HC_HEATER_CUISINE));
	wndLstHc->AddChild(new guiHcRadiateur(renderer,"Salon",HC_HEATER_SALON));
	wndLstHc->AddChild(new guiHcRadiateur(renderer,"Barnabé",HC_HEATER_BARNABE));
	wndLstHc->AddChild(new guiHcRadiateur(renderer,"Daphnée",HC_HEATER_DAPHNEE));
	wndLstHc->AddChild(new guiHcThermometre(renderer,"Victor",HC_TEMP_VICTOR));
	wndLstHc->AddChild(new guiHcRadiateur(renderer,"HomeCinema",HC_HEATER_HOMECINEMA));

	wndLstHc->AddChild(new guiHcLight(renderer,"VMC",HC_LIGHT_VMC));
	wndLstHc->AddChild(new guiHcLight(renderer,"Disco",HC_LIGHT_DISCO));

	homeControlLaunch();
}

guiHomeControl::~guiHomeControl() {
	// TODO Auto-generated destructor stub
}

void guiHomeControl::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();


}

