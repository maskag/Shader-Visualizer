#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/general.hpp>
#include <Geode/binding/EffectGameObject.hpp>

using namespace geode::prelude;

namespace TLabel {
    enum class Variant {
        Standard,
        Badge
    };

    // Create a text on trigger
    CCLabelBMFont* create(EffectGameObject* obj, float scale, CCPoint position);
    // automatic scale and position
    CCLabelBMFont* create(EffectGameObject* obj);

    CCLabelBMFont* setValue(EffectGameObject* obj, int value, float scale, CCPoint position);

    CCPoint getPos(Variant var);

    float getScale(Variant var);

    float getMaxWidth(Variant var);

    CCLabelBMFont* setValue(EffectGameObject* obj, int value, Variant var);

    int getValue(EffectGameObject* obj);
}
