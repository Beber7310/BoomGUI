#include <stdio.h>
#include <fcntl.h>
#include <podcastManager.h>
#include <unistd.h>
#include <vector>

#include "guiManager.h"
#include "export.h"
#include "configuration.h"

using namespace std;

int main (int argc, char* argv[]) {

	//
	//  	./BoomGui  /mnt/usbdrive/playlists/Special\ girl.piz
	//

	if(argc>1)
	{
		printf("Export %s\n",argv[1]);
		return mp3export(argv[1]);

	}
	system("mpc update");
#ifdef _CONF_PODCAST_EN
	podcastTask();
#endif
	rendertask();

}

