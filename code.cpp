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
#include <vector>

void externalSort (int fdInput, uint64_t size, int fdOutput, uint64_t memSize) {
	std::vector< std::vector<uint64_t> > SortRuns;
	std::vector<uint64_t> IndivRun;
	uint64_t x;
	uint64_t cntsize=0;
	while (!(read(fdInput, &x, sizeof(uint64_t)) < 0)) // divide and sort individual runs
	{
		IndivRun.push_back(x);
		size++;
		cntsize++;
		if (cntsize==IndivRun.size())
		{
			std::sort (IndivRun.begin(), IndivRun.end());
			SortRuns.push_back(IndivRun);
			IndivRun.clear();
			cntsize=0;
		}
		
	}
	if (IndivRun.size()>0) // the last chunk
	{
		std::sort (IndivRun.begin(), IndivRun.end());
		SortRuns.push_back(IndivRun);
		IndivRun.clear();
	}
	
	std::vector<uint64_t> Result; // merge 
	uint64_t smallest=SortRuns[0].front();
	int position=0;
	while (SortRuns.size()>0) {  // find the smallest among the first elements of the runs
		for (int i=0; i<SortRuns.size(); i++) {
			if (SortRuns[i].front()< smallest) {
				smallest=SortRuns[i].front();
				position=i;
			}
		}
		Result.push_back(SortRuns[position].front());
		SortRuns[position].erase(SortRuns[position].begin());
		for (int i =0; i < SortRuns.size();) { // remove runs with no element
			if (SortRuns[i].size()<=0)
			{
				SortRuns.erase(SortRuns.begin()+i);
			}
			else
			{
        			i++;
			}
		
		}
		
	}
	
	for (int i=0; i<Result.size(); i++) {   // write the result
	if (write(fdOutput, Result[i], sizeof(uint64_t)) < 0)
	std::cout << "error";
	}
}



int main(int argc, char* argv[]) {

	int fdInput =open(argv[1],O_RDONLY);
	int fdOutput=open(argv[2],O_CREAT|O_TRUNC|O_WRONLY);
	uint64_t memSize =(uint64_t)(atoi(argv[3]))*1048576;
	externalSort (fdInput,0,fdOutput,memSize);
	return 0;
}
