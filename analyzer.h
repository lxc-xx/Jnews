#pragma once
#include <string>
#include <vector>
#include <set>
#include "stemmer.h"

using namespace std;

class Analyzer
{
public:
	void GenWords( vector< string > & , string );
	static Analyzer * Instance();


private:
	Analyzer(void);
	~Analyzer(void);

	static Analyzer * instance;

	set< string > stop_words;
	Stemmer stemmer;
	
};

