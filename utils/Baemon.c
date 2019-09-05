#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	while(1)
	{
//		system("sleep 5");
		sleep(5);
		printf(" \n\n\n=========== RUN BOOM ================\n\n\n");
		system("./BoomGui");
	}
}
