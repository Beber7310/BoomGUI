/*
 * tools.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_TOOLS_TOOLS_H_
#define SRC_TOOLS_TOOLS_H_

#include <vector>

#include "guiListPodcast.h"
#include "guiItemPodcast.h"

#include "peePodcast.h"
#include "peePodcastTrack.h"


void toolsLoadAlbum (SDL_Renderer *renderer,guiList* mainWin,guiAlbumFilter* wndFilter);
void toolsLoadPlaylist (SDL_Renderer *renderer,guiList* mainWin);
void toolsLoadRadio(SDL_Renderer *renderer, guiList* mainWin);

int toolsCleanUTF8(char* szString);
bool  toolsDownloadExist(char * localPath);

using namespace std;

void toolsUpdateUserPodcastTracks(vector<peePodcastTrack*>* podcastList,peePodcast* pParent,char* htmlSource);
std::vector<peePodcast*>*  toolsGetPodcast(void);

#endif /* SRC_TOOLS_TOOLS_H_ */
