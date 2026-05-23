#include "../dynamic.hpp"
#include "../cache.hpp"


void dynamic::updateColorTexture(EffectGameObject* obj) {
    if (!obj) return;
    auto color = dynUtils::getColorTriggerTint(obj);
    auto baseTex = dynUtils::getColorTriggerBaseTexture(obj->m_objectID);

    auto sprBase = CCSprite::create(baseTex.c_str());
    if (!sprBase) {
        texture::setObjIcon(obj, baseTex);
        return;
    }

    auto sprEmp = texture::createSprite("col_empty");
    if (!sprEmp) {
        texture::setObjIcon(obj, baseTex);
        return;
    }
    sprEmp->setColor(color);

    auto baseSize = sprBase->getContentSize();
    auto empSize = sprEmp->getContentSize();
    float w = baseSize.width > empSize.width ? baseSize.width : empSize.width;
    float h = baseSize.height > empSize.height ? baseSize.height : empSize.height;
    if (w <= 0.f || h <= 0.f) {
        texture::setObjIcon(obj, baseTex);
        return;
    }

    constexpr float kPad = 2.f;
    float rtW = w + kPad * 2.f;
    float rtH = h + kPad * 2.f;
    float cx = rtW * 0.5f;
    float cy = rtH * 0.5f;

    sprBase->setPosition({cx, cy});
    sprEmp->setPosition({cx, cy});
    sprBase->setFlipY(true);
    sprEmp->setFlipY(true);

    auto rt = CCRenderTexture::create(rtW, rtH);
    if (!rt) {
        texture::setObjIcon(obj, baseTex);
        return;
    }

    rt->beginWithClear(0, 0, 0, 0);
    sprBase->visit();
    sprEmp->visit();
    rt->end();

    if (auto tex = rt->getSprite()->getTexture()) {
        ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
        tex->setTexParameters(&tp);
        obj->m_addToNodeContainer = true;
        obj->setTexture(tex);
        obj->setTextureRect({kPad, kPad, w, h});
    } else {
        texture::setObjIcon(obj, baseTex);
    }
}

void dynamic::updatePulseTexture(EffectGameObject* obj) {
    if (!obj) return;

    auto sprPulse = texture::createSprite("pulse");
    auto sprRing = texture::createSprite("pulse_empty");
    if (!sprPulse || !sprRing) {
        texture::setObjIcon(obj, texture::sprite("pulse"));
        return;
    }

    auto pulseSize = sprPulse->getContentSize();
    auto ringSize = sprRing->getContentSize();
    float w = pulseSize.width > ringSize.width ? pulseSize.width : ringSize.width;
    float h = pulseSize.height > ringSize.height ? pulseSize.height : ringSize.height;
    if (w <= 0.f || h <= 0.f) {
        texture::setObjIcon(obj, texture::sprite("pulse"));
        return;
    }

    constexpr float kPad = 2.f;
    float rtW = w + kPad * 2.f;
    float rtH = h + kPad * 2.f;
    float cx = rtW * 0.5f;
    float cy = rtH * 0.5f;

    sprPulse->setPosition({cx, cy});
    sprRing->setPosition({cx, cy});
    sprPulse->setFlipY(true);
    sprRing->setFlipY(true);
    sprRing->setColor(obj->m_triggerTargetColor);

    auto rt = CCRenderTexture::create(rtW, rtH);
    if (!rt) {
        texture::setObjIcon(obj, texture::sprite("pulse"));
        return;
    }

    rt->beginWithClear(0, 0, 0, 0);
    sprPulse->visit();
    sprRing->visit();
    rt->end();

    if (auto tex = rt->getSprite()->getTexture()) {
        ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
        tex->setTexParameters(&tp);
        obj->m_addToNodeContainer = true;
        obj->setTexture(tex);
        obj->setTextureRect({kPad, kPad, w, h});
    } else {
        texture::setObjIcon(obj, texture::sprite("pulse"));
    }
}

namespace cache {
    CacheSig sigPulse(EffectGameObject* obj, const Settings&) {
        if (!obj) return {};
        return {
            obj->m_objectID,
            obj->m_triggerTargetColor.r,
            obj->m_triggerTargetColor.g,
            obj->m_triggerTargetColor.b,
        };
    }

    CacheSig sigColorTrigger(EffectGameObject* obj, const Settings&) {
        if (!obj) return {};
        auto color = dynUtils::getColorTriggerTint(obj);
        return {obj->m_objectID, color.r, color.g, color.b};
    }
}
