#include <global/global.hpp>

#include "../../lazyload.hpp"

namespace {
lazyload<system::io::entity::Keyboard> gobalKeyboard;
} // namespace

namespace system::global {
namespace instance {
    system::io::entity::Keyboard *getKeyboard() {
        return gobalKeyboard.get();
    }
} // namespace instance

} // namespace system::global
