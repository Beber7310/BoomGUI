#include <stdio.h>
#include <fcntl.h>
#include <podcastManager.h>
#include <unistd.h>
#include <vector>

#include "guiManager.h"


using namespace std;


int main (int argc, char* argv[]) {

	podcastTask();
	rendertask();

}

