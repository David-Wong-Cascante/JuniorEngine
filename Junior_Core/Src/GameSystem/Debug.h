#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Debug.h
* Description: Describes the debug methods used
* Created: 19-Mar-2019
* Last Modified: 19-Mar-2019
*/

// Includes
#include <fstream>				// File Stream
#include <ostream>				// Output Stream
#include <iostream>				// IO Stream
#include <sstream>				// String Stream

namespace Junior
{

	// The debug levels to print
	enum DebugLevel
	{
		NOTIFICATION, WARNING, ERROR,
	};
	// Forward Declarations

	// Debug
	class Debug
	{
	private:
		// Private Member Variables
		// The output buffer for files
		std::filebuf fileBuffer;
		// The output stream for debug
		std::ostream outputStream;
		
		// Private Member Functions

		// Hide the constructor, copy constructor
		Debug(const std::string& fileName);
		Debug(std::ostream& ostream);
		Debug(const Debug& other);
	public:
		// Public Member Functions

		// Prints the object to the stream without a new line
		// Params:
		//	object: The object we are printing
		template<typename T>
		void Print(const T& object)
		{
			outputStream << object;
		}

		// Prints the object to the stream with a new line
		// Params:
		//	object: The object we are printing
		template<typename T>
		void PrintLn(const T& object)
		{
			outputStream << object << std::endl;
		}
		// Params:
		//	level: The debug level we want
		// Returns: A string version of the debug level enumeration
		const std::string GetDebugLevelName(DebugLevel level) const;
		// Set the output file stream for debug
		// Params:
		//	file: The file name we are writting into
		void SetOutputFile(const std::string& file);
		// Sets the output stream for debug
		// Params:
		//	stream: The output stream we are writting into
		void SetOutputStream(std::ostream& stream);
		// Returns: The static object of this class
		// THERE CAN ONLY BE ONE
		static Debug& GetInstance();
	};
}