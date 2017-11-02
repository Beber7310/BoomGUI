/*
 * guiHomeControl.cpp
 *
 *  Created on: 20 sept. 2017
 *      Author: Bertrand
 */

#include <guiHomeControl.h>
#include "homeControl.h"
#include "configuration.h"



guiHomeControl::guiHomeControl() {
	// TODO Auto-generated constructor stub
	wndBtnBack = new guiButton( 0, 0, 100, 100, "res/back.png");
	AddChild(wndBtnBack);

	wndLstHc = new guiList();
	AddChild(wndLstHc);
	wndLstHc->setRect(0, 100, SCREEN_WIDTH, SCREEN_HEIGHT-100);

	wndLstHc->AddChild(new guiHcCurrent("Courant"));
	wndLstHc->AddChild(new guiHcThermometre("Exterieur",HC_TEMP_EXTERIEUR));

	wndLstHc->AddChild(new guiHcRadiateur("Cuisine",HC_HEATER_CUISINE));
	wndLstHc->AddChild(new guiHcRadiateur("Salon",HC_HEATER_SALON));
	wndLstHc->AddChild(new guiHcRadiateur("Barnabé",HC_HEATER_BARNABE));
	wndLstHc->AddChild(new guiHcRadiateur("Daphnée",HC_HEATER_DAPHNEE));
	wndLstHc->AddChild(new guiHcThermometre("Victor",HC_TEMP_VICTOR));
	wndLstHc->AddChild(new guiHcRadiateur("HomeCinema",HC_HEATER_HOMECINEMA));



	wndLstHc->AddChild(new guiHcThermometre("Garage",HC_TEMP_GARAGE));
	wndLstHc->AddChild(new guiHcThermometre("Parent",HC_TEMP_PARENT));

	wndLstHc->AddChild(new guiHcLight("VMC",HC_LIGHT_VMC));
	wndLstHc->AddChild(new guiHcLight("Disco",HC_LIGHT_DISCO));
	wndLstHc->AddChild(new guiHcLight("Atelier",HC_LIGHT_ETABLI));
	wndLstHc->AddChild(new guiHcLight("Garage",HC_LIGHT_GARAGE));

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

