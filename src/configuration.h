/*
 * configuration.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_


#define WALLPAPER	"res/wallpaper2.jpg"
#ifndef __RASP__
#define ALBUM_DIR	  "album"
#define PLAYLIST_DIR  "playlists"
#else
#define ALBUM_DIR	  "/mnt/usbdrive/album"
#define PLAYLIST_DIR  "/mnt/usbdrive/playlists"
#endif

#endif /* SRC_CONFIGURATION_H_ */
