#include "../dynamic.hpp"
#include "../cache.hpp"
#include <Geode/binding/CountTriggerGameObject.hpp>
#include <Geode/binding/ItemTriggerGameObject.hpp>

void dynamic::updatePickupTexture(CountTriggerGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("pickup");

    if(obj->m_isOverride) tex = texture::sprite("pickup_set");

    else if(obj->m_pickupTriggerMode == 1) tex = texture::sprite("pickup_mul");

    else if(obj->m_pickupTriggerMode == 2) tex = texture::sprite("pickup_div");
    
    else if(obj->m_pickupCount < 0) tex = texture::sprite("pickup_sub");

    else if(obj->m_pickupCount > 0) tex = texture::sprite("pickup_add");

    texture::setObjIcon(obj, tex);
}

void dynamic::updateCountTexture(CountTriggerGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("insCount");

    if(obj->m_pickupTriggerMode == 1) tex = texture::sprite("insCount_gt");

    else if(obj->m_pickupTriggerMode == 2) tex = texture::sprite("insCount_lt");
    
    else tex = texture::sprite("insCount_eq");

    texture::setObjIcon(obj, tex);
}

void dynamic::updateCompTexture(ItemTriggerGameObject* obj) {
    if (!obj) return;
    auto tex = texture::sprite("comp");
    switch (obj->m_resultType3) {
        case 5: tex = texture::sprite("comp_neq"); break;
        case 4: tex = texture::sprite("comp_lte"); break;
        case 3: tex = texture::sprite("comp_lt"); break;
        case 2: tex = texture::sprite("comp_gte"); break;
        case 1: tex = texture::sprite("comp_gt"); break;
        case 0: tex = texture::sprite("comp_eq"); break;
    }
    texture::setObjIcon(obj, tex);
}

void dynamic::updateEditTexture(ItemTriggerGameObject* obj, bool) {
    if (!obj) return;
    auto tex = texture::sprite("edit");
    switch (obj->m_resultType1) {
        case 4: tex = texture::sprite("edit_div"); break;
        case 3: tex = texture::sprite("edit_mul"); break;
        case 2: tex = texture::sprite("edit_sub"); break;
        case 1: tex = texture::sprite("edit_add"); break;
        case 0: tex = texture::sprite("edit_set"); break;
    }
    texture::setObjIcon(obj, tex);
}

namespace cache {
    CacheSig sigPickup(EffectGameObject* obj, const Settings&) {
        auto count = typeinfo_cast<CountTriggerGameObject*>(obj);
        if (!count) return {};
        int variant = 0;
        if (count->m_isOverride) variant = 1;
        else if (count->m_pickupTriggerMode == 1) variant = 2;
        else if (count->m_pickupTriggerMode == 2) variant = 3;
        else if (count->m_pickupCount < 0) variant = 4;
        else if (count->m_pickupCount > 0) variant = 5;

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigCount(EffectGameObject* obj, const Settings&) {
        auto count = typeinfo_cast<CountTriggerGameObject*>(obj);
        if (!count) return {};
        int variant = 0;
        if (count->m_pickupTriggerMode == 1) variant = 1;
        else if (count->m_pickupTriggerMode == 2) variant = 2;

        return {obj->m_objectID, variant + 1};
    }

    CacheSig sigComp(EffectGameObject* obj, const Settings&) {
        auto item = typeinfo_cast<ItemTriggerGameObject*>(obj);
        if (!item) return {};
        return {obj->m_objectID, item->m_resultType3 + 1};
    }

    CacheSig sigEdit(EffectGameObject* obj, const Settings& s) {
        auto item = typeinfo_cast<ItemTriggerGameObject*>(obj);
        if (!item) return {};
        return {obj->m_objectID, item->m_resultType1 + 1, s.dotEdit ? 1 : 0};
    }
}
