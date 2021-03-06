#include <global/instace.hpp>
#include <keyboard/keyboard.hpp>
#include <port/port.hpp>

#include "../irq.hpp"

void system::interrupt::irq::irq0x21(interrupt_frame *frame) {
    system::io::entity::TextScreen *text_screen =
        system::global::instance::getTextScreen();

    system::io::entity::Keyboard *keyboard =
        system::global::instance::getKeyboard();

    uint8_t scan_code = system::io::port::readBtye(0x60);

    keyboard->enqueue(scan_code);
    system::io::port::writeBtye(0x20, 0x20);
}