#include "dynamic/dynamic.hpp"
#include "dynamic/cache.hpp"
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/SetupTriggerPopup.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/LevelSettingsObject.hpp>
#include <Geode/modify/LevelSettingsLayer.hpp>
#include <Geode/modify/SetupCameraOffsetTrigger.hpp>
#include <Geode/modify/SetupCameraModePopup.hpp>
#include <Geode/modify/ColorSelectPopup.hpp>


static bool s_dynamicReady = false;

static bool isModEnabled() {
    return getSwitchValue("new-triggers");
}

static void refreshLevelIcons() {
    auto lel = LevelEditorLayer::get();
    if (!lel || !lel->m_objects) {
        return;
    }

    Ref<CCArray> arr = lel->m_objects;
    for (auto obj : CCArrayExt<EffectGameObject*>(arr)) {
        if (!obj) {
            continue;
        }
        obj->customSetup();
    }

    cache::clear();
    if (isModEnabled() && getSwitchValue("dyn-enable")) {
        cache::applyChangesGlobal();
    }
}

static void applyDynamicToObjects(CCArray* objects) {
    if (!objects) {
        return;
    }
    if (!isModEnabled() || !s_dynamicReady || !getSwitchValue("dyn-enable")) {
        return;
    }

    auto ds = dynamic::getSettings();
    for (auto obj : CCArrayExt<GameObject*>(objects)) {
        if (auto eff = typeinfo_cast<EffectGameObject*>(obj)) {
            cache::applyUpdatesCached(eff, ds);
        }
    }
}

// change texture
class $modify(MyEffectGameObject, EffectGameObject) {
    void customSetup() {
        EffectGameObject::customSetup();

        if (!isModEnabled()) {
            return;
        }

        int id = m_objectID;

        auto it = texture::iconMap.find(id);

        if (it != texture::iconMap.end()) {
            auto icon = texture::sprite(it->second);
            if (icon == "") {
                return;
            }
            if (!icon.empty()) {
                texture::setObjIcon(this, icon);
            }
        }

       if (!dynamic::g_isToolboxInit && s_dynamicReady && getSwitchValue("dyn-enable")) {
            auto ds = dynamic::getSettings();
            cache::applyUpdatesCached(this, ds);
        }
    }
};

// dynamic texture apply (create, copy...)
class $modify(ShowDynamic, EditorUI) {
    bool init(LevelEditorLayer* editorlayer) {
        dynamic::g_isToolboxInit = true;
        
        if (!EditorUI::init(editorlayer)) {
            dynamic::g_isToolboxInit = false;
            return false;
        }

        dynamic::g_isToolboxInit = false;

        if (!isModEnabled()) {
            s_dynamicReady = false;
            return true;
        }

        if (!getSwitchValue("dyn-logic") && !getSwitchValue("dyn-cam") &&
            !getSwitchValue("dyn-game") && !getSwitchValue("dyn-color")) {
            return true;
        }

        s_dynamicReady = false;
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.0f),
            CallFuncExt::create([]() {
                s_dynamicReady = true;
                cache::clear();
                cache::applyChangesGlobal();
            }),
            nullptr
        ));
        return true;
    }

    GameObject* createObject(int objectID, cocos2d::CCPoint position) {
        auto obj = EditorUI::createObject(objectID, position);
        if (!obj) {
            return obj;
        }
        if (!isModEnabled() || !s_dynamicReady || !getSwitchValue("dyn-enable")) {
            return obj;
        }

        if (auto eff = typeinfo_cast<EffectGameObject*>(obj)) {
            auto ds = dynamic::getSettings();
            cache::applyUpdatesCached(eff, ds);
        }
        return obj;
    }

    void onDuplicate(CCObject* sender) {
        EditorUI::onDuplicate(sender);
        applyDynamicToObjects(this->getSelectedObjects());
    }

    void onPaste(CCObject* sender) {
        EditorUI::onPaste(sender);
        applyDynamicToObjects(this->getSelectedObjects());
    }


    void onDeselectAll(CCObject* sender) {
        EditorUI::onDeselectAll(sender);
        if (!isModEnabled()) {
            return;
        }
        cache::applyChangesGlobal();
    }
};

$execute {
    if (auto mod = Mod::get()) {
        listenForSettingChanges<bool>("new-triggers", [](bool) {
            refreshLevelIcons();
        }, mod);

        listenForSettingChanges<bool>("dyn-enable", [](bool value) {
            if (!isModEnabled()) {
                cache::clear();
                refreshLevelIcons();
                return;
            }

            if (value) {
                cache::clear();
            }
            refreshLevelIcons();
        }, mod);
    } else {
    }
}


class $modify(MySetupTriggerPopup, SetupTriggerPopup) {
    void onClose(cocos2d::CCObject* sender) {
        SetupTriggerPopup::onClose(sender); 
        if (!isModEnabled()) {
            return;
        }
        
        cache::markDirty(this->m_gameObject);
        cache::markDirty(this->m_gameObjects);
        cache::applyChangesGlobal();
    }
};

class $modify(MySetupCameraOffsetTrigger, SetupCameraOffsetTrigger) {
    void onClose(cocos2d::CCObject* sender) {
        SetupCameraOffsetTrigger::onClose(sender);
        if (!isModEnabled()) {
            return;
        }

        cache::markDirty(this->m_gameObject);
        cache::markDirty(this->m_gameObjects);
        cache::applyChangesGlobal();
    }
};

class $modify(MyColorSelectPopup, ColorSelectPopup) {
    void applyColorPopupDynamicUpdate() {
        if (!isModEnabled()) {
            return;
        }
        cache::markDirty(this->m_gameObject);
        cache::markDirty(this->m_gameObjects);
        cache::markDirty(this->m_colorObjects);
        cache::applyChangesGlobal();
    }

    void onClose(cocos2d::CCObject* sender) {
        ColorSelectPopup::onClose(sender);
        applyColorPopupDynamicUpdate();
    }

    void closeColorSelect(cocos2d::CCObject* sender) {
        ColorSelectPopup::closeColorSelect(sender);
        applyColorPopupDynamicUpdate();
    }
};

class $modify(MyLevelSettingsLayer, LevelSettingsLayer) {
    void onClose(cocos2d::CCObject* sender) {
        LevelSettingsLayer::onClose(sender);
        if (!isModEnabled()) {
            return;
        }

        if (auto lel = LevelEditorLayer::get()) {
            if (auto objects = lel->m_objects) {
                for (auto obj : CCArrayExt<EffectGameObject*>(objects)) {
                    if (obj && obj->m_objectID == 31) {
                        cache::markDirty(obj);
                    }
                }
            }
        }
        cache::applyChangesGlobal();
    }
};

