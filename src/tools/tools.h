/*
 * tools.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_TOOLS_TOOLS_H_
#define SRC_TOOLS_TOOLS_H_

#include "guiListPodcast.h"
#include "guiItemPodcast.h"

void toolsLoadAlbum (SDL_Renderer *renderer,guiList* mainWin,guiAlbumFilter* wndFilter);
void toolsLoadPlaylist (SDL_Renderer *renderer,guiList* mainWin);
void toolsGetPodcast(SDL_Renderer *renderer, guiListPodcast* pListPodcast);
void toolsUpdateUserPodcastTracks(guiItemPodcast* pPodcast);
#endif /* SRC_TOOLS_TOOLS_H_ */
