#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include <string>
#include <algorithm>
#include <vector>

namespace {
	const char taken     = 'X';
	const char notTaken  = '.';
	const char left      = 'L';
	const char right     = 'R';
}

void buildInitStatus(std::string& init, int leftDir[], int rightDir[])
{
	//build initial status
	memset(leftDir,0,init.size()*sizeof(&leftDir[0]));
	memset(rightDir,0,init.size()*sizeof(&rightDir[0]));		
	for(int idx = 0; idx < init.size(); ++idx)
	{
		switch (init[idx])
		{
			case left:
			    leftDir[idx] += 1;
			    init[idx] = taken;		    
				break;
			case right:
			    rightDir[idx] += 1;
			    init[idx] = taken;			    
			    break;
			default:
			    break;    		
		}
	}			
}
std::vector<std::string> animate(int speed,const std::string& init)
{
	//define some facilitating symbols
	const int rightInc = 1;
	const int leftInc  = -1;
	const unsigned int len = init.size();
		
	const std::string done(init.size(),'.');
	std::string iter = init;
	int leftDir[init.size()];
	int rightDir[init.size()];
	int leftDirTmp[init.size()];
	int rightDirTmp[init.size()];
    buildInitStatus(iter, leftDir,rightDir);
    for (int idx=0; idx<init.size();++idx)
	    leftDirTmp[idx]= 0;
    for (int idx=0; idx<init.size();++idx)
	    rightDirTmp[idx]= 0;
	    	    
	std::vector<std::string> result;
	result.push_back(iter);
	
	//tmp variable
	int pos = -1;
    while ( 0 != memcmp(done.data(),iter.data(),iter.size()) )
    {
    	for(unsigned int idx=0; idx < len; ++idx)
    	{    		
    		if ( iter[idx] == taken )
    		{
    			//neither move left nor move right will take the
    			//same position, so process left and right in sequence
    			//iter[idx] = notTaken;    				
    		    while ( leftDir[idx] > 0)
    		    {
    		    	
    			    leftDir[idx] -= 1; //remove from current pos
    			    //leftDirTmp[idx] -= 1;
    			    pos = idx + speed*leftInc;    			    
    			    if ( pos > 0 )
    			    {
    			        leftDirTmp[pos] += 1;
    			        iter[pos] = taken;    			        
    			    }
    		    }
    		    while ( rightDir[idx] > 0 )
    		    {
    		        rightDir[idx] -= 1; //remove from current pos
    		        //rightDirTmp[idx] -= 1;
    			    pos = idx + speed*rightInc;    			    
    			    if ( pos < len )
    			    {
    			        rightDirTmp[pos] += 1;
    			        iter[pos] = taken;    			        
    			    }
    		    }    		    			
		   }		   		   		            	          	       
    	}    	
    	for (int idx=0; idx<len;++idx)
	    {	       	   	       	   
			if ( leftDirTmp[idx] > 0 || rightDirTmp[idx] > 0 )
			{
				iter[idx] = taken;					
			}	
			else
			{
				iter[idx] = notTaken;					
			}
			leftDir[idx]= leftDirTmp[idx]; 
			rightDir[idx]= rightDirTmp[idx];
	    }
	    memset(leftDirTmp,0,init.size()*sizeof(&leftDir[0]));
	    memset(rightDirTmp,0,init.size()*sizeof(&rightDir[0]));
        result.push_back(iter);    	
    }
    
    return result;
}

void testFunc(double bb[])
{
		printf("testFunc:%d %d\n",sizeof(bb), sizeof(&bb[0]));
}
int main()
{
	//double aa[10] = {0.0};
	//testFunc(aa);
	std::string test = "LRLR.LRLR";
	std::vector<std::string> result = animate(2,test);
	printf("%d\n",result.size());
	for (int idx=0; idx<result.size();++idx)
	{
		for (int idz=0; idz<result[idx].size();++idz)
		{
			printf("%c",result[idx].at(idz));
		}
		printf("\n");
	}	
	
	return EXIT_SUCCESS;
}
