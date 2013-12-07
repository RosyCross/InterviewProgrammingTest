#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <algorithm>
#include <locale>



const std::string g_allLetters = "abcdefghijklmnopqrstuvwxyz";
std::string getMissingLetters(const std::string& sentence)
{	
	if (sentence.empty())
	    return g_allLetters;
	    
    int charSet[26]={0};                  	
	std::string lackChars;	
	for (unsigned int idx = 0; idx < sentence.size(); ++idx)
	{		
		if ( std::isalpha(sentence[idx]) )
		    charSet[tolower(sentence[idx])-97] = 1;
	}	
	for (unsigned int idx = 0; idx < sizeof(charSet)/sizeof(&charSet[0]); ++idx)
	{
		if ( charSet[idx] <= 0)
		    lackChars += char(idx+97);
	}
	
	return lackChars;    
}

int main()
{
	std::string test="A?slow?yellow?fox?crawls?under?the?proactive?dog";
	test = getMissingLetters(test); printf("%s %d\n",test.c_str());
	return EXIT_SUCCESS;
}
