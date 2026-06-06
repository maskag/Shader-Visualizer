#include "../dynamic.hpp"
#include "../cache.hpp"
#include "../label.hpp"
#include <Geode/binding/EventLinkTrigger.hpp>
#include <Geode/binding/SFXTriggerGameObject.hpp>
#include <Geode/binding/StartPosObject.hpp>
#include <Geode/binding/UISettingsGameObject.hpp>
#include <vector>


void dynamic::updateSongTexture(SongTriggerGameObject* obj) {
    if (!obj) return;
    
    if (!TLabel::setValue(obj, obj->m_songChannel, TLabel::Variant::Standard)) {
        return;
    }
}

void dynamic::updateTimeTexture(EffectGameObject* obj) {
    if (!obj) return;

    if (!TLabel::setValue(obj, obj->m_itemID, TLabel::Variant::Standard)) {
        return;
    }
}

void dynamic::updateSFXTexture(SFXTriggerGameObject* obj) {
    if (!obj) return;
    float vol = obj->m_volume;
    
    static auto getSfxVal = [](const char* key) { return Mod::get()->getSettingValue<float>(key); };
    
    auto tex = texture::sprite("sfx_0");
    if (vol > getSfxVal("sfx5")) tex = texture::sprite("sfx_4");
    else if (vol > getSfxVal("sfx4")) tex = texture::sprite("sfx_3");
    else if (vol > getSfxVal("sfx3")) tex = texture::sprite("sfx_2");
    else if (vol > getSfxVal("sfx2")) tex = texture::sprite("sfx_1");
    
    texture::setObjIcon(obj, tex);
}

void dynamic::updateStartTexture(StartPosObject* obj) {
    if (!obj) {
        return;
    }
    
    auto settings = obj->m_startSettings;
    if (!settings) {
        return;
    }

    auto sprMain = texture::createSprite("start_titles");
    if (!sprMain) {
        return;
    }

    float gap = 12.f; 

    auto modeTex = "start_cube";
    switch (settings->m_startMode) {
        case 0: modeTex = "start_cube"; break;
        case 1: modeTex = "start_ship"; break;
        case 2: modeTex = "start_ball"; break;
        case 3: modeTex = "start_ufo"; break;
        case 4: modeTex = "start_wave"; break;
        case 5: modeTex = "start_robot"; break;
        case 6: modeTex = "start_spider"; break;
        case 7: modeTex = "start_swing"; break;
    }
    auto sprMode = texture::createSprite(modeTex);
    if (!sprMode) {
        return;
    }
    if (settings->m_startMini) {
        sprMode->setScale(0.75f);
    }

    auto speedTex = "start_speed1";
    int speedVal = static_cast<int>(settings->m_startSpeed);
    switch (speedVal) {
        case 1: speedTex = "start_speed0"; break; 
        case 0: speedTex = "start_speed1"; break; 
        case 2: speedTex = "start_speed2"; break; 
        case 3: speedTex = "start_speed3"; break; 
        case 4: speedTex = "start_speed4"; break; 
    }
    auto sprSpeed = texture::createSprite(speedTex);
    if (!sprSpeed) {
        return;
    }

    auto sprRot = texture::createSprite("start_path");
    if (sprRot) {
        if (settings->m_reverseGameplay) sprRot->setFlipX(true);
        sprRot->setFlipY(!settings->m_isFlipped);
    }
    if (!sprRot) {
        return;
    }
    
    float w = 50.f, h = 30.f;
    float cx = w / 2;
    float cy = h / 2; 

    float mainY = cy;
    
    float subY = cy + 3; 

    float subGap = (gap > 0.f) ? gap : 15.f;

    sprMain->setPosition({cx, mainY}); 
    sprMain->setFlipY(true); 

    if (sprMode) {
        sprMode->setPosition({cx - subGap, subY});
        sprMode->setFlipY(true);
    }

    if (sprSpeed) {
        sprSpeed->setPosition({cx, subY});
        sprSpeed->setFlipY(true);
    }

    if (sprRot) {
        sprRot->setPosition({cx + subGap, subY});
    }

    auto rt = CCRenderTexture::create(w, h);
    if (!rt) {
        return;
    }
    rt->beginWithClear(0, 0, 0, 0);
    
    sprMain->visit();
    if (sprMode) sprMode->visit();
    if (sprSpeed) sprSpeed->visit();
    if (sprRot) sprRot->visit();
    
    rt->end();

    if (auto tex = rt->getSprite()->getTexture()) {
        ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
        tex->setTexParameters(&tp);
        
        obj->m_addToNodeContainer = true;
        obj->setTexture(tex);
        obj->setTextureRect({0, 0, w, h});
    }
    else {
    }
}

