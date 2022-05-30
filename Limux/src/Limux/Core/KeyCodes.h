#pragma once

namespace LMX
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define LMX_KEY_SPACE           ::LMX::Key::Space
#define LMX_KEY_APOSTROPHE      ::LMX::Key::Apostrophe    /* ' */
#define LMX_KEY_COMMA           ::LMX::Key::Comma         /* , */
#define LMX_KEY_MINUS           ::LMX::Key::Minus         /* - */
#define LMX_KEY_PERIOD          ::LMX::Key::Period        /* . */
#define LMX_KEY_SLASH           ::LMX::Key::Slash         /* / */
#define LMX_KEY_0               ::LMX::Key::D0
#define LMX_KEY_1               ::LMX::Key::D1
#define LMX_KEY_2               ::LMX::Key::D2
#define LMX_KEY_3               ::LMX::Key::D3
#define LMX_KEY_4               ::LMX::Key::D4
#define LMX_KEY_5               ::LMX::Key::D5
#define LMX_KEY_6               ::LMX::Key::D6
#define LMX_KEY_7               ::LMX::Key::D7
#define LMX_KEY_8               ::LMX::Key::D8
#define LMX_KEY_9               ::LMX::Key::D9
#define LMX_KEY_SEMICOLON       ::LMX::Key::Semicolon     /* ; */
#define LMX_KEY_EQUAL           ::LMX::Key::Equal         /* = */
#define LMX_KEY_A               ::LMX::Key::A
#define LMX_KEY_B               ::LMX::Key::B
#define LMX_KEY_C               ::LMX::Key::C
#define LMX_KEY_D               ::LMX::Key::D
#define LMX_KEY_E               ::LMX::Key::E
#define LMX_KEY_F               ::LMX::Key::F
#define LMX_KEY_G               ::LMX::Key::G
#define LMX_KEY_H               ::LMX::Key::H
#define LMX_KEY_I               ::LMX::Key::I
#define LMX_KEY_J               ::LMX::Key::J
#define LMX_KEY_K               ::LMX::Key::K
#define LMX_KEY_L               ::LMX::Key::L
#define LMX_KEY_M               ::LMX::Key::M
#define LMX_KEY_N               ::LMX::Key::N
#define LMX_KEY_O               ::LMX::Key::O
#define LMX_KEY_P               ::LMX::Key::P
#define LMX_KEY_Q               ::LMX::Key::Q
#define LMX_KEY_R               ::LMX::Key::R
#define LMX_KEY_S               ::LMX::Key::S
#define LMX_KEY_T               ::LMX::Key::T
#define LMX_KEY_U               ::LMX::Key::U
#define LMX_KEY_V               ::LMX::Key::V
#define LMX_KEY_W               ::LMX::Key::W
#define LMX_KEY_X               ::LMX::Key::X
#define LMX_KEY_Y               ::LMX::Key::Y
#define LMX_KEY_Z               ::LMX::Key::Z
#define LMX_KEY_LEFT_BRACKET    ::LMX::Key::LeftBracket   /* [ */
#define LMX_KEY_BACKSLASH       ::LMX::Key::Backslash     /* \ */
#define LMX_KEY_RIGHT_BRACKET   ::LMX::Key::RightBracket  /* ] */
#define LMX_KEY_GRAVE_ACCENT    ::LMX::Key::GraveAccent   /* ` */
#define LMX_KEY_WORLD_1         ::LMX::Key::World1        /* non-US #1 */
#define LMX_KEY_WORLD_2         ::LMX::Key::World2        /* non-US #2 */

