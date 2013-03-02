#ifndef AVOCADO_WINDOW_H
#define AVOCADO_WINDOW_H

#include "core/avocado-global.h"

#include <map>
#include <string>

#include "../Graphics/Image.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * A %Window for displaying graphics.
 */
class Window {

public:

	/** Event polling. */
	struct Event {

		/** Standardize mouse buttons. */
		static const std::map<std::string, int> &MouseButtons() {

			static bool initialized = false;
			static std::map<std::string, int> m_mouseButtons;

			if (!initialized) {
				initialized = true;

				(addMapValues<std::string, int>(m_mouseButtons))

					("ButtonLeft", 1)
					("ButtonMiddle", 2)
					("ButtonRight", 3)
					("WheelUp", 4)
					("WheelDown", 5)
				;
			}

			return m_mouseButtons;
		}

		/**
		 * Standardize key codes.
		 *
		 * We will use ASCII where we can. Anything else will be > 255. There
		 * are no standards for non-ASCII keycodes (as far as I can tell), so
		 * we will simply resign to standardizing between different SPIIs.
		 */
		static const std::map<std::string, int> &KeyCodes() {

			static bool initialized = false;
			static std::map<std::string, int> m_keyCodes;

			if (!initialized) {
				initialized = true;

				(addMapValues<std::string, int>(m_keyCodes))

					("Backspace", 8)
					("Tab", 9)
					("Enter", 13)
					("Escape", 27)
					("Space", 32)
					("ExclamationMark", 33)
					("QuotationMark", 34)
					("NumberSign", 35)
					("DollarSign", 36)
					("PercentSign", 37)
					("Ampersand", 38)
					("Apostrophe", 39)
					("LeftParenthesis", 40)
					("RightParenthesis", 41)
					("Asterisk", 42)
					("Plus", 43)
					("Comma", 44)
					("Dash", 45)
					("Period", 46)
					("Slash", 47)

					("0", 48)
					("1", 49)
					("2", 50)
					("3", 51)
					("4", 52)
					("5", 53)
					("6", 54)
					("7", 55)
					("8", 56)
					("9", 57)

					("Colon", 58)
					("Semicolon", 59)
					("LessThan", 60)
					("Equals", 61)
					("GreaterThan", 62)
					("QuestionMark", 63)
					("At", 64)

					("A", 65)
					("B", 66)
					("C", 67)
					("D", 68)
					("E", 69)
					("F", 70)
					("G", 71)
					("H", 72)
					("I", 73)
					("J", 74)
					("K", 75)
					("L", 76)
					("M", 77)
					("N", 78)
					("O", 79)
					("P", 80)
					("Q", 81)
					("R", 82)
					("S", 83)
					("T", 84)
					("U", 85)
					("V", 86)
					("W", 87)
					("X", 88)
					("Y", 89)
					("Z", 90)

					("LeftBracket", 91)
					("Backslash", 92)
					("RightBracket", 93)
					("Caret", 94)
					("Underscore", 95)
					("Backtick", 96)

					// Lowercase alphabet excluded...

					("LeftBrace", 123)
					("Pipe", 124)
					("RightBrace", 125)
					("Tilde", 126)
					("Delete", 127)

					("F1", 256)
					("F2", 257)
					("F3", 258)
					("F4", 259)
					("F5", 260)
					("F6", 261)
					("F7", 262)
					("F8", 263)
					("F9", 264)
					("F10", 265)
					("F11", 266)
					("F12", 267)

					("ArrowUp", 268)
					("ArrowRight", 269)
					("ArrowDown", 270)
					("ArrowLeft", 271)

					("Insert", 272)
					("Home", 273)
					("End", 274)
					("PageUp", 275)
					("PageDown", 276)

					("Control", 277)
					("Alt", 278)
					("Shift", 279)
					("Meta", 280)
					("Function", 281)
				;
			}

			return m_keyCodes;
		}

		/** Standardize key down event. */
		struct KeyDown {
			int code;
		};

		/** Standardize key up event. */
		struct KeyUp {
			int code;
		};

		/** Standardize joystick axis event. */
		struct JoyAxis {
			int stickIndex;
			int axis;
			double value;