void dynamic::updateUiTexture(UISettingsGameObject* obj) {
    if (!obj) {
        return;
    }

    if (!TLabel::setValue(obj, obj->m_targetGroupID, TLabel::Variant::Badge)) {
        return;
    }
    
    auto sprUiel = texture::createSprite("ui_element");
    auto sprTitle = texture::createSprite("ui_titles");
    if (!sprUiel || !sprTitle) {
        return;
    }

    float w = 25.f, h = 35.f;
    float cx = w/2, cy = h/2;
    float uielX = cx, uielY = cy;

    if (obj->m_xRef == 3) uielX -= 3.f;
    else if (obj->m_xRef == 4) uielX += 3.f;
    
    if (obj->m_yRef == 7) uielY += 3.f;
    else if (obj->m_yRef == 8) uielY -= 3.f;

    sprTitle->setPosition({cx, cy});
    sprUiel->setPosition({uielX, uielY});
    sprTitle->setFlipY(true);
    sprUiel->setFlipY(true);

    auto rt = CCRenderTexture::create(w, h);
    if (!rt) {
        return;
    }
    rt->beginWithClear(0,0,0,0);
    sprTitle->visit();
    sprUiel->visit();

    if (obj->m_xRelative) {
        if (auto s = texture::createSprite("ui_xRel")) {
            s->setPosition({cx, cy}); s->setFlipY(true); s->visit();
        }
    }
    if (obj->m_yRelative) {
        if (auto s = texture::createSprite("ui_yRel")) {
            s->setPosition({cx, cy}); s->setFlipY(true); s->visit();
        }
    }
    rt->end();

    if (auto tex = rt->getSprite()->getTexture()) {
        ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
        tex->setTexParameters(&tp);
        obj->m_addToNodeContainer = true;
        obj->setTexture(tex);
        obj->setTextureRect({0, 0, w, h});
    }
    else {
    }
}

void dynamic::updateEventTexture(EventLinkTrigger* obj, float gap) {
    if (!obj) {
        return;
    }

    if (!TLabel::setValue(obj, obj->m_targetGroupID, TLabel::Variant::Badge)) {
        return;
    }

    const auto& eids = obj->m_eventIDs;
    std::vector<std::string> singleTex, combinedTex;

    auto add = [&](std::string const& s, std::string const& c) {
        bool found = false;
        for (auto const& value : singleTex) {
            if (value == s) {
                found = true;
                break;
            }
        }
        if (!found) {
            singleTex.push_back(s);
            combinedTex.push_back(c);
        }
    };

    if (eids.empty()) {
        add(texture::sprite("event"), texture::sprite("event_other"));
    } else {
        for (int id : eids) {
            if (id >= 1 && id <= 5) add(texture::sprite("event_land"), texture::sprite("event_land2"));
            else if (id == 6) add(texture::sprite("event_hit"), texture::sprite("event_hit2"));
            else if ((id >= 7 && id <= 8) || (id >= 34 && id <= 44)) add(texture::sprite("event_orb"), texture::sprite("event_orb2"));
            else if (id == 9 || (id >= 45 && id <= 49)) add(texture::sprite("event_pad"), texture::sprite("event_pad2"));
            else if ((id >= 10 && id <= 11) || (id >= 50 && id <= 52)) add(texture::sprite("event_gravity"), texture::sprite("event_gravity2"));
            else if (id >= 12 && id <= 22) add(texture::sprite("event_jump"), texture::sprite("event_jump2"));
            else if (id == 62 || id == 63) add(texture::sprite("event_coin"), texture::sprite("event_coin2"));
            else if (id >= 65 && id <= 68) add(texture::sprite("event_fall"), texture::sprite("event_fall2"));
            else if (id == 69) add(texture::sprite("event_upRelease"), texture::sprite("event_upRelease2"));
            else if (id == 70) add(texture::sprite("event_up"), texture::sprite("event_up2"));
            else if (id == 71) add(texture::sprite("event_left"), texture::sprite("event_left2"));
            else if (id == 72) add(texture::sprite("event_leftRelease"), texture::sprite("event_leftRelease2"));
            else if (id == 73) add(texture::sprite("event_right"), texture::sprite("event_right2"));
            else if (id == 74) add(texture::sprite("event_rightRelease"), texture::sprite("event_rightRelease2"));
            else if (id == 75) add(texture::sprite("event_reverse"), texture::sprite("event_reverse2"));
            else if (id == 60 || id == 64) add(texture::sprite("event_checkpoint"), texture::sprite("event_checkpoint2"));
            else if ((id >= 26 && id <= 33) || (id >= 50 && id <= 59)) add(texture::sprite("event_portal"), texture::sprite("event_portal2"));
            else add(texture::sprite("event"), texture::sprite("event_other"));
        }
    }

    if (singleTex.size() == 1) {
        texture::setObjIcon(obj, singleTex[0]);
        return;
    }

    auto spr1 = CCSprite::create(combinedTex[0].c_str());
    auto spr2 = CCSprite::create(combinedTex[1].c_str());
    auto sprText = texture::createSprite("event_titles");
    auto sprBase = CCSprite::create(singleTex[0].c_str());
    if (!spr1 || !spr2 || !sprText || !sprBase) {
        return;
    }

    auto baseSize = sprBase->getTextureRect().size;
    float w = baseSize.width;
    float h = baseSize.height;
    if (w <= 0.f || h <= 0.f) {
        return;
    }

    float cx = w/2, cy = h/2;
    spr1->setFlipY(true); spr2->setFlipY(true); sprText->setFlipY(true);
    spr1->setPosition({cx - gap, cy});
    spr2->setPosition({cx + gap, cy});
    sprText->setPosition({cx, cy});

    auto rt = CCRenderTexture::create(w, h);
    if (!rt) {
        return;
    }
    rt->beginWithClear(0,0,0,0);
    spr1->visit(); spr2->visit(); sprText->visit();
    rt->end();

    if (auto tex = rt->getSprite()->getTexture()) {

        ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
        tex->setTexParameters(&tp);
        obj->m_addToNodeContainer = true;
        obj->setTexture(tex);
        obj->setTextureRect({0, 0, w, h});
    }
    else {
    }
}