/* Function keys */
#define LMX_KEY_ESCAPE          ::LMX::Key::Escape
#define LMX_KEY_ENTER           ::LMX::Key::Enter
#define LMX_KEY_TAB             ::LMX::Key::Tab
#define LMX_KEY_BACKSPACE       ::LMX::Key::Backspace
#define LMX_KEY_INSERT          ::LMX::Key::Insert
#define LMX_KEY_DELETE          ::LMX::Key::Delete
#define LMX_KEY_RIGHT           ::LMX::Key::Right
#define LMX_KEY_LEFT            ::LMX::Key::Left
#define LMX_KEY_DOWN            ::LMX::Key::Down
#define LMX_KEY_UP              ::LMX::Key::Up
#define LMX_KEY_PAGE_UP         ::LMX::Key::PageUp
#define LMX_KEY_PAGE_DOWN       ::LMX::Key::PageDown
#define LMX_KEY_HOME            ::LMX::Key::Home
#define LMX_KEY_END             ::LMX::Key::End
#define LMX_KEY_CAPS_LOCK       ::LMX::Key::CapsLock
#define LMX_KEY_SCROLL_LOCK     ::LMX::Key::ScrollLock
#define LMX_KEY_NUM_LOCK        ::LMX::Key::NumLock
#define LMX_KEY_PRINT_SCREEN    ::LMX::Key::PrintScreen
#define LMX_KEY_PAUSE           ::LMX::Key::Pause
#define LMX_KEY_F1              ::LMX::Key::F1
#define LMX_KEY_F2              ::LMX::Key::F2
#define LMX_KEY_F3              ::LMX::Key::F3
#define LMX_KEY_F4              ::LMX::Key::F4
#define LMX_KEY_F5              ::LMX::Key::F5
#define LMX_KEY_F6              ::LMX::Key::F6
#define LMX_KEY_F7              ::LMX::Key::F7
#define LMX_KEY_F8              ::LMX::Key::F8
#define LMX_KEY_F9              ::LMX::Key::F9
#define LMX_KEY_F10             ::LMX::Key::F10
#define LMX_KEY_F11             ::LMX::Key::F11
#define LMX_KEY_F12             ::LMX::Key::F12
#define LMX_KEY_F13             ::LMX::Key::F13
#define LMX_KEY_F14             ::LMX::Key::F14
#define LMX_KEY_F15             ::LMX::Key::F15
#define LMX_KEY_F16             ::LMX::Key::F16
#define LMX_KEY_F17             ::LMX::Key::F17
#define LMX_KEY_F18             ::LMX::Key::F18
#define LMX_KEY_F19             ::LMX::Key::F19
#define LMX_KEY_F20             ::LMX::Key::F20
#define LMX_KEY_F21             ::LMX::Key::F21
#define LMX_KEY_F22             ::LMX::Key::F22
#define LMX_KEY_F23             ::LMX::Key::F23
#define LMX_KEY_F24             ::LMX::Key::F24
#define LMX_KEY_F25             ::LMX::Key::F25

/* Keypad */
#define LMX_KEY_KP_0            ::LMX::Key::KP0
#define LMX_KEY_KP_1            ::LMX::Key::KP1
#define LMX_KEY_KP_2            ::LMX::Key::KP2
#define LMX_KEY_KP_3            ::LMX::Key::KP3
#define LMX_KEY_KP_4            ::LMX::Key::KP4
#define LMX_KEY_KP_5            ::LMX::Key::KP5
#define LMX_KEY_KP_6            ::LMX::Key::KP6
#define LMX_KEY_KP_7            ::LMX::Key::KP7
#define LMX_KEY_KP_8            ::LMX::Key::KP8
#define LMX_KEY_KP_9            ::LMX::Key::KP9
#define LMX_KEY_KP_DECIMAL      ::LMX::Key::KPDecimal
#define LMX_KEY_KP_DIVIDE       ::LMX::Key::KPDivide
#define LMX_KEY_KP_MULTIPLY     ::LMX::Key::KPMultiply
#define LMX_KEY_KP_SUBTRACT     ::LMX::Key::KPSubtract
#define LMX_KEY_KP_ADD          ::LMX::Key::KPAdd
#define LMX_KEY_KP_ENTER        ::LMX::Key::KPEnter
#define LMX_KEY_KP_EQUAL        ::LMX::Key::KPEqual

#define LMX_KEY_LEFT_SHIFT      ::LMX::Key::LeftShift
#define LMX_KEY_LEFT_CONTROL    ::LMX::Key::LeftControl
#define LMX_KEY_LEFT_ALT        ::LMX::Key::LeftAlt
#define LMX_KEY_LEFT_SUPER      ::LMX::Key::LeftSuper
#define LMX_KEY_RIGHT_SHIFT     ::LMX::Key::RightShift
#define LMX_KEY_RIGHT_CONTROL   ::LMX::Key::RightControl
#define LMX_KEY_RIGHT_ALT       ::LMX::Key::RightAlt
#define LMX_KEY_RIGHT_SUPER     ::LMX::Key::RightSuper
#define LMX_KEY_MENU            ::LMX::Key::Menu