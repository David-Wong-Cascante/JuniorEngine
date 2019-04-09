/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Parser.cpp
* Description: Parses through a text file
* Created: 27-Mar-2019
* Last Modified: 27-Mar-2019
*/

// Includes
#include "Parser.h"

Junior::ParserException::ParserException(const std::string& fileName, const std::string& error)
	: std::exception((fileName + ": " + error).c_str())
{
}

Junior::Parser::Parser(const std::string& fileName, std::fstream::openmode mode)
	: file_(), fileName_(fileName), tab_("   "), numTabs_(0)
{
	file_.open(fileName, mode);
}

Junior::Parser::~Parser()
{
	if (file_.is_open())
		file_.close();
}

void Junior::Parser::CheckIfOpen() const
{
	if(!file_.is_open())
		throw ParserException(fileName_, "File failed to open!");
}

std::string Junior::Parser::GetLine(unsigned length)
{
	char* rawData = nullptr;
	file_.getline(rawData, length);
	std::string line(rawData);
	return line;
}

void Junior::Parser::Skip(char skip)
{
	file_.ignore(skip, 10);
}

void Junior::Parser::Skip(const std::string& skip)
{
	CheckIfOpen();

	std::string word;
	file_ >> word;

	//If the contents of the string don't match the name parameter, throw a ParseException with the file name and a message about how a variable with the given name could not be found.
	if (word != skip) {
		throw ParserException(fileName_, "Skipping " + skip + " didn't match the skipped portion of the file");
	}
}

unsigned Junior::Parser::StarScope()
{
	CheckIfOpen();
	for (unsigned i = 0; i < numTabs_; ++i)
		file_ << tab_;
	file_ << '{' << std::endl;
	unsigned prevTabs = numTabs_++;
	return prevTabs;
}

unsigned Junior::Parser::EndScope()
{
	CheckIfOpen();
	--numTabs_;
	for (unsigned i = 0; i < numTabs_; ++i)
		file_ << tab_;
	file_ << '}' << std::endl;

	return numTabs_;
}

unsigned Junior::Parser::GetCurrentIndents() const
{
	return numTabs_;
}
