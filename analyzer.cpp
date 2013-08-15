#include "analyzer.h"

#define REP( i , j , k ) for( int i = j ; i < k ; ++i )


Analyzer::Analyzer(void)
{
	this->stop_words.insert( "i" );
	this->stop_words.insert( "me" );
	this->stop_words.insert( "my" );
	this->stop_words.insert( "myself" );
	this->stop_words.insert( "we" );
	this->stop_words.insert( "our" );
	this->stop_words.insert( "ours" );
	this->stop_words.insert( "ourselves" );
	this->stop_words.insert( "you" );
	this->stop_words.insert( "your" );
	this->stop_words.insert( "yours" );
	this->stop_words.insert( "yourself" );
	this->stop_words.insert( "yourselves" );
	this->stop_words.insert( "he" );
	this->stop_words.insert( "him" );
	this->stop_words.insert( "his" );
	this->stop_words.insert( "himself" );
	this->stop_words.insert( "she" );
	this->stop_words.insert( "her" );
	this->stop_words.insert( "hers" );
	this->stop_words.insert( "herself" );
	this->stop_words.insert( "it" );
	this->stop_words.insert( "its" );
	this->stop_words.insert( "itself" );
	this->stop_words.insert( "they" );
	this->stop_words.insert( "them" );
	this->stop_words.insert( "their" );
	this->stop_words.insert( "theirs" );
	this->stop_words.insert( "themselves" );
	this->stop_words.insert( "what" );
	this->stop_words.insert( "which" );
	this->stop_words.insert( "who" );
	this->stop_words.insert( "whom" );
	this->stop_words.insert( "this" );
	this->stop_words.insert( "that" );
	this->stop_words.insert( "these" );
	this->stop_words.insert( "those" );
	this->stop_words.insert( "am" );
	this->stop_words.insert( "is" );
	this->stop_words.insert( "are" );
	this->stop_words.insert( "was" );
	this->stop_words.insert( "were" );
	this->stop_words.insert( "be" );
	this->stop_words.insert( "been" );
	this->stop_words.insert( "being" );
	this->stop_words.insert( "have" );
	this->stop_words.insert( "has" );
	this->stop_words.insert( "had" );
	this->stop_words.insert( "having" );
	this->stop_words.insert( "do" );
	this->stop_words.insert( "does" );
	this->stop_words.insert( "did" );
	this->stop_words.insert( "doing" );
	this->stop_words.insert( "would" );
	this->stop_words.insert( "could" );
	this->stop_words.insert( "ought" );
	this->stop_words.insert( "i'm" );
	this->stop_words.insert( "you're" );
	this->stop_words.insert( "he's" );
	this->stop_words.insert( "she's" );
	this->stop_words.insert( "it's" );
	this->stop_words.insert( "we're" );
	this->stop_words.insert( "they're" );
	this->stop_words.insert( "i've" );
	this->stop_words.insert( "you've" );
	this->stop_words.insert( "we've" );
	this->stop_words.insert( "they've" );
	this->stop_words.insert( "i'd" );
	this->stop_words.insert( "you'd" );
	this->stop_words.insert( "he'd" );
	this->stop_words.insert( "she'd" );
	this->stop_words.insert( "we'd" );
	this->stop_words.insert( "they'd" );
	this->stop_words.insert( "i'll" );
	this->stop_words.insert( "you'll" );
	this->stop_words.insert( "he'll" );
	this->stop_words.insert( "she'll" );
	this->stop_words.insert( "we'll" );
	this->stop_words.insert( "they'll" );
	this->stop_words.insert( "isn't" );
	this->stop_words.insert( "aren't" );
	this->stop_words.insert( "wasn't" );
	this->stop_words.insert( "weren't" );
	this->stop_words.insert( "hasn't" );
	this->stop_words.insert( "haven't" );
	this->stop_words.insert( "hadn't" );
	this->stop_words.insert( "doesn't" );
	this->stop_words.insert( "don't" );
	this->stop_words.insert( "didn't" );
	this->stop_words.insert( "won't" );
	this->stop_words.insert( "wouldn't" );
	this->stop_words.insert( "shan't" );
	this->stop_words.insert( "shouldn't" );
	this->stop_words.insert( "can't" );
	this->stop_words.insert( "cannot" );
	this->stop_words.insert( "couldn't" );
	this->stop_words.insert( "mustn't" );
	this->stop_words.insert( "let's" );
	this->stop_words.insert( "that's" );
	this->stop_words.insert( "who's" );
	this->stop_words.insert( "what's" );
	this->stop_words.insert( "here's" );
	this->stop_words.insert( "there's" );
	this->stop_words.insert( "when's" );
	this->stop_words.insert( "where's" );
	this->stop_words.insert( "why's" );
	this->stop_words.insert( "how's" );
	this->stop_words.insert( "a" );
	this->stop_words.insert( "an" );
	this->stop_words.insert( "the" );
	this->stop_words.insert( "but" );
	this->stop_words.insert( "if" );
	this->stop_words.insert( "and" );
	this->stop_words.insert( "or" );
	this->stop_words.insert( "because" );
	this->stop_words.insert( "as" );
	this->stop_words.insert( "until" );
	this->stop_words.insert( "while" );
	this->stop_words.insert( "of" );
	this->stop_words.insert( "at" );
	this->stop_words.insert( "by" );
	this->stop_words.insert( "for" );
	this->stop_words.insert( "with" );
	this->stop_words.insert( "about" );
	this->stop_words.insert( "against" );
	this->stop_words.insert( "between" );
	this->stop_words.insert( "into" );
	this->stop_words.insert( "through" );
	this->stop_words.insert( "during" );
	this->stop_words.insert( "before" );
	this->stop_words.insert( "after" );
	this->stop_words.insert( "above" );
	this->stop_words.insert( "below" );
	this->stop_words.insert( "to" );
	this->stop_words.insert( "from" );
	this->stop_words.insert( "up" );
	this->stop_words.insert( "down" );
	this->stop_words.insert( "in" );
	this->stop_words.insert( "out" );
	this->stop_words.insert( "on" );
	this->stop_words.insert( "off" );
	this->stop_words.insert( "over" );
	this->stop_words.insert( "under" );
	this->stop_words.insert( "again" );
	this->stop_words.insert( "further" );
	this->stop_words.insert( "then" );
	this->stop_words.insert( "once" );
	this->stop_words.insert( "here" );
	this->stop_words.insert( "there" );
	this->stop_words.insert( "when" );
	this->stop_words.insert( "where" );
	this->stop_words.insert( "why" );
	this->stop_words.insert( "how" );
	this->stop_words.insert( "all" );
	this->stop_words.insert( "any" );
	this->stop_words.insert( "both" );
	this->stop_words.insert( "each" );
	this->stop_words.insert( "few" );
	this->stop_words.insert( "more" );
	this->stop_words.insert( "most" );
	this->stop_words.insert( "other" );
	this->stop_words.insert( "some" );
	this->stop_words.insert( "such" );
	this->stop_words.insert( "no" );
	this->stop_words.insert( "nor" );
	this->stop_words.insert( "not" );
	this->stop_words.insert( "only" );
	this->stop_words.insert( "own" );
	this->stop_words.insert( "same" );
	this->stop_words.insert( "so" );
	this->stop_words.insert( "than" );
	this->stop_words.insert( "too" );
	this->stop_words.insert( "very" );
	this->stop_words.insert( "a" );
	this->stop_words.insert( "b" );
	this->stop_words.insert( "c" );
	this->stop_words.insert( "d" );
	this->stop_words.insert( "e" );
	this->stop_words.insert( "f" );
	this->stop_words.insert( "g" );
	this->stop_words.insert( "h" );
	this->stop_words.insert( "i" );
	this->stop_words.insert( "j" );
	this->stop_words.insert( "k" );
	this->stop_words.insert( "l" );
	this->stop_words.insert( "m" );
	this->stop_words.insert( "n" );
	this->stop_words.insert( "o" );
	this->stop_words.insert( "p" );
	this->stop_words.insert( "q" );
	this->stop_words.insert( "r" );
	this->stop_words.insert( "s" );
	this->stop_words.insert( "t" );
	this->stop_words.insert( "u" );
	this->stop_words.insert( "v" );
	this->stop_words.insert( "w" );
	this->stop_words.insert( "x" );
	this->stop_words.insert( "y" );
	this->stop_words.insert( "z" );
}


Analyzer::~Analyzer(void)
{
}

Analyzer * Analyzer::instance = NULL;

Analyzer * Analyzer::Instance()
{
	if( Analyzer::instance != NULL )
	{
		return Analyzer::instance;
	}
	else
	{
		Analyzer::instance = new Analyzer();
		return Analyzer::instance;
	}
}

void Analyzer::GenWords( vector< string > & pool , string text )
{
	pool.reserve( text.size() / 5 );

	string word;
	word.reserve( 20 );
	word.clear();

	REP( i , 0 , text.size() )
	{
		if( text[ i ] >= 'A' && text[ i ] <= 'Z' )
		{
			text[ i ] = text[ i ] + 'a' - 'A';
		}

		if( text[ i ] >= 'a' && text[ i ] <= 'z' )
		{
			word.push_back( text[ i ] );
		}
		else
		{
			if( word.size() != 0 )
			{
				if( stop_words.find( word ) == stop_words.end() )
				{
					pool.push_back( stemmer.Stem ( word ) );
				}
				word.clear();
			}
		}
	}


}


