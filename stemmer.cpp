/* This is the Porter stemming algorithm, coded up as thread-safe ANSI C
by the author.

It may be be regarded as cononical, in that it follows the algorithm
presented in

Porter, 1980, An algorithm for suffix stripping, Program, Vol. 14,
no. 3, pp 130-137,

only differing from it at the points maked --DEPARTURE-- below.

See also http://www.tartarus.org/~martin/PorterStemmer

The algorithm as described in the paper could be exactly replicated
by adjusting the points of DEPARTURE, but this is barely necessary,
because (a) the points of DEPARTURE are definitely improvements, and
(b) no encoding of the Porter stemmer I have seen is anything like
as exact as this version, even with the points of DEPARTURE!

You can compile it on Unix with 'gcc -O3 -o stem stem.c' after which
'stem' takes a list of inputs and sends the stemmed equivalent to
stdout.

The algorithm as encoded here is particularly fast.

Release 2 (the more old-fashioned, non-thread-safe version may be
regarded as release 1.)
*/

#include <iostream>
using namespace std;

#include "stemmer.h"

Stemmer::Stemmer(void):m_oriWord(""), m_length(0), m_offset(0)
{
}

Stemmer::~Stemmer(void)
{

}

//////////////////////////////////////////////////////////////////////////
// cons(i) is true <=> b[i] is a consonant.
BOOL Stemmer::cons(int i)
{
	switch (m_oriWord[i])
	{
	case 'a': case 'e': case 'i': case 'o': case 'u': return FALSE;
	case 'y': return (i == 0) ? TRUE : cons(i - 1);
	default: return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////
// m(z) measures the number of consonant sequences between 0 and j. if c is
// a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
// presence,
// 
// <c><v>       gives 0
// <c>vc<v>     gives 1
// <c>vcvc<v>   gives 2
// <c>vcvcvc<v> gives 3
// ....
int Stemmer::m()
{
	int n = 0;
	int i = 0;

	while (TRUE)
	{
		if ( i>m_offset ) 
		{
			return n;
		}
		if (!cons(i)) break; 
		i++;
	}
	i++;
	while (TRUE)
	{
		while(TRUE)
		{  
			if (i > m_offset) return n;
			if (cons(i)) break;
			i++;
		}
		i++;
		n++;
		while(TRUE)
		{  
			if (i > m_offset) return n;
			if (!cons(i)) break;
			i++;
		}
		i++;
	}
}

//////////////////////////////////////////////////////////////////////////
//  vowelinstem() is TRUE <=> 0,...j contains a vowel
BOOL Stemmer::vowelinstem()
{
	int i; 
	for (i = 0; i <= m_offset; i++) 
	{
		if (!cons(i)) return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//  doublec(i) is TRUE <=> i,(i-1) contain a double consonant.
BOOL  Stemmer::doublec(int i)
{
	string  b = m_oriWord;
	if (i<1) 
	{
		return FALSE;
	}
	if (b[i] != b[i-1])
	{
		return FALSE;
	}
	return cons(i);
}

//////////////////////////////////////////////////////////////////////////
// cvc(i) is TRUE <=> i-2,i-1,i has the form consonant - vowel - consonant
// and also if the second c is not w,x or y. this is used when trying to
// restore an e at the end of a short word. e.g.
// 
// cav(e), lov(e), hop(e), crim(e), but
// snow, box, tray.
BOOL Stemmer::cvc(int i)
{
	if (i < 2 || !cons(i) || cons(i - 1) || !cons(i - 2)) 
	{
		return FALSE;
	}
	int ch = m_oriWord[i];
	if (ch  == 'w' || ch == 'x' || ch == 'y')
	{
		return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//  ends(s) is TRUE <=> 0,...m_length ends with the string s.
BOOL  Stemmer::ends(const string& s)
{
	int l = s.length();
	int start = m_length - l + 1;

	if (start<0)
	{
		return FALSE;
	}

	for (int i=0; i<l; i++)
	{
		if (s[i] != m_oriWord[start+i])
		{
			return FALSE;
		}  
	}

	m_offset =  m_length - l;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//  sets (m_offset+1),...m_length to the characters in the string s, 
//  readjusting m_length.
void Stemmer::setto(const std::string &s)
{
	int l = s.length();
	string tmpSubStr = m_oriWord.substr(0, m_offset+1);
	m_oriWord = tmpSubStr + s;
	m_length = m_offset + l;
}

// r(s) is used further down.
void Stemmer::r(const string &s)
{
	if(m()>0) 
	{
		setto(s);
	}
}

//////////////////////////////////////////////////////////////////////////
// step1ab(z) gets rid of plurals and -ed or -ing. e.g.
// 
// caresses  ->  caress
// ponies    ->  poni
// ties      ->  ti
// caress    ->  caress
// cats      ->  cat
// 
// feed      ->  feed
// agreed    ->  agree
// disabled  ->  disable
// 
// matting   ->  mat
// mating    ->  mate
// meeting   ->  meet
// milling   ->  mill
// messing   ->  mess
// 
// meetings  ->  meet
void Stemmer::step1()
{
	if ('s' == m_oriWord[m_length])
	{
		if (ends("sses"))
		{
			m_length -= 2;
		} else
			if (ends("ies"))
			{
				setto("i");
			}else
				if ('s' != m_oriWord[m_length-1])
				{
					m_length--;
				}
	}

	if (ends("eed"))
	{
		if (m()>0)
		{
			m_length--;
		}
	}else if ( (ends("ed") || ends("ing")) && vowelinstem() )
	{
		m_length = m_offset;
		if (ends("at"))
		{
			setto("ate");
		}else if (ends("bl"))
		{
			setto("ble");
		}else if (ends("iz"))
		{
			setto("ize");
		}else if (doublec(m_length))
		{
			m_length--;
			{
				char ch;
				ch = m_oriWord[m_length];
				if ( ch == 'l' || ch == 's' || ch == 'z' )
				{
					m_length++;
				}
			}
		}else if (m()==1 && cvc(m_length))
		{
			setto("e");
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//  step2() turns terminal y to i when there is another vowel in the stem.
void Stemmer::step2()
{
	if (ends("y") && vowelinstem())
	{
		m_oriWord[m_length] = 'i';
	}
}

//////////////////////////////////////////////////////////////////////////
// step3() maps double suffices to single ones. so -ization ( = -ize plus -ation) 
// maps to -ize etc. note that the string before the suffix must give m() > 0.
void Stemmer::step3()
{
	if (0==m_length)
	{
		return;
	}
	switch (m_oriWord[m_length-1])
	{
	case 'a':
		if (ends("ational"))  { r("ate"); break; }
		if (ends("tional"))   { r("tion"); break; }
		break;
	case 'c':
		if (ends("enci"))   { r("ence"); break; }
		if (ends("anci"))   { r("ance"); break; }
		break;
	case 'e':
		if (ends("izer"))   { r("ize"); break; }
		break;
	case 'l':
		if (ends("bli"))    { r("ble"); break; }
		if (ends("alli"))   { r("al"); break; }
		if (ends("entli"))  { r("ent"); break; }
		if (ends("eli"))    { r("e"); break;}
		if (ends("ousli"))  { r("ous"); break; }
		break;
	case 'o':
		if (ends("ization"))  { r("ize"); break;}
		if (ends("ation"))    { r("ate"); break; }
		if (ends("ator"))     { r("ate"); break; }
		break;
	case 's':
		if (ends("alism"))    { r("al"); break; }
		if (ends("iveness"))  { r("ive"); break; }
		if (ends("fulness"))  { r("ful"); break; }
		if (ends("ousness"))  { r("ous"); break; }
		break;
	case 't':
		if (ends("aliti"))    { r("al"); break;}
		if (ends("iviti"))    { r("ive"); break; }
		if (ends("biliti"))   { r("ble"); break; }
		break;
	case 'g':
		if (ends("logi"))     { r("log"); break; }
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// step4() deals with -ic-, -full, -ness etc. similar strategy to step3. 
void Stemmer::step4()
{
	switch (m_oriWord[m_length])
	{
	case 'e':
		if (ends("icate"))    { r("ic"); break; }
		if (ends("ative"))    { r(""); break; }
		if (ends("alize"))    { r("al"); break; }
		break;
	case 'i':
		if (ends("iciti"))    { r("ic"); break; }
		break;
	case 'l':
		if (ends("ical"))     { r("ic"); break; }
		if (ends("ful"))      { r(""); break; }
		break;
	case 's':
		if (ends("ness"))     { r(""); break; }
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// step5() takes off -ant, -ence etc., in context <c>vcvc<v>.
void Stemmer::step5()
{
	if (0==m_length)
	{
		return;
	}
	switch (m_oriWord[m_length-1])
	{
	case 'a':
		if (ends("al"))     { break; }
		return;
	case 'c':
		if (ends("ance"))   { break; }
		if (ends("ence"))   { break; }
		return;
	case 'e':
		if (ends("er"))     { break; }
		return;
	case 'i':
		if (ends("ic"))     { break; }
		return;
	case 'l':
		if (ends("able"))   { break; }
		if (ends("ible"))   { break; }
		return;
	case 'n':
		if (ends("ant"))    { break; }
		if (ends("ement"))  { break; }
		if (ends("ment"))   { break; }
		if (ends("ent"))    { break; }
		return;
	case 'o':
		if ( ends("ion") && 0<=m_offset && ('s'==m_oriWord[m_offset] || 't'==m_oriWord[m_offset]) ) { break; }
		if (ends("ou"))     { break; }
		return;
	case 's':
		if (ends("ism"))    { break; }
		return;
	case 't':
		if (ends("ate"))    { break; }
		if (ends("iti"))    { break; }
		return;
	case 'u':
		if (ends("ous"))    { break; }
		return;
	case 'v':
		if (ends("ive"))    { break; }
		return;
	case 'z':
		if (ends("ize"))    { break; }
		return;
	default:
		return;
	}
	if (m()>1)
	{
		m_length = m_offset;
	}
}

//////////////////////////////////////////////////////////////////////////
// step6() removes a final -e if m() > 1.
void Stemmer::step6()
{
	m_offset = m_length;
	if ('e' == m_oriWord[m_length])
	{
		int a = m();
		if (a>1 || a==1 && !cvc(m_length-1))
		{
			m_length--;
		}
	}
	if ('l' == m_oriWord[m_length] && doublec(m_length) && m()>1)
	{
		m_length--;
	}
}

//  this stemmer can only deal with lowercase
string Stemmer::Stem( const string & word)
{
	m_oriWord = word;
	m_length = m_oriWord.length()-1;
	m_offset = 0;

	if (0<m_length)
	{
		step1();
		step2();
		step3();
		step4();
		step5();
		step6();
	}

	return m_oriWord.substr(0, m_length+1);
}
