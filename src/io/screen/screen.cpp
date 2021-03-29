#include <global/global.hpp>

#include "../../lazyload.hpp"

namespace {
lazyload<system::io::entity::Screen> gobalScreen;
} // namespace

namespace system::global {
namespace init {
    void initScreen() {
        gobalScreen.init();
    }
} // namespace init

namespace instance {
    system::io::entity::Screen *getScreen() {
        return gobalScreen.get();
    }
} // namespace instance

} // namespace system::global
