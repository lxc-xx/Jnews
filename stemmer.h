#pragma once
#include <string>

using namespace std;

#ifndef BOOL
#define BOOL  int
#endif
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

class Stemmer
{
public:
	Stemmer(void);
	~Stemmer(void);

private:
	string    m_oriWord;
	int       m_length; //  offset to the end of the string
	int       m_offset; //  a general offset into the string

public:
	string Stem( const string & word);

private:
	BOOL  cons(int i);
	int   m();
	BOOL  vowelinstem();
	BOOL  doublec(int i);
	BOOL  cvc(int i);
	BOOL  ends(const string& s);
	void  setto(const string& s);
	void  r(const string& s);
	void  step1();
	void  step2();
	void  step3();
	void  step4();
	void  step5();
	void  step6();
};
