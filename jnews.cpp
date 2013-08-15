// NewsClassifier.cpp : Defines the entry point for the console application.
//

#include <string>
#include <sstream>
#include <iostream>
#include "stemmer.h"
#include "analyzer.h"
#include "svm.h"
#include <fstream>
#include <map>
#include <cmath>

#define REP( i , j , k ) for( int i = j ; i < k ; ++i )

#define NUM_COLUMN ( 5 )

#define ART ( 0 )
#define BUSINESS ( 1 )
#define HEALTH ( 2 )
#define POLITICS ( 3 )
#define SPORTS ( 4 )

using namespace std;

string Column[] = { "Art" , "Business" , "Health" , "Politics" , "Sports" };

map< string , int > T;
map< string , int > D;


void Save( map< string , int > & dict , string file_name )
{
	map< string , int >::iterator it;

	ofstream fout( file_name.c_str() );

	for( it = dict.begin() ; it != dict.end() ; ++it )
	{
		fout << it->first << " " << it->second << endl;	
	}

	fout.close();
}

void Load( map< string , int > & dict , string file_name )
{
	dict.clear();
	ifstream fin( file_name.c_str() );

	string str;
	int num;

	while(  fin >> str >> num )
	{
		dict[ str ] = num;
	}


	fin.close();
}



void GenTable()
{
	T.clear();

	char file_name[20];
	int file_num = 1;
	string file_content;
	file_content.reserve( 20000 );
	vector< string > word_pool;


	REP( i , 0 , NUM_COLUMN )
	{
		string path_pre = "./Data/";
		path_pre.append( Column[ i ] );
		path_pre.append( "/" );


		file_num = 1;
		file_content.clear();
		word_pool.clear();

		while( true )
		{
			sprintf( file_name , "%d.txt" , file_num ++ );
			string path = path_pre;
			path.append( file_name );

			ifstream fin( path.c_str() );

			if( !fin.good() )
			{
				break;
			}

			ostringstream tmp;
			tmp << fin.rdbuf();
			file_content = tmp.str();

			word_pool.clear();
			( Analyzer::Instance() )->GenWords( word_pool , file_content );

			REP( i , 0 , word_pool.size() )
			{
				if( T.find( word_pool[ i ] ) == T.end() )
				{
					T[ word_pool[ i ] ] = 1;
				}
				else
				{
					++T[ word_pool[ i ] ];
				}
			}


			fin.close();

		}	
	}

	string dic_file_name =  "./Data/Dictionary/raw.dic";

	Save( T , dic_file_name );

}



void CompileDictionary( int threshold )
{
	D.clear();

	int num = 1;

	map< string , int >::iterator it;

	for( it = T.begin() ; it != T.end() ; ++it )
	{
		if( it->second >= threshold )
		{
			D[ it->first ] = num++;
		}
	}


	string dic_file_name = "./Data/Dictionary/main.dic";
	Save( D , dic_file_name );

}



void GenVector( map< int , double > & v , const string & file_content )
{
	vector< string > word_pool;
	word_pool.clear();
	( Analyzer::Instance() )->GenWords( word_pool , file_content );


	map< string , int > t;
	t.clear();

	REP( i , 0 , word_pool.size() )
	{
		if( D.find( word_pool[ i ] ) == D.end() )
		{
			continue;
		}

		if( t.find( word_pool[ i ] ) == t.end() )
		{
			t[ word_pool[ i ] ] = 1;
		}
		else
		{
			++t[ word_pool[ i ] ];
		}
	}

	map< string , int >::iterator it;


	for( it = t.begin() ; it != t.end() ; ++it )
	{
		double weight = 0;
		/*
		weight = ( double )( it->second ) / ( log( (double)T[ it->first ] ) );

		weight = ( weight > 1 )? 1 : weight;

		*/

		weight = it->second;


		v[ D[ it->first ] ] = weight;
	}
}



