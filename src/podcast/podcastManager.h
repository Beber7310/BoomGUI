#ifndef SRC_PODCASTMGR_H_
#define SRC_PODCASTMGR_H_

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

int podcastTask();

bool lockPodcast(std::vector<peePodcast*>** pPodcast);
void releasePodcast();

#endif
