#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Parser.h
* Description: Parses through a text file
* Created: 27-Mar-2019
* Last Modified: 8-Apr-2019
*/

// Includes
#include <fstream>				// File Streams
#include <exception>			// Exception
#include <string>				// String

namespace Junior
{
	struct ParserException : public std::exception
	{
		// Public Member Functions
		ParserException(const std::string& fileName, const std::string& what);
	};

	class Parser
	{
	private:
		// Private Member Variables
		// The file we are reading from
		std::fstream file_;
		// The file name
		std::string fileName_;
		// Tab
		const char* tab_;
		// How many tabs we accumulated
		unsigned numTabs_;

	public:
		// Public Member Variables

		// Constructor
		// Params:
		//	fileName: The file name we are parsing through
		//	mode: The mode we are parsing file
		Parser(const std::string& fileName, std::fstream::openmode mode = std::ios::in);
		// Destructor
		~Parser();
		// Prevents reading when the file is not open
		// Throws: ParserException
		void CheckIfOpen() const;
		// Reads through a variable
		// Params:
		//	varName: The variable's name
		//	value: The value to save what we read
		// Throws: ParserException
		template <typename T>
		void ReadVariable(const std::string& varName, T& value)
		{
			CheckIfOpen();
			std::string word;
			file_ >> word;
			// Test if the names are the same first
			if (word != varName)
			{
				throw ParserException(fileName_, "Attempted to read the variable name \"" + word + "\" as \"" + varName + "\"!");
			}
			// then read the name of the variables
			Skip(":");
			file_ >> value;
		}
		// Writes a variable to the file
		// Params:
		//	varName: The variable's name
		//	value: The value we are writing
		// Throws: ParserException
		template <typename T>
		void WriteVariable(const std::string& varName, const T& value)
		{
			CheckIfOpen();
			// Fill in the tabs
			for (unsigned i = 0; i < numTabs_; ++i)
			{
				file_ << tab_;
			}
			// Write the variable
			file_ << varName << " : " << value << std::endl;
		}
		// Reads through a value
		// Params:
		//	value: The value we are reading through
		// Throws: ParserException
		template <typename T>
		void ReadValue(T& value)
		{
			CheckIfOpen();
			file_ >> value;
		}
		// Writes a variable to the file
		// Params:
		//	value: The value that we are writing
		// Throws: ParserException
		template <typename T>
		void WriteValue(const T& value)
		{
			CheckIfOpen();
			// Fill in the amount of tabs we got
			for (unsigned i = 0; i < numTabs_; ++i)
			{
				file_ << tab_;
			}
			// Write the value
			file_ << value << std::endl;
		};
		// Params:
		//	length: The expected length of the current line
		// Returns: The current line the parser is reading through
		std::string GetLine(unsigned length);
		// Skips the character specified
		// Params:
		//	skip: The character we want to skip
		// Throws: ParserException
		void Skip(char skip);
		// Skips the piece of text specified
		// Params:
		//	skip: The text we want to skip
		void Skip(const std::string& skip);
		// Starts writing a scope and increases the indent level
		// Returns: The amount of indents we have before making the scope
		// Throws: ParserException
		void StarScope();
		// Ends writing a scope and decreases the indent level
		// Returns: The number of indents we are after we closed the scope
		// Throws: ParserException
		void EndScope();
		// Returns: The current number of indents our scope has
		unsigned GetCurrentIndents() const;
	};
}