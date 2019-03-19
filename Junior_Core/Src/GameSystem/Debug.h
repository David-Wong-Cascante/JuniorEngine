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

namespace Junior
{
	// Forward Declarations

	// Debug
	class Debug
	{
	private:
		// Private Member Variables
		// The output file stream of the debug
		std::fstream fileStream;
		// The output stream for debug
		std::ostream outputStream;
		// Whether we are using the file stream (if true, then we are printing to file, otherwise we are printing to stream)
		bool printingToFile;
		
		// Private Member Functions

		// Hide the constructor, copy constructor
		Debug();
		Debug(const Debug& other);
	public:
		// Public Member Functions

		// Set the output file stream for debug
		// Params:
		//	file: The file name we are writting into
		void SetOutputFile(const std::string& file);
		// Sets the output stream for debug
		// Params:
		//	stream: The output stream we are writting into
		void SetOutputStream(std::ostream& stream);
		// Prints text into the output stream
		// Params:
		//	object: The object we are printing
		//	addLine: If true, it adds a newline after printing the object
		template<typename T>
		void PrintString(T object, bool addLine = false)
		{
			if (printingToFile)
			{
				// Attempt to print to file
				if (fileStream.is_open())
				{
					fileStream << object;
					if (addLine)
						fileStream << std::endl;
				}
				else
				{
					std::cout << "Failed to print " << T << " into file" << std::endl;
				}
			}
			else
			{
				outputStream << object;
			}
		}
		// Returns: The static object of this class
		// THERE CAN ONLY BE ONE
		Debug& GetInstance() const;
	};
}