void GenTrainData()
{
	char file_name[20];
	int file_num = 1;
	string file_content;
	file_content.reserve( 20000 );
	vector< string > word_pool;
	ofstream fout( "./Data/train.txt" );


	REP( i , 0 , NUM_COLUMN )
	{
		string path_pre = "./Data/";
		path_pre.append( Column[ i ] );
		path_pre.append( "/" );


		file_num = 1;
		file_content.clear();
		word_pool.clear();

		while( true )
		{
			sprintf( file_name , "%d.txt" , file_num ++ );
			string path = path_pre;
			path.append( file_name );

			ifstream fin( path.c_str() );

			if( !fin.good() )
			{
				break;
			}

			ostringstream tmp;
			tmp << fin.rdbuf();
			file_content = tmp.str();

			map< int , double > v;
			v.clear();


			GenVector( v , file_content );

			fout << i;

			for( map< int , double >::iterator it = v.begin() ; it != v.end() ; ++it )
			{
				fout << " " << it->first << ":" << it->second;
			}
			fout << endl;





		}	
	}

	string dic_file_name =  "./Data/Dictionary/raw.dic";

	Save( T , dic_file_name );

	fout.close();
}


void shuffle( vector< string > & v )
{
	REP( i , 0 , v.size() - 1 )
	{
		int j = i + rand() % ( v.size() - i );

		string tmp = v[ i ];
		v[ j ] = v[ i ];
		v[ i ] = tmp;
	}
}

void shuffle( string file_name )
{
	ifstream fin( file_name.c_str() );

	vector< string > v;
	
	string str;
	while( !fin.eof() )
	{
		getline( fin , str );

		int type;

		sscanf( str.c_str() , "%d" , &type );

		//if( type == POLITICS || type == SPORTS )
		//{
			v.push_back( str );
		//}

	}

	shuffle( v );

	ofstream fout( ( file_name + ".sf" ).c_str() );

	REP( i , 0 , v.size() )
	{
		fout << v[ i ] << endl;
	}

	fin.close();
	fout.close();

}

int main(int argc, char* argv[])
{
	string command = "svm-precit";
	string test_file = "./Data/test.txt";
	string model_file = "./Data/model.txt";
	string result_file = "./Data/result.txt";
	

	if( argc != 2 )
	{
		printf("Usage: jnews news_file\n" );
		return 0;
	}

	Load( T , "./Data/raw.dic" );
	Load( D , "./Data/main.dic" );
	
	string file_name = argv[ 1 ];
	
	ifstream fin( file_name.c_str() );
	
	if( !fin.good() )
	{
		printf( "Cannot open the file.\n" );
		return 0;
	}
	
	ostringstream tmp;
	tmp << fin.rdbuf();
	string file_content = tmp.str();
	
	map< int , double > v;
	v.clear();

	GenVector( v , file_content );

	ofstream fout( test_file.c_str() );
	
	fout << 0;
	
	for( map< int , double >::iterator it = v.begin() ; it != v.end() ; ++it )
	{
		fout << " " << it->first << ":" << it->second;
	}
	fout << endl;	
	
	fout.close();

	int argcx = 4;

	char * argvx[] = { "svm-precit" , "./Data/test.txt" , "./Data/model.txt" , "./Data/result.txt" };

	svm_predict_wrapped( argcx , argvx );

	ifstream refin( result_file.c_str() );
	
	int type;
	refin >> type;
	
	string result;
	
	switch( type )
	{
		case ART : 
			result = "Arts";
			break;
		case BUSINESS : 
			result = "Business";
			break;
		case HEALTH : 
			result = "Health";
			break;
		case POLITICS : 
			result = "Politics";
			break;
		case SPORTS : 
			result = "Sports";
			break;
		default : 
			result = "Unknown";
			break;
	}
	
	printf( "I guess this news is from %s column\n" , result.c_str() );
	
	fin.close();
	fout.close();
	refin.close();

	return 0;
}
