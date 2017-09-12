/*
 * guiItemAlbum.cpp
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

guiItemAlbum::guiItemAlbum () {

}

guiItemAlbum::guiItemAlbum (SDL_Renderer * renderer, char* fileName) {
  char filePath[512];
  char str[512];

  char str_artiste[512];
  char str_album[512];
  char str_cover[512];

  _relWndRect.x = 10;
  _relWndRect.y = 10;
  _relWndRect.w = 600;
  _relWndRect.h = 200;
  // texCover = IMG_LoadTexture(renderer,"cover.jpeg");

  sprintf (filePath, "%s/%s", ALBUM_PLAYLIST_DIR, fileName);
  std::ifstream infile (filePath);
  std::string line;

  while (!infile.eof ()) {
	infile.getline (str, 500);
	printf ("%s\n",str);
	if (strstr (str, "<ARTISTE>") != NULL) {
	  strcpy (str_artiste, &str[strlen ("<ARTISTE>")]);
	  _Artiste = (char*) malloc (strlen (str_artiste)+1);
	  strcpy (_Artiste, str_artiste);

	  printf ("%s\n", str_artiste);
	}
	if (strstr (str, "<ALBUM>") != NULL) {
	  strcpy (str_album, &str[strlen ("<ALBUM>")]);
	  _AlbumName = (char*) malloc (strlen (str_album)+1);
	  strcpy (_AlbumName, str_album);
	  printf ("%s\n", str_album);
	}
	if (strstr (str, "<COVER>") != NULL) {
	  strcpy (str_cover, &str[strlen ("<COVER>")]);
	  printf ("%s\n", str_cover);
	  //FIXME free surface!!!!
	  SDL_Surface * image = IMG_Load (str_cover);
	  texCover = SDL_CreateTextureFromSurface (renderer, image);
	  SDL_FreeSurface(image);
	}

	_sortName=(char*) malloc (strlen (str_artiste)+strlen (str_album)+10);
	sprintf(_sortName,"%s_%s",str_artiste,str_album);




  }
  printf ("Exit\n");
}

guiItemAlbum::~guiItemAlbum () {
  // TODO Auto-generated destructor stub
}

void
guiItemAlbum::render (SDL_Renderer *renderer) {
  SDL_Rect coverRect;

  SDL_RenderSetClipRect (renderer, &_absWndRect);

  boxRGBA (renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0x0, 0x0, 0x00, 0xFF);
  rectangleRGBA (renderer, _absWndRect.x, _absWndRect.y, _absWndRect.x + _absWndRect.w, _absWndRect.y + _absWndRect.h, 0xFF, 0xFF, 0xFF, 0xFF);

  coverRect.x = _absWndRect.x;
  coverRect.y = _absWndRect.y;
  coverRect.w = _absWndRect.h;
  coverRect.h = _absWndRect.h;

  SDL_RenderCopy (renderer, texCover, NULL, &coverRect);

  stringRGBA(renderer, _absWndRect.h+10, _absWndRect.y+_absWndRect.h/4,_Artiste,0xFF,0xFF,0xFF,0xFF);
  stringRGBA(renderer, _absWndRect.h+10, _absWndRect.y+3*_absWndRect.h/4,_AlbumName,0xFF,0xFF,0xFF,0xFF);
}

void guiItemAlbum::play()
{
	system("mpc clear");

}
