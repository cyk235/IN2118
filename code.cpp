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
	vector< vector<uint64_t> > SortRuns;
	vector<uint64_t> IndivRun;
	uint64_t x;
	while (!(read(fdInput, &x, sizeof(uint64_t)) < 0) // divide and sort individual runs
	{
		IndivRun.push_back(x);
		size++;
		if (size==IndivRun.size())
		{
			std::sort (IndivRun.begin(), IndivRun.end());
			SortRuns.push_back(IndivRun);
		}
		
	}
	if (IndivRun.size()>0) // the last chunk
	{
		std::sort (IndivRun.begin(), IndivRun.end());
		SortRuns.push_back(IndivRun);
	}
	
	for (int i=0; i<Result.size(); i++) {   // write the result
	if (write(fdOutput, Result[i], sizeof(uint64_t)) < 0)
	std::cout << "error";
	}
}



int main(int argc, char* argv[]) {

	int fdInput =open(argv[1],O_RDONLY);
	int fdOutput=open(argv[2],O_CREAT|O_TRUNC|O_WRONLY);
	int memSize =argv[3]*1048576;
	externalSort (fdInput,0,fdOutput,memSize);
	return 0;
}
