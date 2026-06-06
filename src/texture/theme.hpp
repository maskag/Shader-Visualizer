#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <array>
#include <string>

using namespace geode::prelude;

namespace theme {
    enum class Themes {
        Visualizer,
        Standard
    };

    inline constexpr std::array allThemes {
        Themes::Visualizer,
        Themes::Standard,
    };

    Themes getCurrentTheme();
    std::string getThemeKey(Themes key);
    void changeTheme(Themes currentTheme);
    void showSelectPopup();

    class SelectPopup : public geode::Popup {
    protected:
        CCLabelBMFont* m_visualizerLabel = nullptr;
        CCSprite* m_visualizerPreview = nullptr;

        CCLabelBMFont* m_standardLabel = nullptr;
        CCSprite* m_standardPreview = nullptr;

        bool init();
        void updateVisibility(theme::Themes currentTheme);

    public:
        static SelectPopup* create();
        void changeTheme(CCObject* sender);
    };
}
