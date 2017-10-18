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
#include "http_fetcher.h"
#include "tinyxml2.h"
#include "string.h"
#include "guiList.h"
#include "guiItemAlbum.h"
#include "guiAlbumFilter.h"
#include "guiItemPlaylist.h"
#include "guiListPodcast.h"
#include "guiItemPodcast.h"
#include "configuration.h"
#include "unistd.h"

#include "peePodcast.h"
#include "peePodcastTrack.h"

#include <vector>

using namespace std;
using namespace tinyxml2;

/*
 *
 * Dont forget to free(fileBuf); !!!
 */
char * toolsGetHtml(char *url) {
#ifdef __RASP__
	int ret=NULL;
	//char *url = "http://api.deezer.com/user/92847721/albums&output=xml";   	/* Pointer to the url you want */
	char *fileBuf; /* Pointer to downloaded data */

	ret = http_fetch(url, &fileBuf); /* Downloads page */
	if(ret == -1) /* All HTTP Fetcher functions return */
	{
		//	http_perror("http_fetcha");		/*	-1 on error. */
		printf("toolsGetHtml error\n");
		return NULL;
	}
	else
	{
		//	printf("Page successfully downloaded. (%s)\n", url);
		//	printf("Page successfully downloaded. (%s)\n", fileBuf);

	}

	/*
	 * Now we have the page downloaded and stored in fileBuf, we could save it
	 *	to disk, print it out, etc.  Notice that http_fetch() is the primary
	 *	function of the library, and for a barebones request is the only
	 *	function you need (in conjunction with http_perror).  With HTTP Fetcher
	 *	you can also set User Agent, referer, and timeout values, parse
	 *	filenames, etc... see the header file (http_fetcher.h) for function
	 *	usage/information.
	 */

	return fileBuf;
#else
	return NULL;
#endif
}

void toolsLoadAlbum(SDL_Renderer *renderer, guiList* mainWin, guiAlbumFilter* wndFilter) {
	int ii = 0;

	DIR *d;
	struct dirent *dir;
	d = opendir(ALBUM_DIR);
	if (d) {
		while (((dir = readdir(d)) != NULL) && (ii < 1000)) {
			ii++;
			if (dir->d_type == DT_REG) {
				if (strstr(dir->d_name, ".piz") != NULL) {

					mainWin->AddChild(new guiItemAlbum(dir->d_name, wndFilter));

				}
			}
		}

		closedir(d);
	}
}

void toolsLoadPlaylist(SDL_Renderer *renderer, guiList* mainWin) {
	int ii = 0;

	DIR *d;
	struct dirent *dir;
	d = opendir(PLAYLIST_DIR);
	if (d) {
		while (((dir = readdir(d)) != NULL) && (ii < 1000)) {
			ii++;
			if (dir->d_type == DT_REG) {
				if (strstr(dir->d_name, ".piz") != NULL) {
					printf("Opening %s\n", dir->d_name);
					mainWin->AddChild(new guiItemPlaylist(dir->d_name));

				}
			}
		}

		closedir(d);
	}
}
/* Returns a list of files in a directory (except the ones that begin with a dot) */

int toolsCleanUTF8(char* szString)
{
	int len=strlen(szString);
	int dst=0;
	for(int i=0;i<len;i++)
	{
		if((szString[i]&0xF0)==0xC0)
		{
			i++;

			if((szString[i]==0xa8)||(szString[i]==0xa9)||(szString[i]==0xaa)||(szString[i]==0xab) ) //223 -> é  //232 -> è
			{
				szString[dst]='e';
			}
			else if((szString[i]==0xa7)) //221 -> ç
			{
				szString[dst]='c';
			}
			else if((szString[i]==0xa0)||(szString[i]==0xa1)||(szString[i]==0xa2))
			{
				szString[dst]='a';
			}
			else if((szString[i]==0xb2)||(szString[i]==0xb3)||(szString[i]==0xb4))
			{
				szString[dst]='o';
			}
			else if((szString[i]==0xaf))
			{
				szString[dst]='i';
			}
			else if((szString[i]==0xbb)||(szString[i]==0x80)||(szString[i]==0xae))
			{
				szString[dst]=' ';
			}
			else
			{
				i++;
				//printf("Missed! 0x%x : %s\n",szString[i],szString);
			}
		}
		else if((szString[i]&0xF0)==0xE0)
		{
			i+=3;
			szString[dst]=' ';
		}
		else if((szString[i]&0xF0)==0xF0)
		{
			i+=4;
			szString[dst]=' ';
		}

		else if(isalnum(szString[i]) || szString[i]==' '|| szString[i]=='/'|| szString[i]=='.')
		{
			szString[dst]=szString[i];
		}
		else
		{
			szString[dst]=' ';
		}


		dst++;
	}
	szString[dst]=0;

	while(szString[strlen(szString)-1]==' ')
		szString[strlen(szString)-1]=0;

	dst=0;
	for(unsigned int ii=0;ii<strlen(szString)-1;ii++)
	{
		if(szString[ii] ==' ' && szString[ii+1] == '/')
		{
			ii++;
		}
		szString[dst]=szString[ii];
		dst++;
	}

	return 0;
}

