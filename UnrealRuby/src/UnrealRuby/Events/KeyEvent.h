#pragma once

#include "Event.h"
#include <sstream>


namespace UnrealRuby {
	class UNREALRUBY_API KeyEvent : public Event
	{
	protected:
		int m_keycode;

		KeyEvent(int keycode)
			:m_keycode(keycode) {}

	public:
		inline int GetKeyCode() const { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};


	class UNREALRUBY_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;

	public:
		KeyPressedEvent(int keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Pressed Event: " << m_keycode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class UNREALRUBY_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key Released Event:" << m_keycode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};

}