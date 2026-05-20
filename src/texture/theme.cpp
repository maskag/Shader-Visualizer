#include "texture.hpp"

using namespace geode::prelude;

namespace theme {

    Themes getCurrentTheme() {
        auto theme = Mod::get()->getSavedValue<std::string>("theme", "visualizer");

        if (theme == "visualizer") {
            return Themes::Visualizer;
        }

        return Themes::Standard;
    }

    std::string getThemeKey(Themes key) {
        switch (key) {
            case Themes::Visualizer:
                return "visualizer";

            case Themes::Standard:
                return "standard";
        }

        return "visualizer";
    }

    void changeTheme(Themes currentTheme) {
        Mod::get()->setSavedValue<std::string>(
            "theme",
            getThemeKey(currentTheme)
        );
    }
}
