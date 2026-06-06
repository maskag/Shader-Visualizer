#include "theme.hpp"

using namespace geode::prelude;

namespace theme {

    Themes getCurrentTheme() {
        auto theme = Mod::get()->getSavedValue<int>(
            "theme",
            static_cast<int>(Themes::Visualizer)
        );

        switch (theme) {
            case static_cast<int>(Themes::Standard):
                return Themes::Standard;

            case static_cast<int>(Themes::Visualizer):
            default:
                return Themes::Visualizer;
        }
    }

    std::string getThemeKey(Themes key) {
        switch (key) {
            case Themes::Visualizer:
                return "maskagd.";

            case Themes::Standard:
                return "robtop.";
        }

        return "maskagd.";
    }

    void changeTheme(Themes currentTheme) {
        Mod::get()->setSavedValue<int>(
            "theme",
            static_cast<int>(currentTheme)
        );
    }
}