			bool operator == (const JoyAxis &other) {
				return other.stickIndex == stickIndex && other.axis == axis;
			}
		};

		/** Standardize joystick button down event. */
		struct JoyButtonDown {
			int stickIndex;
			int button;

			bool operator == (const JoyButtonDown &other) {
				return other.stickIndex == stickIndex && other.button == button;
			}
		};

		/** Standardize joystick button up event. */
		struct JoyButtonUp {
			int stickIndex;
			int button;

			bool operator == (const JoyButtonUp &other) {
				return other.stickIndex == stickIndex && other.button == button;
			}
		};

		/** Standardize mouse button down event. */
		struct MouseButtonDown {
			int x;
			int y;
			int button;
		};

		/** Standardize mouse button up event. */
		struct MouseButtonUp {
			int x;
			int y;
			int button;
		};

		/** Standardize mouse move event. */
		struct MouseMove {
			int x;
			int y;
		};

		/** Standardize screen resize event. */
		struct Resize {
			int width;
			int height;
		};

		std::deque<KeyDown> keyDown;
		std::deque<KeyUp> keyUp;

		std::deque<JoyAxis> joyAxis;
		std::deque<JoyButtonDown> joyButtonDown;
		std::deque<JoyButtonUp> joyButtonUp;

		std::deque<MouseButtonDown> mouseButtonDown;
		std::deque<MouseButtonUp> mouseButtonUp;
		std::deque<MouseMove> mouseMove;

		Resize resize;

		bool quit;

		Event()
		{
			reset();
		}

		void reset() {

			keyDown.clear();
			keyUp.clear();

			joyAxis.clear();
			joyButtonDown.clear();
			joyButtonUp.clear();

			mouseButtonDown.clear();
			mouseButtonUp.clear();
			mouseMove.clear();

			resize.width = resize.height = -1;
			quit = false;
		}

		bool empty() {

			if (keyDown.size() > 0) return false;
			if (keyUp.size() > 0) return false;

			if (joyAxis.size() > 0) return false;
			if (joyButtonDown.size() > 0) return false;
			if (joyButtonUp.size() > 0) return false;

			if (mouseButtonDown.size() > 0) return false;
			if (mouseMove.size() > 0) return false;
			if (mouseButtonUp.size() > 0) return false;

			if (resize.width != -1 && resize.height != -1) return false;

			if (quit) return false;

			return true;
		}
	};

	/**
	 * Flags used when creating a window.
	 */
	enum WindowFlags {

		/** Nothing special. */
		Flags_Default    = 0,

		/** Fullscreen window. */
		Flags_Fullscreen = 1
	};

	Window();

	/**
	 * Destroy the window.
	 */
	virtual ~Window() {}

	/**
	 * Show the window.
	 */
	virtual void display() {}

	/**
	 * %Window flags.
	 */
	int flags() const;

	/**
	 * %Window height.
	 */
	int height() const;

	/**
	 * Poll events.
	 */
	virtual Event pollEvents() = 0;

	/**
	 * Render an Image onto this window.
	 */
	virtual void render(Image *working, int x, int y, int w, int h) = 0;

	/**
	 * Set the window flags.
	 */
	virtual void setFlags(WindowFlags flags = Flags_Default);

	/**
	 * Set the window size.
	 */
	virtual void setSize(int width, int height);

	/**
	 * Set whether the mouse is visible while hovering over the window.
	 */
	virtual void setMouseVisibility(bool visible) = 0;

	/**
	 * Set the window title.
	 */
	virtual void setWindowTitle(const std::string &window, const std::string &iconified = "") = 0;

	/**
	 * %Window width.
	 */
	int width() const;

	/**
	 * Manages the concrete %Window factory instance.
	 */
	static FactoryManager<Window> factoryManager;

private:

	int m_width;
	int m_height;

	int m_flags;
};

/**
 * @ingroup Manufacturing
 * @ingroup SPI
 */
template <>
class AbstractFactory<Window> {

public:

	virtual ~AbstractFactory<Window>() {}

	virtual Window *create() = 0;

};

/**
 * @}
 */

}

#endif // AVOCADO_WINDOW_H
