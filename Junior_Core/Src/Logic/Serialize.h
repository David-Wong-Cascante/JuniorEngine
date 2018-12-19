#pragma once
/*
 * Author: David Wong
 * Email: david.wongcascante@digipen.edu
 * Date Created: 28-Apr-2018
 * Last Modified: 29-Oct-2018
 * Description: Let other classes read/write into files
*/

namespace Junior
{
	class ISerializable
	{
	public:
		// Public Member Functions //
		virtual void Serialize() = 0;
		virtual void Deserialize() = 0;
	};
}