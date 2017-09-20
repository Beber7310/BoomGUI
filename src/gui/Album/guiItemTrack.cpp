/*
 * guiItemTrack.cpp
 *
 *  Created on: 10 sept. 2017
 *      Author: Bertrand
 */
#include "configuration.h"
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <stdlib.h>
#include "string.h"
#include <guiItemTrack.h>

guiItemTrack::guiItemTrack() {
	// TODO Auto-generated constructor stub
	_szName = NULL;
}

guiItemTrack::guiItemTrack(char* name) {
	// TODO Auto-generated constructor stub

	_szName = NULL;
	_szPath = (char*) malloc(strlen(name) + 1);

	char *token;

	token = strtok(name, " ");

	if (token) {
		strcpy(_szPath, token);
	 }
//FIXME add name capture
}

guiItemTrack::~guiItemTrack() {
	// TODO Auto-generated destructor stub
}

