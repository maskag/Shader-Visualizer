#include "texture.hpp"
#include <Geode/loader/Log.hpp>

namespace texture {
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

    // todo: theme support in the future
    std::string getTheme() {
        return "maskagd.";
    }

    bool hasWord(const std::string& key ,const std::string& word) {
        return key.find(word) != std::string::npos;
    }

    bool miscSprite(const std::string& key) {
        if(getTheme() != "maskagd.") {
            return false;
        }   

        if(hasWord(key, "toggle")) {
            return true;
        }

        if(hasWord(key, "reset")) {
            return true;
        }

        if(hasWord(key, "spawnParticle")) {
            return true;
        }

        if(hasWord(key, "linkVisible")) {
            return true;
        }

        if(hasWord(key, "bpm")) {
            return true;
        }

        if(hasWord(key, "gradient")) {
            return true;
        }

        if(hasWord(key, "rotateGameplay")) {
            return true;
        }

        return false;
    }

    std::string sprite(std::string const& key) {
        auto theme = getTheme();

        if (key.starts_with("gl.")) {
            return Mod::get()->expandSpriteName(key + ".png");
        }

        if (hasWord(key, "areaStop") || hasWord(key, "enterStop")) {
            return getSwitchValue("color-stop")
                ? Mod::get()->expandSpriteName(theme + "color_" + key + ".png")
                : Mod::get()->expandSpriteName(theme + key + ".png");
        }

        if (hasWord(key, "shake") && getSwitchValue("new-shake"))
            return "";

        if (hasWord(key, "Block") && getSwitchValue("new-colis"))
            return "";

        if (hasWord(key, "edit_mul"))
            return getSwitchValue("dot-edit")
                ? Mod::get()->expandSpriteName(theme + "edit_dot.png")
                : Mod::get()->expandSpriteName(theme + key + ".png");

        if (miscSprite(key))
            return "";

        return Mod::get()->expandSpriteName(theme + key + ".png");
    }

    std::string rawSprite(std::string const& key) {
        if (key.starts_with("gl.")) {
            return Mod::get()->expandSpriteName(key + ".png");
        }
        return Mod::get()->expandSpriteName(getTheme() + key + ".png");
    }

    CCSprite* createSprite(std::string const& key) {
        auto resolved = texture::sprite(key);
        if (!resolved.empty()) {
            return CCSprite::create(resolved.c_str());
        }
        return CCSprite::create(key.c_str());
    }

    CCSprite* createRawSprite(std::string const& key) {
        auto resolved = texture::rawSprite(key);
        if (!resolved.empty()) {
            return CCSprite::create(resolved.c_str());
        }
        return CCSprite::create(key.c_str());
    }

}
