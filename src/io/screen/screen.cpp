#include <global/global.hpp>

namespace {
system::io::entity::Screen gobalInstance;
} // namespace

namespace system::global {
namespace init {
    void initScreen() {
        gobalInstance = system::io::entity::Screen();
    }
} // namespace init

namespace instance {
    system::io::entity::Screen *getScreen() {
        return &gobalInstance;
    }
} // namespace instance

} // namespace system::global
