/*
 * configuration.h
 *
 *  Created on: 9 sept. 2017
 *      Author: Bertrand
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_

#define WALLPAPER	"res/wallpaper2.jpg"


 #define SALON
//#define CHAMBRE_B
//#define CHAMBRE_D
// #define CHAMBRE_V
// #define MAMIE

#ifdef SALON
	#define SCREEN_7P
	#define _CONF_HOMECONTROL_EN
	#define _CONF_PODCAST_EN
	#define _CONF_EXT_HDD
#endif
#ifdef CHAMBRE_B
	#define SCREEN_5P
	#define _CONF_PODCAST_EN
#endif
#ifdef CHAMBRE_V
	#define SCREEN_5P
#endif
#ifdef CHAMBRE_D
	#define SCREEN_5P
	#define _CONF_PODCAST_EN
#endif
#ifdef MAMIE
	#define SCREEN_7P
#endif

#ifdef SCREEN_7P
	#define	SCREEN_WIDTH	600
	#define	SCREEN_HEIGHT	1024
#endif
#ifdef SCREEN_5P
	#define	SCREEN_WIDTH	480
	#define	SCREEN_HEIGHT	800
#endif

#ifndef __RASP__

	#define ALBUM_DIR	  	"/media/pi/D5A1-3B4E/album/"
	#define PLAYLIST_DIR 	"/media/pi/D5A1-3B4E/playlists/"
	#define PODCAST_DIR  	"/media/pi/D5A1-3B4E/podcast/"
	#define BASE_DIR  		"/media/pi/D5A1-3B4E/"
#else
#ifdef _CONF_EXT_HDD
	#define ALBUM_DIR	  	"/mnt/hdd/album/"
	#define PLAYLIST_DIR  	"/mnt/hdd/playlists/"
	#define PODCAST_DIR  	"/mnt/hdd/podcast/"
	#define BASE_DIR  		"/mnt/hdd/"
#else
	#define ALBUM_DIR	  	"/home/pi/projects/audio/album/"
	#define PLAYLIST_DIR  	"/home/pi/projects/audio/playlists/"
	#define PODCAST_DIR  	"/home/pi/projects/audio/podcast/"
	#define BASE_DIR  		"/home/pi/projects/audio/"
#endif
#endif



#endif /* SRC_CONFIGURATION_H_ */
