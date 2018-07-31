/**
 * Object representing a parsed command.  Contains the verb, the param, and
 * status which indicates whether or not the command was valid.
 *
 * Last modified: 2018-07-27
 */

#include "ParsedCommand.hpp"
#include "Tag.hpp"
#include <string>

/**
 * Sets param and verb to empty string and status to false.
 */
ParsedCommand::ParsedCommand()
{
	this->param = "";
	this->verb = "";
	this->status = false;
}

/**
 * Stores a word as either param or verb accoridng to tag.
 */
void ParsedCommand::storeWord( std::string word, Tag tag )
{
	// the first noun or edge we fine becomes the param.
	// thus, if already param, just ignore.
	if ( (tag == N || tag == E) && this->getParam() == "" )
		this->setParam( word );
	else if ( tag == V )
		this->setVerb( word );
	return;
}

/**
 * Sets param string.
 */
void ParsedCommand::setParam( std::string word )
{
	this->param = word;
	return;
}

/**
 * Sets verb string.
 */
void ParsedCommand::setVerb( std::string verb )
{
	this->verb = verb;
	return;
}

/**
 * Sets status boolean.
 */
void ParsedCommand::setStatus( bool b )
{
	this->status = b;
	return;
}

/**
 * Returns param string.
 */
std::string ParsedCommand::getParam()
{
	return this->param;
}

/**
 * Returns verb string.
 */
std::string ParsedCommand::getVerb()
{
	return this->verb;
}

/**
 * Returns status boolean.
 */
bool ParsedCommand::getStatus()
{
	return this->status;
}
