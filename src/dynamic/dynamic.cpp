#include "dynamic.hpp"
#include "cache.hpp"

namespace dynamic {
    bool g_isToolboxInit = false;

    Settings getSettings() {
        Settings settings;
        settings.logic = getSwitchValue("dyn-logic");
        settings.dotEdit = getSwitchValue("dot-edit");
        settings.cam = getSwitchValue("dyn-cam");
        settings.game = getSwitchValue("dyn-game");
        settings.dynColor = getSwitchValue("dyn-color");
        settings.offEv = Mod::get()->getSettingValue<float>("off-ev");
        return settings;
    }

    void applyUpdates(EffectGameObject* obj, const Settings& settings) {
        if (!obj) {
            return;
        }

        auto rule = cache::findRule(obj->m_objectID);
        if (!rule) {
            return;
        }
        if (!rule->enabled(settings)) {
            return;
        }

        cache::applyAction(rule->action, obj, settings);
    }
}
