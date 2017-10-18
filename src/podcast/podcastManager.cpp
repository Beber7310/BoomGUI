/*
 * podcastManager.cpp
 *
 *  Created on: 15 oct. 2017
 *      Author: Bertrand
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#include "tools.h"
#include "peePodcast.h"
#include "downloader.h"

std::vector<peePodcast*>* Podcasts;

sem_t semPodcast;


void* podcastThread(void * p) {
	while (1) {
		unsigned int ii;

		for (ii = 0; ii < Podcasts->size(); ii++) {
			sleep(10);
			sem_wait(&semPodcast);
			Podcasts->at(ii)->updatePodcast();
			sem_post(&semPodcast);
		}
		sleep(15 * 60);
	}
}

int podcastTask() {
	pthread_t my_podcastThread;
	sem_init(&semPodcast, 0, 1);
	toolsDownloadInit();
	Podcasts = toolsGetPodcast();
	int ret = pthread_create(&my_podcastThread, NULL, &podcastThread, NULL);
	if (ret != 0) {
		printf("Error: pthread_create() failed\n");
	}
}

bool lockPodcast(std::vector<peePodcast*>** pPodcast)
{
	if(pPodcast)
		*pPodcast=Podcasts;
	return(sem_trywait(&semPodcast)==0);
}

void releasePodcast()
{
	sem_post(&semPodcast);
}
