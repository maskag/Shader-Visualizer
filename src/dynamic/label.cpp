#include "label.hpp"

using namespace geode::prelude;

namespace TLabel {
    CCLabelBMFont* create(EffectGameObject* obj, float scale, CCPoint position) {
        if (!obj) {
            return nullptr;
        }

        if (obj->m_objectLabel) {
            obj->m_objectLabel->setScale(scale);
            obj->m_objectLabel->setAnchorPoint({0.5f, 0.5f});
            obj->m_objectLabel->setPosition(position);
            obj->m_objectLabel->setZOrder(1);
            return obj->m_objectLabel;
        }

        auto label = CCLabelBMFont::create("", "bigFont.fnt");
        if (!label) {
            return nullptr;
        }

        label->setScale(scale);
        label->setAnchorPoint({0.5f, 0.5f});
        label->setPosition(position);
        label->setZOrder(1);
        
        obj->addChild(label);
        obj->m_objectLabel = label;
        return label;
    }

    CCLabelBMFont* create(EffectGameObject* obj) {
        return create(obj, 0.35f, {0.f, 0.f});
    }

    CCLabelBMFont* setValue(EffectGameObject* obj, int value, float scale, CCPoint position) {
        auto label = create(obj, scale, position);
        if (!label) {
            return nullptr;
        }

        auto text = utils::numToString(value);
        label->setString(text.c_str());

        return label;
    }

    CCPoint getPos(Variant var) {
        if (var == Variant::Standard) {
            return {16.5f, 11.5f};
        }
        if (var == Variant::Badge) {
            return {4.f, 4.f};
        }
        if (var == Variant::ItemBadge) {
            return {7.f, 13.f};
        }
        return {16.5f, 11.5f};
    }

    float getScale(Variant var) {
        if (var == Variant::Standard) {
            return 0.5f;
        }
        if (var == Variant::Badge) {
            return 0.35f;
        }
        if (var == Variant::ItemBadge) {
            return 0.35f;
        }
        return 0.5f;
    }

    float getMaxWidth(Variant var) {
        if (var == Variant::Standard) {
            return 30.f;
        }
        if (var == Variant::Badge) {
            return 21.f;
        }
        if (var == Variant::ItemBadge) {
            return 21.f;
        }
        return 30.f;
    }

    CCLabelBMFont* setValue(EffectGameObject* obj, int value, Variant var) {
        auto scale = getScale(var);
        auto label = setValue(obj, value, scale, getPos(var));
        if (label) {
            label->limitLabelWidth(getMaxWidth(var), scale, scale * 0.6f);
        }
        return label;
    }

    int getValue(EffectGameObject* obj) {
        if (!obj || !obj->m_objectLabel) {
            return 0;
        }

        auto str = obj->m_objectLabel->getString();
        if (auto value = utils::numFromString<int>(str ? str : "0")) {
            return *value;
        }
        return 0;
    }
}
