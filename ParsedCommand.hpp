/**
 * Object representing a parsed command.  Contains the verb, the param, and
 * status which indicates whether or not the command was valid.
 *
 * Last modified: 2018-07-27
 */

#ifndef PARSED_COMMAND_HPP
#define PARSED_COMMAND_HPP

#include "Tag.hpp"
#include <string>

class ParsedCommand
{
	private:
		std::string param;
		std::string verb;
		bool status;
	public:
		/**
		 * Sets param and verb to empty string and status to false.
		 */
		ParsedCommand();

		/**
		 * Stores a word as either param or verb accoridng to tag.
		 */
		void storeWord( std::string word, Tag tag );

		/**
		 * Sets param string.
		 */
		void setParam( std::string word );

		/**
		 * Sets verb string.
		 */
		void setVerb( std::string verb );

		/**
		 * Sets status boolean.
		 */
		void setStatus( bool b );

		/**
		 * Returns param string.
		 */
		std::string getParam();

		/**
		 * Returns verb string.
		 */
		std::string getVerb();

		/**
		 * Returns status boolean.
		 */
		bool getStatus();
};

#endif
