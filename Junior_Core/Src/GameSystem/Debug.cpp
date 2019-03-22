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
#include "Debug.h"

Junior::Debug::Debug(std::ostream& stream)
	: fileBuffer(), outputStream(stream.rdbuf())
{
}

Junior::Debug::Debug(const std::string& fileName)
	: fileBuffer(fopen(fileName.c_str(), "wt")), outputStream(&fileBuffer)
{
}

Junior::Debug::Debug(const Debug& other)
	: fileBuffer(), outputStream(other.outputStream.rdbuf())
{
}

void Junior::Debug::SetOutputFile(const std::string& file)
{
	fileBuffer.open(file, std::ios_base::out);
	outputStream.rdbuf(&fileBuffer);
}

void Junior::Debug::SetOutputStream(std::ostream& ostream)
{
	outputStream.set_rdbuf(ostream.rdbuf());
}

const std::string Junior::Debug::GetDebugLevelName(Junior::DebugLevel level) const
{
	switch (level)
	{
	case Junior::NOTIFICATION:
		return "[NOTIFICATION] ";
	case Junior::WARNING:
		return "[WARNING] ";
	case Junior::ERROR:
		return "[ERROR] ";
	default:
		return "";
	}
}

Junior::Debug& Junior::Debug::GetInstance()
{
	//static Debug debug("JuniorDebugInfo.txt");
	static Debug debug(std::cout);
	return debug;
}