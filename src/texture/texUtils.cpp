#include "texture.hpp"
#include <Geode/loader/Log.hpp>
#include <Geode/loader/ModEvent.hpp>
#include <map>
#include <unordered_set>
#include <vector>

namespace texture {

    std::map<theme::Themes, std::unordered_set<std::string>> missingSprites;

    std::string missingSpritesKey(theme::Themes selectedTheme) {
        return "missing-sprites-" + std::to_string(static_cast<int>(selectedTheme));
    }

    std::string themedSpriteName(theme::Themes selectedTheme, std::string_view key) {
        return theme::getThemeKey(selectedTheme) + std::string(key) + ".png";
    }

    bool isMissingSprite(std::string const& name) {
        auto expanded = Mod::get()->expandSpriteName(name);
        auto spr = CCSprite::create(expanded.c_str());
        return !spr || spr->isUsingFallback();
    }

    bool isMissingThemeSprite(theme::Themes selectedTheme, std::string_view key) {
        auto missingIt = missingSprites.find(selectedTheme);
        if (missingIt == missingSprites.end()) {
            return false;
        }

        bool isMissing = missingIt->second.contains(std::string(key));
        return isMissing;
    }

/*
    it can automatically find missing sprites
    and remember them for each theme
    (so it doesn't have to check every time)
*/

    void initializeMissingSprites() {
        auto mod = Mod::get();
        auto currentVersion = mod->getVersion().toVString();
        auto hasCurrentCache =
            mod->getSavedValue<std::string>("missing-sprites-version") == currentVersion;

        for (auto selectedTheme : theme::allThemes) {
            hasCurrentCache =
                hasCurrentCache && mod->hasSavedValue(missingSpritesKey(selectedTheme));
        }

        missingSprites.clear();

        if (hasCurrentCache) {
            for (auto selectedTheme : theme::allThemes) {
                auto saved = mod->getSavedValue<std::vector<std::string>>(
                    missingSpritesKey(selectedTheme)
                );
                missingSprites[selectedTheme].insert(saved.begin(), saved.end());
            }

            log::debug("Loaded missing sprite cache for mod version {}", currentVersion);
            return;
        }

        for (auto selectedTheme : theme::allThemes) {
            auto& missing = missingSprites[selectedTheme];
            missing.reserve(spriteKeys.size());

            for (auto key : spriteKeys) {
                if (isMissingSprite(themedSpriteName(selectedTheme, key))) {
                    missing.emplace(key);
                }
            }

            log::info(
                "Found {} missing sprites out of {} for theme {}",
                missing.size(),
                spriteKeys.size(),
                theme::getThemeKey(selectedTheme)
            );

            mod->setSavedValue(
                missingSpritesKey(selectedTheme),
                std::vector<std::string>(missing.begin(), missing.end())
            );
        }

        mod->setSavedValue<std::string>("missing-sprites-version", currentVersion);
    }

    bool hasWord(std::string const& key, std::string_view word) {
        return key.contains(word);
    }

    void setObjIcon(EffectGameObject* obj, const std::string& texture) {
        if (!obj) {
            return;
        }
        if (texture.empty()) {
            return;
        }
        if (auto newSpr = CCSprite::create(texture.c_str())) {
            obj->m_addToNodeContainer = true;
            obj->setTexture(newSpr->getTexture());
            obj->setTextureRect(newSpr->getTextureRect());
        }
    }

    std::string sprite(std::string const& key) {
        if (key.starts_with("gl.")) {
            return Mod::get()->expandSpriteName(key + ".png");
        }

        auto currentTheme = theme::getCurrentTheme();

        if (hasWord(key, "areaStop") || hasWord(key, "enterStop")) {
            auto themedKey = getSwitchValue("color-stop")
                ? "color_" + key
                : key;
            auto themed = themedSpriteName(currentTheme, themedKey);

            if (isMissingThemeSprite(currentTheme, themedKey)) {
                return "";
            }

            return Mod::get()->expandSpriteName(themed);
        }

        if (hasWord(key, "shake") && getSwitchValue("new-shake"))
            return "";

        if (hasWord(key, "Block") && getSwitchValue("new-colis"))
            return "";

        if (hasWord(key, "edit_mul")) {
            auto themedKey = getSwitchValue("dot-edit")
                ? std::string("edit_dot")
                : key;
            auto themed = themedSpriteName(currentTheme, themedKey);

            if (isMissingThemeSprite(currentTheme, themedKey)) {
                return "";
            }

            return Mod::get()->expandSpriteName(themed);
        }

        auto themed = themedSpriteName(currentTheme, key);
        if (isMissingThemeSprite(currentTheme, key)) {
            return "";
        }

        return Mod::get()->expandSpriteName(themed);
    }

    std::string rawSprite(std::string const& key) {
        return rawSprite(key, theme::getCurrentTheme());
    }

    std::string rawSprite(std::string const& key, theme::Themes selectedTheme) {
        if (key.starts_with("gl.")) {
            return Mod::get()->expandSpriteName(key + ".png");
        }

        auto themed = themedSpriteName(selectedTheme, key);
        if (isMissingThemeSprite(selectedTheme, key)) {
            return "";
        }

        return Mod::get()->expandSpriteName(themed);
    }

    CCSprite* createSprite(std::string const& key) {
        auto resolved = texture::sprite(key);
        if (!resolved.empty()) {
            return CCSprite::create(resolved.c_str());
        }
        return nullptr;
    }

    CCSprite* createRawSprite(std::string const& key) {
        return createRawSprite(key, theme::getCurrentTheme());
    }

    CCSprite* createRawSprite(std::string const& key, theme::Themes selectedTheme) {
        auto resolved = texture::rawSprite(key, selectedTheme);
        if (!resolved.empty()) {
            return CCSprite::create(resolved.c_str());
        }
        return nullptr;
    }

}

$on_mod(Loaded) {
    texture::initializeMissingSprites();
}