namespace cache {
    CacheSig sigSong(EffectGameObject* obj, const Settings&) {
        auto song = typeinfo_cast<SongTriggerGameObject*>(obj);
        if (!song) return {};

        CacheSig sig {obj->m_objectID};

        if (TLabel::getValue(song) != song->m_songChannel) {
            sig.add(song->m_songChannel);
        }

        return sig;
    }

    CacheSig sigTime(EffectGameObject* obj, const Settings&) {
        if (!obj) return {};

        CacheSig sig {obj->m_objectID};

        if (TLabel::getValue(obj) != obj->m_itemID) {
            sig.add(obj->m_itemID);
        }

        return sig;
    }

    CacheSig sigEvent(EffectGameObject* obj, const Settings& s) {
        auto ev = typeinfo_cast<EventLinkTrigger*>(obj);
        if (!ev) return {};
        CacheSig sig {obj->m_objectID, ev->m_eventIDs.size()};
        for (int id : ev->m_eventIDs) {
            sig.add(id);
        }

        if (TLabel::getValue(ev) != ev->m_targetGroupID) {
            sig.add(ev->m_targetGroupID);
        }
        sig.add(s.offEv);
        return sig;
    }

    CacheSig sigSfx(EffectGameObject* obj, const Settings&) {
        auto sfx = typeinfo_cast<SFXTriggerGameObject*>(obj);
        if (!sfx) return {};
        float vol = sfx->m_volume;

        float sfx5 = Mod::get()->getSettingValue<float>("sfx5");
        float sfx4 = Mod::get()->getSettingValue<float>("sfx4");
        float sfx3 = Mod::get()->getSettingValue<float>("sfx3");
        float sfx2 = Mod::get()->getSettingValue<float>("sfx2");

        int bucket = 1;
        if (vol > sfx5) bucket = 5;
        else if (vol > sfx4) bucket = 4;
        else if (vol > sfx3) bucket = 3;
        else if (vol > sfx2) bucket = 2;

        return {obj->m_objectID, bucket};
    }

    CacheSig sigUi(EffectGameObject* obj, const Settings&) {
        auto ui = typeinfo_cast<UISettingsGameObject*>(obj);
        if (!ui) return {};

        CacheSig sig 
        {
            obj->m_objectID,
            ui->m_xRef,
            ui->m_yRef,
            ui->m_xRelative ? 1 : 0,
            ui->m_yRelative ? 1 : 0,
        };

        if (TLabel::getValue(ui) != ui->m_targetGroupID) {
            sig.add(ui->m_targetGroupID);
        }

        return sig;
    }

    CacheSig sigStart(EffectGameObject* obj, const Settings&) {
        auto start = typeinfo_cast<StartPosObject*>(obj);
        if (!start || !start->m_startSettings) return {};
        auto settings = start->m_startSettings;
        return {
            obj->m_objectID,
            settings->m_startMode,
            static_cast<int>(settings->m_startSpeed),
            settings->m_startMini ? 1 : 0,
            settings->m_reverseGameplay ? 1 : 0,
            settings->m_isFlipped ? 1 : 0,
        };
    }
}
