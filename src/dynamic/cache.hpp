#pragma once

#include "dynamic.hpp"

#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

namespace cache {
    using Settings = dynamic::Settings;

    struct CacheSig {
        std::vector<std::variant<double, std::string>> values;

        CacheSig() = default;

        template <class... Values>
        CacheSig(Values... values) {
            (add(values), ...);
        }

        template <
            class Value,
            typename = std::enable_if_t<std::is_arithmetic_v<Value>>
        >
        void add(Value value) {
            values.emplace_back(static_cast<double>(value));
        }

        void add(std::string const& value) {
            values.emplace_back(value);
        }

        void add(std::string_view value) {
            values.emplace_back(std::string(value));
        }

        bool empty() const {
            return values.empty();
        }

        bool operator==(CacheSig const& other) const {
            return values == other.values;
        }
    };

    enum class Action {
        Event,
        Area,
        Song,
        Time,
        Sfx,
        Comp,
        Edit,
        Pers,
        Ui,
        Start,
        Stop,
        Move,
        Rotate,
        Pickup,
        Colis,
        Spawn,
        Gravity,
        Color,
        Pulse,
        Count,
        OffsetCam,
        RotateCam,
        StaticCam,
        EdgeCam,
    };

    struct Rule {
        int objectID;
        bool (*enabled)(const Settings&);
        CacheSig (*signature)(EffectGameObject*, const Settings&);
        Action action;
    };

    CacheSig sigArea(EffectGameObject* obj, const Settings& settings);
    CacheSig sigEvent(EffectGameObject* obj, const Settings& settings);
    CacheSig sigSong(EffectGameObject* obj, const Settings&);
    CacheSig sigTime(EffectGameObject* obj, const Settings&);
    CacheSig sigSfx(EffectGameObject* obj, const Settings& settings);
    CacheSig sigComp(EffectGameObject* obj, const Settings& settings);
    CacheSig sigEdit(EffectGameObject* obj, const Settings& settings);
    CacheSig sigPers(EffectGameObject* obj, const Settings& settings);
    CacheSig sigUi(EffectGameObject* obj, const Settings& settings);
    CacheSig sigStart(EffectGameObject* obj, const Settings& settings);
    CacheSig sigStopTexture(EffectGameObject* obj, const Settings& settings);
    CacheSig sigMove(EffectGameObject* obj, const Settings& settings);
    CacheSig sigRotate(EffectGameObject* obj, const Settings& settings);
    CacheSig sigPickup(EffectGameObject* obj, const Settings& settings);
    CacheSig sigColis(EffectGameObject* obj, const Settings& settings);
    CacheSig sigSpawn(EffectGameObject* obj, const Settings& settings);
    CacheSig sigGravity(EffectGameObject* obj, const Settings& settings);
    CacheSig sigColorTrigger(EffectGameObject* obj, const Settings& settings);
    CacheSig sigPulse(EffectGameObject* obj, const Settings& settings);
    CacheSig sigCount(EffectGameObject* obj, const Settings& settings);
    CacheSig sigOffsetCam(EffectGameObject* obj, const Settings& settings);
    CacheSig sigRotateCam(EffectGameObject* obj, const Settings& settings);
    CacheSig sigStaticCam(EffectGameObject* obj, const Settings& settings);
    CacheSig sigEdgeCam(EffectGameObject* obj, const Settings& settings);

    const Rule* findRule(int objectID);
    void applyAction(Action action, EffectGameObject* obj, const Settings& settings);
    CacheSig getSignature(EffectGameObject* obj, const Settings& settings);
    void applyUpdatesCached(EffectGameObject* obj, const Settings& settings);
    void applyChangesGlobal();
    void markDirty(EffectGameObject* obj);
    void markDirty(CCArray* objects);
    void clear();
}

namespace cacheUtils {
    using Settings = dynamic::Settings;

    bool isLevelObject(GameObject* obj);
    bool isDynamicColorTriggerID(int objectID);
    bool settingsEqual(const Settings& a, const Settings& b);
}
