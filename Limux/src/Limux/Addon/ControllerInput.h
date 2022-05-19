#pragma once
#include "Limux/Core/KeyCodes.h"
#include "Limux/Events/Event.h"
#include "Limux/Core/Input.h"

namespace LMX::CtrlInp
{
		static std::map<std::string, std::vector<std::vector<int>>> KeyMap {
			{ "Left",	{{LMX_KEY_A, LMX_KEY_LEFT	}}},
			{ "Right",	{{LMX_KEY_D, LMX_KEY_RIGHT	}}},
			{ "Up",		{{LMX_KEY_W, LMX_KEY_UP		}}},
			{ "Down",	{{LMX_KEY_S, LMX_KEY_DOWN	}}},
			{ "Jump",	{{LMX_KEY_SPACE}}},
			{ "Attack1",{{LMX_KEY_E}}},
			{ "Crouch",	{{LMX_KEY_LEFT_CONTROL, LMX_KEY_RIGHT_CONTROL, LMX_KEY_C}}},
			{ "Boost",	{{LMX_KEY_LEFT_SHIFT, LMX_KEY_RIGHT_SHIFT}}},
			{ "Copy",	{{LMX_KEY_LEFT_CONTROL, LMX_KEY_RIGHT_CONTROL}, {LMX_KEY_C}}},
			{ "Paste",	{{LMX_KEY_LEFT_CONTROL, LMX_KEY_RIGHT_CONTROL}, {LMX_KEY_V}}},
		};
		static inline bool IsPressed(std::string input)
		{
			{
				if (KeyMap.contains(input))
				{
					auto KeyList = KeyMap.at(input);
					bool result = true;
					for (auto keyCombi : KeyList)
					{
						bool keyPressed = false;
						for (auto key : keyCombi)
						{
							keyPressed = keyPressed || Input::IsKeyPressed(key);
						}
						result = result && keyPressed;
					}
					return result;
				}
				LMX_WARN("Key Map for \"{0}\" does not exist.", input);
				return false;
			}
		}
		static inline bool CheckEvent(Event& e, std::string input)
		{
			return false;
		}
}