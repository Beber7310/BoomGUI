/*
 * guiHomeControl.cpp
 *
 *  Created on: 20 sept. 2017
 *      Author: Bertrand
 */

#include <HomeControl/guiHomeControl.h>

guiHomeControl::guiHomeControl() {
	// TODO Auto-generated constructor stub
}

guiHomeControl::guiHomeControl(SDL_Renderer * renderer) {
	// TODO Auto-generated constructor stub
	wndBtnBack = new guiButton(renderer, 0, 0, 100, 100, "res/back.png");
	AddChild(wndBtnBack);
}

guiHomeControl::~guiHomeControl() {
	// TODO Auto-generated destructor stub
}

void guiHomeControl::event(int x, int y, int button) {
	guiBase::event(x, y, button);

	if (wndBtnBack->isClicked())
		popActiveWindows();


}
