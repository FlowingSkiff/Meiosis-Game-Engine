#pragma once
#include "../Core/Core.hpp"
#include "Event.hpp"
#include "../Core/Keycodes.hpp"
namespace Genesis
{
    class KeyEvent : public Event
    {
        public:
            inline KeyCode keyCode() const { return m_key_code; }
            virtual int categoryFlags() const override { return static_cast<int>(EventCategory::Keyboard) | static_cast<int>(EventCategory::Input); }
        protected:
            KeyEvent(const KeyCode keycode) : m_key_code(keycode) { }
            KeyCode m_key_code;
    };
}