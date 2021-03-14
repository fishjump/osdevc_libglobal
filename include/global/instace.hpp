#pragma once

#include <text_screen/text_screen.hpp>
#include <screen/screen.hpp>

namespace system::global::instance
{
    system::io::entity::Screen *getScreen();
    system::io::entity::TextScreen *getTextScreen();
} // namespace system::global::instance
