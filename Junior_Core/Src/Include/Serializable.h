#pragma once
/*
* Author: David Wong
* Email: david.wongcascante@digipen.edu
* File name: Serializable.h
* Description: Provides a template for object serialization and deserialization
* Created: 8-Apr-2019
* Last Modified: 8-Apr-2019
*/

// Includes
#include "Parser.h"

namespace Junior
{
	// Forward Declartions

	class Serializable
	{
	private:
		// Private Member Functions
		// Hide copy constructor
		Serializable(const Serializable& other)
		{
		}
	public:
		// Public Member Functions
		Serializable()
		{
		}
		// Writes the component to a file
		// Params:
		//	parser: The parser used to write the component
		// Throws: ParserException
		virtual void Serialize(Parser& parser) = 0;
		// Reads and creates an object from a file
		// Params:
		//	parser: The parser used to r
		// Throws: ParserException
		virtual void Deserialize(Parser& parser) = 0;
	};
}