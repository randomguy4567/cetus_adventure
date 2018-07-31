/**
 * Class representing the command parser for Cetus.  A Parser object
 * can call getParsedCommand() and pass in a string and dictionary of
 * valid words and their Tag types and be returned a ParsedCommand object.
 *
 * Last modified: 2018-07-31
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "ParsedCommand.hpp"
#include "Tag.hpp"
#include <string>
#include <stack>
#include <map>

class Parser
{
	private:
		std::map<std::string, Tag> dict;
		Tag tagReduce( Tag t1, Tag t2 );
		bool tagStackReduce( std::stack<Tag> &tagStack );
		bool parseTagStack( std::stack<Tag> &tagStack );
		std::stack<Tag> buildTagStack( 
				ParsedCommand &parsedCommand, 
				const std::string &s,
				std::map<std::string,Tag> &dict);
		std::string sanitizeString( const std::string &s );
	public:
		/**
		 * Loads internal dictionary.
		 */
		Parser();

		/**
		 * Returns a ParsedCommand object with verb, param, and
		 * status after parsing commandString.
		 */
		ParsedCommand getParsedCommand( std::string commandString,
				std::map<std::string,Tag> &dict );
};

#endif
