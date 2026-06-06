#include "../dynamic.hpp"
#include "../cache.hpp"
#include "../label.hpp"
#include <Geode/binding/EnterEffectObject.hpp>

void dynamic::updateAreaTexture(EnterEffectObject* obj) {
    if (!obj) return;

    if (!TLabel::setValue(obj, obj->m_targetGroupID, TLabel::Variant::Standard)) {
        return;
    }

    auto baseTex = dynUtils::getAreaTriggerBaseTexture(obj->m_objectID);
    auto sprBase = CCSprite::create(baseTex.c_str());
    auto sprEmp = texture::createSprite("area_type1");

    switch (dynUtils::getAreaBucket(obj)) {
        case 2: sprEmp = texture::createSprite("area_type2"); break;
        case 3: sprEmp = texture::createSprite("area_type3"); break;
        case 4: sprEmp = texture::createSprite("area_type4"); break;
        case 5: sprEmp = texture::createSprite("area_type5"); break;
        case 6: sprEmp = texture::createSprite("area_type6"); break;
        case 7: sprEmp = texture::createSprite("area_type7"); break;
        case 8: sprEmp = texture::createSprite("area_type8"); break;
        case 9: sprEmp = texture::createSprite("area_type9"); break;
        case 10: sprEmp = texture::createSprite("area_type10"); break;
        default: sprEmp = texture::createSprite("area_type1"); break;
    }

    if (!sprBase || !sprEmp) {
        texture::setObjIcon(obj, baseTex);
        return;
    }

    auto baseSize = sprBase->getContentSize();
    auto empSize = sprEmp->getContentSize();
    float w = baseSize.width > empSize.width ? baseSize.width : empSize.width;
    float h = baseSize.height > empSize.height ? baseSize.height : empSize.height;
    constexpr float kPad = 4.f;
    w += kPad * 2.f;
    h += kPad * 2.f;

    if (w <= 0.f || h <= 0.f) {
        texture::setObjIcon(obj, baseTex);
        return;
    }

    auto center = CCPoint{w / 2.f, h / 2.f};

    sprBase->setPosition(center);
    sprEmp->setPosition(center);

    sprBase->setFlipY(true);
    sprEmp->setFlipY(true);

    auto rt = CCRenderTexture::create(w, h);
    if (!rt) return;

    rt->beginWithClear(0, 0, 0, 0);
    sprBase->visit();
    sprEmp->visit();
    rt->end();

    if (auto tex = rt->getSprite()->getTexture()) {
        ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
        tex->setTexParameters(&tp);
        obj->m_addToNodeContainer = true;
        obj->setTexture(tex);
        obj->setTextureRect({0, 0, w, h});
    } else {
        texture::setObjIcon(obj, baseTex);
    }
}

namespace cache {
    CacheSig sigArea(EffectGameObject* obj, const Settings&) {
        auto area = typeinfo_cast<EnterEffectObject*>(obj);
        if (!area) return {};

        CacheSig sig {obj->m_objectID};

        if (TLabel::getValue(area) != area->m_targetGroupID) {
            sig.add(area->m_targetGroupID);
        }

        sig.add(dynUtils::getAreaBucket(obj));
        return sig;
    }
}
