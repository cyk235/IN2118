#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <algorithm>
#include <queue>

void externalSort (int fdInput, uint64_t size, int fdOutput, uint64_t memSize) {
	read(fdInput,,memSize);
	vector<uint64_t> SortRuns;
	open(fdInput,,memSize);
}



int main(int argc, char* argv[]) {

	int fdInput =open(argv[1],O_RDONLY);
	int fdOutput=open(argv[2],O_CREAT|O_TRUNC|O_WRONLY);
	int memSize =argv[3]*1024;
	externalSort (fdInput,64,fdOutput,memSize);
	return 0;
}
