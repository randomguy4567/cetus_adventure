/**
 * Class representing the command parser for Cetus.  A Parser object
 * can call getParsedCommand() and pass in a string and dictionary of
 * valid words and their Tag types and be returned a ParsedCommand object.
 *
 * Last modified: 2018-07-31
 */

#include "Parser.hpp"
#include "ParsedCommand.hpp"
#include "Tag.hpp"
#include <string>
#include <sstream>
#include <map>
#include <stack>

/**
 * Grammar rules for reducing two tags accorind to Cetus grammar.
 * If t1 is ERR, this indicates that only t2 should attempt to be reduced.
 *
 * If two tags cannot be reduced, return INV.
 */
Tag Parser::tagReduce( Tag t1, Tag t2 )
{
	if ( t1 == ERR )
	{
		switch ( t2 )
		{
			case EP:
			case VP:
				return C;
			case V:
				return VP;
			case E_:
				return EP;
			case E:
				return E_;
			case N_:
				return NP;
			case N:
				return N_;
			default:
				return INV;
		}
	}

	if ( t1 == V && t2 == NP )
		return VP;
	if ( t1 == V && t2 == EP )
		return VP;
	if ( t1 == VP && t2 == PP )
		return VP;
	if ( t1 == P && t2 == EP )
		return PP;
	if ( t1 == P && t2 == NP )
		return PP;
	if ( t1 == ART && t2 == N_ )
		return NP;
	if ( t1 == ADJ && t2 == N_ )
		return N_;
	if ( t1 == ART && t2 == E_ )
		return EP;
	if ( t1 == ADJ && t2 == E_ )
		return E_;

	return INV;
}

/**
 * Attempt to make at least one reduction of the tag stack, either reducing
 * the top two tags, the top tag, or the rest of the stack (attempts made in
 * that order).
 *
 * Return true if reduction was made.
 */
bool Parser::tagStackReduce( std::stack<Tag> &tagStack )
{
	Tag t1, t2, t3;
	bool reductionMade = false;

	// cannot reduce empty stack
	if ( tagStack.size() == 0 )
		return false;

	// pop top two elements from stack
	if ( tagStack.empty() == true )
		t1 = ERR;
	else
	{
		t1 = tagStack.top();
		tagStack.pop();
	}
	if ( tagStack.empty() == true )
		t2 = ERR;
	else
	{
		t2 = tagStack.top();
		tagStack.pop();
	}

	// attempt to reduce top two elements
	if ( (t3 = this->tagReduce( t2, t1 )) != INV )
	{
		tagStack.push( t3 );
		reductionMade = true;
	}
	else
	{
		// replace second element
		if ( t2 != ERR )
			tagStack.push( t2 );

		// attempt to reduce only top element
		if ( (t3 = this->tagReduce( ERR, t1 )) != INV )
		{
			tagStack.push( t3 );
			reductionMade = true;
		}
		// attempt to reduce rest of stack sans top element
		else 
		{
			if ( this->tagStackReduce( tagStack ) == true )
				reductionMade = true;
			if ( t1 != ERR )
				tagStack.push( t1 );
		}
	}

	return reductionMade;
}

/**
 * Reduce tags in stack according to Cetus grammar to determine if
 * command is grammatically correct.  If all tags can be reduced to single
 * "C" tag, then statement is valid.
 */
bool Parser::parseTagStack( std::stack<Tag> &tagStack )
{
	Tag t1, t2, t3;

	while ( tagStack.top() != C || tagStack.size() > 1 )
	{
		// pop top two elements off stack
		if ( tagStack.empty() == true )
			t1 = ERR;
		else
		{
			t1 = tagStack.top();
			tagStack.pop();
		}
		if ( tagStack.empty() == true )
			t2 = ERR;
		else
		{
			t2 = tagStack.top();
			tagStack.pop();
		}

		// attempt to reduce top two tags
		if ( (t3 = this->tagReduce( t2, t1 )) != INV )
			tagStack.push( t3 );
		else
		{
			// replace second element
			if ( t2 != ERR )
				tagStack.push( t2 );

			// attempt to reduce top tag
			if ( (t3 = this->tagReduce( ERR, t1 )) != INV )
				tagStack.push( t3 );
			// attempt to reduce rest of tag stack sans top element
			else if ( this->tagStackReduce( tagStack ) == true )
				tagStack.push( t1 );
			// nothing can be done, return false
			else
				return false;
		}
	}
	return true;
}

/**
 * Determine type of each word in command string and thus add each word Tag to
 * tag stack.  If verb or param is detected, store string in parsedCommand.
 */
std::stack<Tag> Parser::buildTagStack( 
		ParsedCommand &parsedCommand, 
		const std::string &s,
		std::map<std::string,Tag> &dict)
{
	std::stack<Tag> tagStack;
	std::string tok;
	std::istringstream iss(s);

	while ( std::getline(iss, tok, ' ') )
	{
		std::map<std::string, Tag>::iterator it;
		Tag tag;

		if ( 
		     ((it = dict.find(tok)) == dict.end()) &&
		     ((it = this->dict.find(tok)) == this->dict.end())
		   )
			tag = INV;	
		else
			tag = it->second;

		if ( tag == N || tag == V || tag == E )
			parsedCommand.storeWord( tok, tag );

		tagStack.push( tag );
	}

	return tagStack;
}

/**
 * Convert all letters to lowercase and converts any non alphabetic cahracters
 * to whitespace.
 */
std::string Parser::sanitizeString( const std::string &s )
{
	std::ostringstream oss;
	for ( auto i = std::begin(s); i != std::end(s); ++i )
	{
		if ( !isalpha(*i) )
			oss << " ";
		else
			oss << char(tolower(*i));
	}
	return oss.str();
}

/**
 * Loads internal dictionary.
 */
Parser::Parser()
{
	// populate internal dictionary
	this->dict = 
	{
		{"a", ART},
		{"an", ART},
		{"the", ART},
		{"at", P},
		{"on", P},
		{"to", P},
		{"with", P},
		{"attack", V},
		{"call", V},
		{"drop", V},
		{"eat", V},
		{"go", V},
		{"help", V},
		{"inventory", V},
		{"kick", V},
		{"listen", V},
		{"load", V},
		{"loadgame", V},
		{"look", V},
		{"open", V},
		{"press", V},
		{"quit", V},
		{"save", V},
		{"savegame", V},
		{"sleep", V},
		{"take", V},
		{"talk", V},
		{"use", V}
	};
}

/**
 * Returns a ParsedCommand object with verb, param, and
 * status after parsing commandString.
 */
ParsedCommand Parser::getParsedCommand( std::string commandString,
		std::map<std::string,Tag> &dict )
{
	ParsedCommand parsedCommand;
	std::stack<Tag> tagStack;

	/* remove all characters from string at are not alpha nor whitespace */
	commandString = this->sanitizeString( commandString );

	/* build tag stack */
	tagStack = this->buildTagStack( parsedCommand, commandString, dict );

	/* confirm grammatical correctness of command */
	parsedCommand.setStatus( this->parseTagStack( tagStack ) );

	return parsedCommand;
}

