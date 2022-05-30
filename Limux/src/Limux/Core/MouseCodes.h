#pragma once
namespace LMX
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}
// From glfw3.h
#define LMX_MOUSE_BUTTON_0      ::LMX::Mouse::Button0
#define LMX_MOUSE_BUTTON_1      ::LMX::Mouse::Button1
#define LMX_MOUSE_BUTTON_2      ::LMX::Mouse::Button2
#define LMX_MOUSE_BUTTON_3      ::LMX::Mouse::Button3
#define LMX_MOUSE_BUTTON_4      ::LMX::Mouse::Button4
#define LMX_MOUSE_BUTTON_5      ::LMX::Mouse::Button5
#define LMX_MOUSE_BUTTON_6      ::LMX::Mouse::Button6
#define LMX_MOUSE_BUTTON_7      ::LMX::Mouse::Button7
#define LMX_MOUSE_BUTTON_LAST   ::LMX::Mouse::ButtonLast
#define LMX_MOUSE_BUTTON_LEFT   ::LMX::Mouse::ButtonLeft
#define LMX_MOUSE_BUTTON_RIGHT  ::LMX::Mouse::ButtonRight
#define LMX_MOUSE_BUTTON_MIDDLE ::LMX::Mouse::ButtonMiddle