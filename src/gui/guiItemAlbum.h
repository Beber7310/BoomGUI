/*
 * guiItemAlbum.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_GUIITEMALBUM_H_
#define SRC_GUIITEMALBUM_H_


#include "SDL.h"
#include <SDL_image.h>
#include "guiListItem.h"
#include "SDL2_gfxPrimitives.h"


class guiItemAlbum : public guiListItem
{
public:
  guiItemAlbum ();
  guiItemAlbum (SDL_Renderer * renderer,char* fileName);
  virtual
  ~guiItemAlbum ();

  void
  render (SDL_Renderer *renderer);


  SDL_Texture * texCover;
  char* _Artiste;
  char* _AlbumName;
};

#endif /* SRC_GUIITEMALBUM_H_ */
