#include "Tag.hpp"
#include "Parser.hpp"
#include "ParsedCommand.hpp"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

static void _populateDictionary( std::map<std::string, Tag> &dict );

int main()
{
	std::string line;
	Parser parser;
	ParsedCommand parsedCommand;
	std::map<std::string, Tag> dict;

	_populateDictionary( dict );

	std::cout << "Etner a command to determine verb and param\n"
		<< "Press ctrl+C to quit\n" << std::flush;
	while ( 1 )
	{
		std::cout << " > " << std::flush;
		getline( std::cin, line );
		parsedCommand = parser.getParsedCommand( line, dict );
		std::cout << "Verb: " << parsedCommand.getVerb() << std::endl;
		std::cout << "Param: " << parsedCommand.getParam() << std::endl;
		std::cout << "Status: " << parsedCommand.getStatus() << std::endl;
	}

	return 0;
}

/**
 * Populate the dictionary from the word lists in the command-parser data
 * directory.
 */
static void _populateDictionary( std::map<std::string, Tag> &dict )
{
	std::vector<std::string> wordFiles({
		"", 
		"data/adjectives", "data/articles", "data/edges",
		"data/nouns", "data/prepositions", "data/verbs"
		});
	std::string word;
	for ( int i = 1; i <= 6; i++ )
	{
		std::ifstream ifs( wordFiles.at(i), std::ifstream::in );
		while ( ifs.good() )
		{
			std::getline( ifs, word );
			dict[word] = Tag(i);
		}
		ifs.close();
	}
	return;
}
