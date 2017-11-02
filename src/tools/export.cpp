/*
 * export.cpp
 *
 *  Created on: 20 oct. 2017
 *      Author: Bertrand
 */

#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include "string.h"
#include <libgen.h>

int mp3export(char* filePath) {
	char str[512];
	char cmd[512];
	char dir[512];
	char piz[512];
	char* token;

	// texCover = IMG_LoadTexture(renderer,"cover.jpeg");

	std::ifstream infile(filePath);
	std::string line;
	if(!infile.is_open())
	{
		printf("Error opening %s\n",filePath);
		return -1;
	}

	while (!infile.eof()) {
		infile.getline(str, 500);

		if (strstr(str, "<PLAYLIST>") != NULL) {

		} else if (strstr(str, "<COVER>") != NULL) {
			sprintf(dir,"%s",dirname(&str[strlen("<COVER>")]));
			printf("DIRECTORY %s\n",dir);

			sprintf(cmd,"mkdir -p /mnt/hdd/export/%s",dir);
			printf("%s\n",cmd);
			system(cmd);

			sprintf(cmd,"cp  /mnt/hdd/%s/* /mnt/hdd/export/%s",dir,dir);
			printf("%s\n",cmd);
			system(cmd);

			sprintf(piz,"%s",&filePath[strlen("/mnt/hdd")]);
			printf("PIZ %s\n",piz);

			sprintf(cmd,"mkdir -p \"/mnt/hdd/export/%s\"",dirname(piz));
			printf("%s\n",cmd);
			system(cmd);

			sprintf(piz,"%s",&filePath[strlen("/mnt/hdd")]);
			printf("PIZ %s\n",piz);

			sprintf(cmd,"cp  \"/mnt/hdd/%s\" \"/mnt/hdd/export/%s\"",piz,piz);
			printf("%s\n",cmd);
			system(cmd);

		} else if (strstr(str, "<ARTISTE>") != NULL) {

		} else if (strstr(str, "<ALBUM>") != NULL) {

		} else if (strstr(str, "<GENRE>") != NULL) {

		} else {
			if (strlen(str) > 10) //FIXME add keyword
			{
				token = strtok(str, " ");

				/*sprintf(cmd,"cp /mnt/usbdrive/%s /mnt/usbdrive/export/%s",token,token);
				printf("%s\n",cmd);
				system(cmd);*/
			}
		}

	}
}
