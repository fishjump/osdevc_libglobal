#pragma once

#include <font/font.hpp>
#include <screen/screen.hpp>
#include <text_screen/text_screen.hpp>

namespace system::global::instance {
system::io::entity::Screen *    getScreen();
system::io::entity::TextScreen *getTextScreen();
system::media::entity::Font *   getDefaultFont();
} // namespace system::global::instance
