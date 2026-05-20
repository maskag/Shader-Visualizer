#include "../dynamic.hpp"
#include "../cache.hpp"
#include "../label.hpp"
#include <Geode/binding/CameraTriggerGameObject.hpp>

namespace {
    bool hasOffset(std::optional<int> const& value) {
        return value.value_or(0) != 0;
    }
}

void dynamic::updateOffsetCamTexture(CameraTriggerGameObject* obj) {
    if (!obj) return;

    auto vX = dynUtils::getIntKey(obj, 28);
    auto vY = dynUtils::getIntKey(obj, 29);
    bool xOnly = hasOffset(vX);
    bool yOnly = hasOffset(vY);

    auto tex = texture::sprite("offsetCam");

    if (xOnly && !yOnly)
        tex = texture::sprite("OffsetCam_x");
    else if (yOnly && !xOnly)
        tex = texture::sprite("OffsetCam_y");

    texture::setObjIcon(obj, tex);
}

void dynamic::updateRotateCamTexture(CameraTriggerGameObject* obj) {
    if (!obj) return;
    
    auto tex = texture::sprite("RotateCam_left");

    if (obj->m_rotationDegrees >= 0.f)
        tex = texture::sprite("RotateCam_left");
    else
        tex = texture::sprite("RotateCam_right");

    texture::setObjIcon(obj, tex);
}

void dynamic::updateStaticCamTexture(CameraTriggerGameObject* obj) {
    if (!obj) return;

    if (!TLabel::setValue(obj, obj->m_centerGroupID, TLabel::Variant::Standard)) {
        return;
    }

    auto tex = texture::sprite("staticCam");

    if (auto v = dynUtils::getIntKey(obj, 212); v && *v == 1) {
        tex = texture::sprite("staticCam_follow");
    }

    texture::setObjIcon(obj, tex);
}    

void dynamic::updateEdgeCamTexture(CameraTriggerGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("edgeCam_right");
    switch (obj->m_edgeDirection) {
        case 4: tex = texture::sprite("edgeCam_down"); break;
        case 3: tex = texture::sprite("edgeCam_up"); break;
        case 2: tex = texture::sprite("edgeCam_right"); break;
        case 1: tex = texture::sprite("edgeCam_left"); break;
    }
    texture::setObjIcon(obj, tex);
}    

namespace cache {
    CacheSig sigOffsetCam(EffectGameObject* obj, const Settings&) {
        auto cam = typeinfo_cast<CameraTriggerGameObject*>(obj);
        if (!cam) return {};
        auto vX = dynUtils::getIntKey(cam, 28);
        auto vY = dynUtils::getIntKey(cam, 29);
        bool xOnly = hasOffset(vX);
        bool yOnly = hasOffset(vY);
        int variant = 0;
        if (xOnly && !yOnly) variant = 1;
        else if (yOnly && !xOnly) variant = 2;

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigRotateCam(EffectGameObject* obj, const Settings& s) {
        auto cam = typeinfo_cast<CameraTriggerGameObject*>(obj);
        if (!cam) return {};

        CacheSig sig {obj->m_objectID};

        int variant = cam->m_rotationDegrees < 0.f ? 1 : 0;
        sig.add(variant);
        return sig;
    }

    CacheSig sigStaticCam(EffectGameObject* obj, const Settings& s) {
        auto cam = typeinfo_cast<CameraTriggerGameObject*>(obj);
        if (!cam) return {};

        CacheSig sig {obj->m_objectID};

        if (TLabel::getValue(cam) != cam->m_centerGroupID) {
            sig.add(cam->m_centerGroupID);
        }

        int variant = 0;
        if (auto v = dynUtils::getIntKey(cam, 212); v && *v == 1) {
            variant = 2;
        }
        sig.add(variant);

        return sig;
    }

    CacheSig sigEdgeCam(EffectGameObject* obj, const Settings&) {
        auto cam = typeinfo_cast<CameraTriggerGameObject*>(obj);
        if (!cam) return {};
        return {obj->m_objectID, cam->m_edgeDirection + 1};
    }
}
