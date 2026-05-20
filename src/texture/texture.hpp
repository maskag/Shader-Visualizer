#pragma once

#include <Geode/Geode.hpp>
#include <unordered_map>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

bool getSwitchValue(std::string const& key);

namespace texture {
    extern const std::unordered_map<int, std::string> iconMap;

    void setObjIcon(EffectGameObject* obj, const std::string& texture);

    std::string sprite(std::string const& key);
    CCSprite* createSprite(std::string const& key);
    std::string rawSprite(std::string const& key);
    CCSprite* createRawSprite(std::string const& key);
}

namespace theme {
    enum class Themes {
        Visualizer,
        Standard
    };

    Themes getCurrentTheme();
    std::string getThemeKey(Themes key);
    void changeTheme(Themes thecurrentThememe);

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
