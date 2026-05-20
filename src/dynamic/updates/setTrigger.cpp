#include "../dynamic.hpp"
#include "../cache.hpp"

void dynamic::updateStopTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("stop");

    if (auto v = dynUtils::getIntKey(obj, 580); v && *v == 1) tex = texture::sprite("stop_pause");

    else if (auto v = dynUtils::getIntKey(obj, 580); v && *v == 2) tex = texture::sprite("stop_resume");
    
    texture::setObjIcon(obj, tex);
}

void dynamic::updateRotateTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("rotate");

    if(obj->m_useMoveTarget) tex = texture::sprite("rotate_aim");

    if (auto v = dynUtils::getIntKey(obj, 394); v && *v == 1) {
        tex = texture::sprite("rotate_follow");
    }

    
    texture::setObjIcon(obj, tex);
}

void dynamic::updateMoveTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("move");

    if(obj->m_useMoveTarget) tex = texture::sprite("move_target");

    else if(obj->m_lockToPlayerX || obj->m_lockToPlayerY || obj->m_lockToCameraX || obj->m_lockToCameraY) 
        tex = texture::sprite("move_lock");

    if (auto v = dynUtils::getIntKey(obj, 394); v && *v == 1) {
        tex = texture::sprite("move_direction");
    }
    
    texture::setObjIcon(obj, tex);
}

void dynamic::updateColisTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("collision");

    if(obj->m_triggerOnExit) tex = texture::sprite("collision_exit");

    texture::setObjIcon(obj, tex);
}

void dynamic::updateSpawnTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("spawn");

    auto remap = dynUtils::getIntKey(obj, 442);
    
    if (remap > 0) {
        tex = texture::sprite("spawn_remap");
    }

    texture::setObjIcon(obj, tex);
}

void dynamic::updateGravityTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("gravity");

    if(obj->m_gravityValue > 1.0f) tex = texture::sprite("gravity_high");

    texture::setObjIcon(obj, tex);
}

namespace cache {
    CacheSig sigStopTexture(EffectGameObject* obj, const Settings&) {
        int variant = 0;

        if (auto v = dynUtils::getIntKey(obj, 580); v && *v == 1) variant = 1;
        else if (auto v = dynUtils::getIntKey(obj, 580); v && *v == 2) variant = 2;
        
        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigMove(EffectGameObject* obj, const Settings&) {
        int variant = 0;
        if (obj->m_useMoveTarget) variant = 1;
        else if (obj->m_lockToPlayerX || obj->m_lockToPlayerY || obj->m_lockToCameraX || obj->m_lockToCameraY) variant = 2;
        if (auto v = dynUtils::getIntKey(obj, 394); v && *v == 1) variant = 3;

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigRotate(EffectGameObject* obj, const Settings&) {
        int variant = 0;
        if (obj->m_useMoveTarget) variant = 1;
        if (auto v = dynUtils::getIntKey(obj, 394); v && *v == 1) variant = 2;

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigColis(EffectGameObject* obj, const Settings&) {
        int variant = 0;
        if (obj->m_triggerOnExit) variant = 1;

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigSpawn(EffectGameObject* obj, const Settings&) {
        int variant = 0;
        auto remap = dynUtils::getIntKey(obj, 442);
        if (remap > 0) {
            variant = 1;
        }

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigGravity(EffectGameObject* obj, const Settings&) {
        auto count = typeinfo_cast<EffectGameObject*>(obj);
        if (!count) return {};

        CacheSig sig {obj->m_objectID};

        int variant = 0;
        if (count->m_gravityValue > 1.0f) variant = 1;
        sig.add(variant);

        return sig;
    }
}
