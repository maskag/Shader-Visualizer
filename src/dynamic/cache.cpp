#include "cache.hpp"
#include <Geode/binding/CameraTriggerGameObject.hpp>
#include <Geode/binding/CountTriggerGameObject.hpp>
#include <Geode/binding/EnterEffectObject.hpp>
#include <Geode/binding/EventLinkTrigger.hpp>
#include <Geode/binding/ItemTriggerGameObject.hpp>
#include <Geode/binding/SFXTriggerGameObject.hpp>
#include <Geode/binding/StartPosObject.hpp>
#include <Geode/binding/UISettingsGameObject.hpp>
#include <Geode/utils/general.hpp>
#include <unordered_map>
#include <vector>

namespace cache {
    namespace {
        std::unordered_map<EffectGameObject*, CacheSig> g_cache;
        bool g_hasLastSettings = false;
        Settings g_lastSettings {};
        std::vector<EffectGameObject*> g_dirtyObjects;

        const Rule kRules[] = {
            {3604, dynUtils::dynLogic, sigEvent, Action::Event},
            {1934, dynUtils::dynGame, sigSong, Action::Song},
            {3614, dynUtils::dynGame, sigTime, Action::Time},
            {3615, dynUtils::dynGame, sigTime, Action::Time},
            {3617, dynUtils::dynGame, sigTime, Action::Time},
            {3602, dynUtils::dynGame, sigSfx, Action::Sfx},
            {3620, dynUtils::dynLogic, sigComp, Action::Comp},
            {3619, dynUtils::dynLogic, sigEdit, Action::Edit},
            {3641, dynUtils::dynLogic, sigPers, Action::Pers},
            {3613, dynUtils::dynLogic, sigUi, Action::Ui},
            {31, dynUtils::dynGame, sigStart, Action::Start},
            {1616, dynUtils::dynLogic, sigStopTexture, Action::Stop},
            {901, dynUtils::dynGame, sigMove, Action::Move},
            {1346, dynUtils::dynGame, sigRotate, Action::Rotate},
            {1817, dynUtils::dynLogic, sigPickup, Action::Pickup},
            {1815, dynUtils::dynLogic, sigColis, Action::Colis},
            {1268, dynUtils::dynLogic, sigSpawn, Action::Spawn},
            {2066, dynUtils::dynGame, sigGravity, Action::Gravity},
            {3006, dynUtils::dynGame, sigArea, Action::Area},
            {3007, dynUtils::dynGame, sigArea, Action::Area},
            {3008, dynUtils::dynGame, sigArea, Action::Area},
            {3009, dynUtils::dynGame, sigArea, Action::Area},
            {3010, dynUtils::dynGame, sigArea, Action::Area},
            {899, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {29, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {30, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {105, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {744, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {900, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {915, dynUtils::dynColor, sigColorTrigger, Action::Color},
            {1006, dynUtils::dynColor, sigPulse, Action::Pulse},
            {1811, dynUtils::dynLogic, sigCount, Action::Count},
            {1916, dynUtils::dynCam, sigOffsetCam, Action::OffsetCam},
            {2015, dynUtils::dynCam, sigRotateCam, Action::RotateCam},
            {1914, dynUtils::dynCam, sigStaticCam, Action::StaticCam},
            {2062, dynUtils::dynCam, sigEdgeCam, Action::EdgeCam},
        };
    }

    const Rule* findRule(int objectID) {
        for (const auto& rule : kRules) {
            if (rule.objectID == objectID) return &rule;
        }
        return nullptr;
    }

    void applyAction(Action action, EffectGameObject* obj, const Settings& s) {
        switch (action) {
            case Action::Event:
                dynamic::updateEventTexture(typeinfo_cast<EventLinkTrigger*>(obj), s.offEv);
                break;
            case Action::Song:
                dynamic::updateSongTexture(typeinfo_cast<SongTriggerGameObject*>(obj));
                break;
            case Action::Time:
                dynamic::updateTimeTexture(obj);
                break;
            case Action::Sfx:
                dynamic::updateSFXTexture(typeinfo_cast<SFXTriggerGameObject*>(obj));
                break;
            case Action::Comp:
                dynamic::updateCompTexture(typeinfo_cast<ItemTriggerGameObject*>(obj));
                break;
            case Action::Area:
                dynamic::updateAreaTexture(typeinfo_cast<EnterEffectObject*>(obj));
                break;
            case Action::Edit:
                dynamic::updateEditTexture(typeinfo_cast<ItemTriggerGameObject*>(obj), s.dotEdit);
                break;
            case Action::Pers:
                dynamic::updatePersTexture(typeinfo_cast<ItemTriggerGameObject*>(obj));
                break;
            case Action::Ui:
                dynamic::updateUiTexture(typeinfo_cast<UISettingsGameObject*>(obj));
                break;
            case Action::Start:
                dynamic::updateStartTexture(typeinfo_cast<StartPosObject*>(obj));
                break;
            case Action::Stop:
                dynamic::updateStopTexture(obj);
                break;
            case Action::Move:
                dynamic::updateMoveTexture(obj);
                break;
            case Action::Rotate:
                dynamic::updateRotateTexture(obj);
                break;
            case Action::Pickup:
                dynamic::updatePickupTexture(typeinfo_cast<CountTriggerGameObject*>(obj));
                break;
            case Action::Colis:
                dynamic::updateColisTexture(obj);
                break;
            case Action::Spawn:
                dynamic::updateSpawnTexture(obj);
                break;
            case Action::Gravity:
                dynamic::updateGravityTexture(typeinfo_cast<EffectGameObject*>(obj));
                break;
            case Action::Color:
                dynamic::updateColorTexture(obj);
                break;
            case Action::Pulse:
                dynamic::updatePulseTexture(obj);
                break;
            case Action::Count:
                dynamic::updateCountTexture(typeinfo_cast<CountTriggerGameObject*>(obj));
                break;
            case Action::OffsetCam:
                dynamic::updateOffsetCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj));
                break;
            case Action::RotateCam:
                dynamic::updateRotateCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj));
                break;
            case Action::StaticCam:
                dynamic::updateStaticCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj));
                break;
            case Action::EdgeCam:
                dynamic::updateEdgeCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj));
                break;
        }
    }

    CacheSig getSignature(EffectGameObject* obj, const Settings& s) {
        if (!obj) return {};
        auto rule = findRule(obj->m_objectID);
        if (!rule || !rule->enabled(s)) return {};
        return rule->signature(obj, s);
    }

    void applyUpdatesCached(EffectGameObject* obj, const dynamic::Settings& s) {
        if (!obj) {
            return;
        }
        if (!cacheUtils::isLevelObject(obj)) {
            g_cache.erase(obj);
            return;
        }

        if (cacheUtils::isDynamicColorTriggerID(obj->m_objectID)) {
            dynamic::applyUpdates(obj, s);
            return;
        }

        auto sig = getSignature(obj, s);

        if (sig.empty()) {
            g_cache.erase(obj);
            return;
        }

        auto it = g_cache.find(obj);
        if (it != g_cache.end() && it->second == sig) {
            return;
        }

        g_cache[obj] = sig;
        dynamic::applyUpdates(obj, s);
    }

    void applyChangesGlobal() {
        auto lel = LevelEditorLayer::get();
        if (!lel || !lel->m_objects) {
            return;
        }
        
        if (!getSwitchValue("dyn-enable")) {
            return;
        }

        auto settings = dynamic::getSettings();
        bool settingsChanged = !g_hasLastSettings || !cacheUtils::settingsEqual(settings, g_lastSettings);
        g_hasLastSettings = true;
        g_lastSettings = settings;

        if (!settingsChanged && g_dirtyObjects.empty()) {
            return;
        }

        if (settingsChanged) {
            Ref<CCArray> arr = lel->m_objects;
            for (auto obj : CCArrayExt<EffectGameObject*>(arr)) {
                if (obj) {
                    applyUpdatesCached(obj, settings);
                }
            }
        } 
        
        else {
            for (auto obj : g_dirtyObjects) {
                applyUpdatesCached(obj, settings);
            }
        }

        g_dirtyObjects.clear();
    }

    void markDirty(EffectGameObject* obj) {
        if (!obj) {
            return;
        }
        g_dirtyObjects.push_back(obj);
    }

    void markDirty(CCArray* objects) {
        if (!objects) {
            return;
        }
        for (auto obj : CCArrayExt<EffectGameObject*>(objects)) {
            if (obj) markDirty(obj);
        }
    }

    void clear() {
        g_cache.clear();
        g_dirtyObjects.clear();
        g_hasLastSettings = false;
    }
}
