#include <global/global.hpp>

namespace {
system::io::entity::TextScreen gobalInstance;
} // namespace

namespace system::global {
namespace init {
    void initTextScreen() {
        gobalInstance = system::io::entity::TextScreen();
    }
} // namespace init

namespace instance {
    system::io::entity::TextScreen *getTextScreen() {
        return &gobalInstance;
    }
} // namespace instance

} // namespace system::global
