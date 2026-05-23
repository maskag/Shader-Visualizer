#pragma once

#include "../texture/texture.hpp"

#include <Geode/utils/general.hpp>

#include <optional>
#include <string>

bool getSwitchValue(std::string const& key);

namespace dynamic {
    struct Settings {
        bool logic, dotEdit, cam, game, dynColor;
        float offEv;
    };

    Settings getSettings();
    void applyUpdates(EffectGameObject* obj, const Settings& settings);

    void updateCompTexture(ItemTriggerGameObject* obj);
    void updateEditTexture(ItemTriggerGameObject* obj, bool dot);
    void updatePersTexture(ItemTriggerGameObject* obj);

    void updateAreaTexture(EnterEffectObject* obj);

    void updateSongTexture(SongTriggerGameObject* obj);
    void updateTimeTexture(EffectGameObject* obj);
    void updateSFXTexture(SFXTriggerGameObject* obj);
    void updateUiTexture(UISettingsGameObject* obj);
    void updateEventTexture(EventLinkTrigger* obj, float gap);
    void updateStartTexture(StartPosObject* obj);

    void updateStopTexture(EffectGameObject* obj);
    void updateMoveTexture(EffectGameObject* obj);
    void updateRotateTexture(EffectGameObject* obj);

    void updatePickupTexture(CountTriggerGameObject* obj);
    void updateCountTexture(CountTriggerGameObject* obj);

    void updateColisTexture(EffectGameObject* obj);
    void updateSpawnTexture(EffectGameObject* obj);
    void updateGravityTexture(EffectGameObject* obj);
    void updateColorTexture(EffectGameObject* obj);
    void updatePulseTexture(EffectGameObject* obj);

    void updateOffsetCamTexture(CameraTriggerGameObject* obj);
    void updateRotateCamTexture(CameraTriggerGameObject* obj);
    void updateEdgeCamTexture(CameraTriggerGameObject* obj);
    void updateStaticCamTexture(CameraTriggerGameObject* obj);
}

namespace dynUtils {
    std::optional<int> getIntKey(GameObject* obj, int key);
    std::string getColorTriggerBaseTexture(int objectID);
    std::string getAreaTriggerBaseTexture(int objectID);
    int getAreaBucket(GameObject* obj);
    ccColor3B getColorTriggerTint(EffectGameObject* obj);

    bool dynLogic(const dynamic::Settings& s);
    bool dynCam(const dynamic::Settings& s);
    bool dynGame(const dynamic::Settings& s);
    bool dynColor(const dynamic::Settings& s);
}
