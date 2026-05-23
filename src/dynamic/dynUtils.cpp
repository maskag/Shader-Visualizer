#include "dynamic.hpp"
#include "cache.hpp"
#include <Geode/binding/ColorAction.hpp>
#include <Geode/binding/ColorActionSprite.hpp>
#include <Geode/utils/general.hpp>
#include <Geode/utils/string.hpp>

using namespace geode::prelude;

namespace dynUtils {

    // Get a trigger settings by key
    std::optional<int> getIntKey(GameObject* obj, int key) {
        auto layer = LevelEditorLayer::get();
        if (!obj || !layer) {
            return std::nullopt;
        }

        std::string save = obj->getSaveString(layer);
        utils::string::trimRightIP(save, ";");

        auto values = utils::string::splitView(save, ",");
        for (size_t i = 0; i + 1 < values.size(); i += 2) {
            auto currentKey = utils::numFromString<int>(values[i]);
            if (currentKey && *currentKey == key) {
                if (auto value = utils::numFromString<int>(values[i + 1])) {
                    return *value;
                }
                return std::nullopt;
            }
        }

        return std::nullopt;
    }

    // Get a color trigger type
    std::string getColorTriggerBaseTexture(int objectID) {
        switch (objectID) {
            case 29: return texture::sprite("col_bg");
            case 30: return texture::sprite("col_grnd");
            case 105: return texture::sprite("col_obj");
            case 744: return texture::sprite("col_3dl");
            case 900: return texture::sprite("col_grnd2");
            case 915: return texture::sprite("col_line");
            case 899:
            default:
                return texture::sprite("col");
        }
    }

    std::string getAreaTriggerBaseTexture(int objectID) {
        switch (objectID) {
            case 3006: return texture::sprite("areaMove");
            case 3007: return texture::sprite("areaRotate");
            case 3008: return texture::sprite("areaScale");
            case 3009: return texture::sprite("areaFade");
            case 3010: return texture::sprite("areaTint");
            default:
                return texture::sprite("areaMove");
        }
    }

    // Get a effect type of area trigger
    int getAreaBucket(GameObject* obj) {
        if (!obj) return 1;
        int direct = getIntKey(obj, 262).value_or(0);
        bool reverse = getIntKey(obj, 276).value_or(0) != 0;
        bool sided = getIntKey(obj, 283).value_or(0) != 0;
        if (direct == 0) {
            return reverse ? 2 : 1;
        }
        if (direct == 1) {
            if (sided) {
                return reverse ? 4 : 3;
            }
            return reverse ? 6 : 5;
        }
        if (direct == 2) {
            if (sided) {
                return reverse ? 8 : 7;
            }
            return reverse ? 10 : 9;
        }
        return 1;
    }

    ccColor3B getColorTriggerTint(EffectGameObject* obj) {
        if (!obj) return ccColor3B{255, 255, 255};

        auto r = getIntKey(obj, 7);
        auto g = getIntKey(obj, 8);
        auto b = getIntKey(obj, 9);
        if (r && g && b) {
            auto clampByte = [](int v) -> unsigned char {
                if (v < 0) return 0;
                if (v > 255) return 255;
                return static_cast<unsigned char>(v);
            };
            return ccColor3B{
                clampByte(*r),
                clampByte(*g),
                clampByte(*b),
            };
        }

        if (obj->m_mainActionSprite) {
            if (obj->m_mainActionSprite->m_colorAction) {
                return obj->m_mainActionSprite->m_colorAction->m_color;
            }
            return obj->m_mainActionSprite->m_color;
        }
        return obj->m_triggerTargetColor;
    }


    bool dynLogic(const dynamic::Settings& s) { return s.logic; }
    bool dynCam(const dynamic::Settings& s) { return s.cam; }
    bool dynGame(const dynamic::Settings& s) { return s.game; }
    bool dynColor(const dynamic::Settings& s) { return s.dynColor; }
}

namespace cacheUtils {

    bool isLevelObject(GameObject* obj) {
        auto layer = LevelEditorLayer::get();
        return obj &&
            layer &&
            layer->m_objects &&
            layer->m_objects->containsObject(obj);
    }

    bool isDynamicColorTriggerID(int objectID) {
        switch (objectID) {
            case 899:
            case 29:
            case 30:
            case 105:
            case 744:
            case 900:
            case 915:
                return true;
            default:
                return false;
        }
    }

    bool settingsEqual(const Settings& a, const Settings& b) {
        return a.logic == b.logic &&
            a.dotEdit == b.dotEdit &&
            a.cam == b.cam &&
            a.game == b.game &&
            a.dynColor == b.dynColor &&
            a.offEv == b.offEv;
    }
}
