#include <port/port.hpp>

#include "../irq.hpp"

void system::interrupt::irq::irq0x22(interrupt_frame *frame) {
    // system::io::TextModeScreen &tm =
    // system::io::TextModeScreen::getGobalInstance(); tm.print("irq0x22
    // triggered\n");
    system::io::port::writeBtye(0x20, 0x20);
}