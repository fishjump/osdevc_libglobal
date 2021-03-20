#pragma once

#include <color/color.hpp>
#include <font/font.hpp>

namespace system::global::init {
void initIdt();
void initPic();
void initMemory();
void initDefaultFont();
void initScreen();
void initTextScreen(system::media::entity::Font  defaultFont,
                    system::media::entity::Color defaultColor);
} // namespace system::global::init
