#include "dynamic/dynamic.hpp"
#include "dynamic/cache.hpp"
#include "texture/texture.hpp"
#include "texture/theme.hpp"
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

static void applyLevelObjectAppearance(EffectGameObject* obj) {
    if (!obj || !isModEnabled()) {
        return;
    }

    auto it = texture::iconMap.find(obj->m_objectID);
    if (it != texture::iconMap.end()) {
        auto icon = texture::sprite(it->second);
        if (!icon.empty()) {
            texture::setObjIcon(obj, icon);
            LevelEditorLayer::updateObjectLabel(obj);
        }
    }

    if (s_dynamicReady && getSwitchValue("dyn-enable")) {
        auto settings = dynamic::getSettings();
        dynamic::applyUpdates(obj, settings);
    }
}

static void applyLevelObjectAppearances(CCArray* objects) {
    if (!objects || !isModEnabled()) {
        return;
    }

    for (auto obj : CCArrayExt<GameObject*>(objects)) {
        applyLevelObjectAppearance(typeinfo_cast<EffectGameObject*>(obj));
    }
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
    applyLevelObjectAppearances(objects);
}

// change texture
class $modify(MyEffectGameObject, EffectGameObject) {
    void customSetup() {
        EffectGameObject::customSetup();

        if (!isModEnabled()) {
            return;
        }

        if (theme::getCurrentTheme() == theme::Themes::Standard &&
            !cacheUtils::isLevelObject(this)) {
            return;
        }

        int id = m_objectID;

        auto it = texture::iconMap.find(id);

        if (it != texture::iconMap.end()) {
            auto icon = texture::sprite(it->second);
            if (!icon.empty()) {
                texture::setObjIcon(this, icon);
            }
        }

       if (s_dynamicReady && getSwitchValue("dyn-enable")) {
            auto ds = dynamic::getSettings();
            cache::applyUpdatesCached(this, ds);
        }
    }
};

// dynamic texture apply (create, copy...)
class $modify(ShowDynamic, EditorUI) {
    bool init(LevelEditorLayer* editorlayer) {
        if (!EditorUI::init(editorlayer)) {
            return false;
        }

        if (!isModEnabled()) {
            s_dynamicReady = false;
            return true;
        }

        s_dynamicReady = false;
        this->runAction(CCSequence::create(
            CCDelayTime::create(0.0f),
            CallFuncExt::create([]() {
                s_dynamicReady = true;
                cache::clear();
                if (auto lel = LevelEditorLayer::get()) {
                    applyLevelObjectAppearances(lel->m_objects);
                }
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

        applyLevelObjectAppearance(typeinfo_cast<EffectGameObject*>(obj));
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

    CCArray* pasteObjects(gd::string str, bool withColor, bool noUndo) {
        auto objects = EditorUI::pasteObjects(str, withColor, noUndo);
        applyLevelObjectAppearances(objects);
        return objects;
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
        Ref<EffectGameObject> gameObject = this->m_gameObject;
        Ref<CCArray> gameObjects = this->m_gameObjects;

        SetupTriggerPopup::onClose(sender); 
        if (!isModEnabled()) {
            return;
        }
        
        cache::markDirty(gameObject);
        cache::markDirty(gameObjects);
        cache::applyChangesGlobal();
    }
};

class $modify(MySetupCameraOffsetTrigger, SetupCameraOffsetTrigger) {
    void onClose(cocos2d::CCObject* sender) {
        Ref<EffectGameObject> gameObject = this->m_gameObject;
        Ref<CCArray> gameObjects = this->m_gameObjects;

        SetupCameraOffsetTrigger::onClose(sender);
        if (!isModEnabled()) {
            return;
        }

        cache::markDirty(gameObject);
        cache::markDirty(gameObjects);
        cache::applyChangesGlobal();
    }
};

class $modify(MyColorSelectPopup, ColorSelectPopup) {
    static void applyColorPopupDynamicUpdate(
        EffectGameObject* gameObject,
        CCArray* gameObjects,
        CCArray* colorObjects
    ) {
        if (!isModEnabled()) {
            return;
        }

        if (!gameObject || !gameObjects || !colorObjects) {
            return;
        }
        cache::markDirty(gameObject);
        cache::markDirty(gameObjects);
        cache::markDirty(colorObjects);
        cache::applyChangesGlobal();
    }

    void onClose(cocos2d::CCObject* sender) {
        Ref<EffectGameObject> gameObject = this->m_gameObject;
        Ref<CCArray> gameObjects = this->m_gameObjects;
        Ref<CCArray> colorObjects = this->m_colorObjects;
        // This will probably fix color slider bug 
        if (!gameObject || !gameObjects || !colorObjects) {
            return;
        }
        ColorSelectPopup::onClose(sender);
        applyColorPopupDynamicUpdate(gameObject, gameObjects, colorObjects);
    }

    void closeColorSelect(cocos2d::CCObject* sender) {
        Ref<EffectGameObject> gameObject = this->m_gameObject;
        Ref<CCArray> gameObjects = this->m_gameObjects;
        Ref<CCArray> colorObjects = this->m_colorObjects;

        if (!gameObject || !gameObjects || !colorObjects) {
            return;
        }
        ColorSelectPopup::closeColorSelect(sender);
        applyColorPopupDynamicUpdate(gameObject, gameObjects, colorObjects);
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

