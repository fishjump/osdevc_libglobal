#include <global/global.hpp>

#include "../../lazyload.hpp"

namespace {
lazyload<system::io::entity::TextScreen> gobalTextScreen;
} // namespace

namespace system::global {
namespace init {
    void initTextScreen(system::media::entity::Font  defaultFont,
                        system::media::entity::Color defaultColor) {
        gobalTextScreen.init(defaultFont, defaultColor);
    }
} // namespace init

namespace instance {
    system::io::entity::TextScreen *getTextScreen() {
        return gobalTextScreen.get();
    }
} // namespace instance

} // namespace system::global
