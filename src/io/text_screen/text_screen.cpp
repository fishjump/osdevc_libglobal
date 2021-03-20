#include <global/global.hpp>

namespace {
system::io::entity::TextScreen gobalInstance;
} // namespace

namespace system::global {
namespace init {
    void initTextScreen(system::media::entity::Font defaultFont, system::media::entity::Color defaultColor) {
        gobalInstance = system::io::entity::TextScreen(defaultFont, defaultColor);
    }
} // namespace init

namespace instance {
    system::io::entity::TextScreen *getTextScreen() {
        return &gobalInstance;
    }
} // namespace instance

} // namespace system::global