std::vector<peePodcast*>*  toolsGetPodcast(void)
				{
	FILE *stream;
	char *line = NULL;
	char* podCast;
	size_t len = 0;
	ssize_t read;
	std::vector<peePodcast*>*retPodcast =new std::vector<peePodcast*>();


	stream = fopen("/home/pi/projects/res/podcast.conf", "r");
	if (stream == NULL)
	{
		printf("Unable to open /home/pi/projects/res/podcast.conf\n");
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&line, &len, stream)) != -1) {
		if(strncmp("lpodcast:",line,strlen("lpodcast:"))==0)
		{
			podCast=&line[strlen("lpodcast:")];
			podCast[strlen(podCast)-1]=0;// remove last char as it is a \n

			retPodcast->push_back(new peePodcast(podCast,100,10));
		}
		if(strncmp("spodcast:",line,strlen("spodcast:"))==0)
		{
			podCast=&line[strlen("spodcast:")];
			podCast[strlen(podCast)-1]=0;// remove last char as it is a \n

			retPodcast->push_back(new peePodcast(podCast,100,1));
		}
	}

	free(line);
	fclose(stream);

	return retPodcast;

				}

void toolsUpdateUserPodcastTracks(vector<peePodcastTrack*>* podcastList,peePodcast* pParent,char* htmlSource)
{
	XMLDocument xmlDoc;
	char *fileBuf=NULL;
	fileBuf = toolsGetHtml(htmlSource);
	if(fileBuf==NULL)
		return;

	xmlDoc.Parse( fileBuf, strlen(fileBuf));
	free(fileBuf);
	XMLNode* podcastNode;
	podcastNode = xmlDoc.FirstChildElement( "rss" );
	if(!podcastNode)
		return;

	podcastNode = podcastNode->FirstChildElement( "channel" );

	pParent->setTitle(podcastNode->FirstChildElement( "title")->FirstChild()->Value());
	pParent->setImage(podcastNode->FirstChildElement( "image")->FirstChildElement( "url")->FirstChild()->Value());

	podcastNode = podcastNode->FirstChildElement( "item");

	char szCmd[512];
	sprintf(szCmd,"mkdir -p \"%s/%s\"",PODCAST_DIR,pParent->_directory);
	system(szCmd);

	while(podcastNode!=NULL)
	{
		tm tsDuration;
		tm	date;
		int size;
		const char*	title;
		const char*	htmlMp3;
		const char* duration;
		const char* pubDate;

		//deprecated, to be updated with the new xml
		title=podcastNode->FirstChildElement("title")->FirstChild()->Value();
		htmlMp3=podcastNode->FirstChildElement( "enclosure" )->Attribute( "url");
		size=atoi(podcastNode->FirstChildElement( "enclosure" )->Attribute( "length"));
		duration=podcastNode->FirstChildElement( "itunes:duration" )->FirstChild()->Value();
		pubDate=podcastNode->FirstChildElement( "pubDate" )->FirstChild()->Value();

		strptime(duration, "%H:%M:%S", &tsDuration);
		strptime(pubDate, "%a, %d %b %Y %H:%M:%S", &date);

		if(((tsDuration.tm_hour*60)+tsDuration.tm_min)>pParent->_minLength)
		{
			if(pParent->GetTrackByTitle(title)==NULL)
			{
				podcastList->push_back(new peePodcastTrack(pParent,&date,title,htmlMp3,size));
			}
		}
		podcastNode=podcastNode->NextSibling();
	}
	return;
}
