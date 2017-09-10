/*
 * tools.cpp
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */
#include "configuration.h"
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include "string.h"
#include "guiList.h"
#include "guiItemAlbum.h"

using namespace std;



void
toolsLoadAlbum (SDL_Renderer *renderer,guiList* mainWin) {
  int ii=0;

  DIR *d;
  struct dirent *dir;
  d = opendir (ALBUM_PLAYLIST_DIR);
  if (d) {
	while (((dir = readdir (d)) != NULL)&&(ii<10000)) {
	  ii++;
	  if (dir->d_type == DT_REG) {
		if (strstr (dir->d_name, ".piz") != NULL) {
		  printf ("%s\n", dir->d_name);
		  mainWin->AddChild(new guiItemAlbum(renderer,dir->d_name));
		  printf ("Done %s\n", dir->d_name);
		}
	  }
	}

	closedir (d);
  }
}

/* Returns a list of files in a directory (except the ones that begin with a dot) */

void
GetFilesInDirectory () {

} // GetFilesInDirectory
