#include "Utils.hpp"
#include <Geode/binding/SFXTriggerGameObject.hpp>
#include <Geode/binding/ItemTriggerGameObject.hpp>
#include <Geode/binding/UISettingsGameObject.hpp>
#include <Geode/binding/EventLinkTrigger.hpp>
#include <Geode/binding/StartPosObject.hpp>
#include <Geode/binding/LevelSettingsObject.hpp>
#include <Geode/binding/CameraTriggerGameObject.hpp>

// Im too lazy to write comments 😔

bool TextureUtils::g_isToolboxInit = false;

CCSprite* createIconSprite(std::string const& name) {
    auto modPath = Mod::get()->expandSpriteName(name.c_str());
    if (auto spr = CCSprite::create(std::string(modPath).c_str())) return spr;
    if (auto spr = CCSprite::createWithSpriteFrameName(name.c_str())) return spr;
    if (auto spr = CCSprite::create(name.c_str())) return spr;
    return CCSprite::create();
}

void TextureUtils::setObjIcon(EffectGameObject* obj, const std::string& texture) {
    if (!obj) return;
    if (auto newSpr = CCSprite::create(texture.c_str())) {
        obj->m_addToNodeContainer = true;
        obj->setTexture(newSpr->getTexture());
        obj->setTextureRect(newSpr->getTextureRect());
    }
}

void TextureUtils::updateCompTexture(ItemTriggerGameObject* obj) {
    if (!obj) return;
    const char* tex = "comp.png"_spr;
    switch (obj->m_resultType3) {
        case 5: tex = "comp5.png"_spr; break;
        case 4: tex = "comp4.png"_spr; break;
        case 3: tex = "comp3.png"_spr; break;
        case 2: tex = "comp2.png"_spr; break;
        case 1: tex = "comp1.png"_spr; break;
        case 0: tex = "comp0.png"_spr; break;
    }
    setObjIcon(obj, tex);
}

void TextureUtils::updateEditTexture(ItemTriggerGameObject* obj, bool dot) {
    if (!obj) return;
    const char* tex = "edit.png"_spr;
    switch (obj->m_resultType1) {
        case 4: tex = "edit4.png"_spr; break;
        case 3: tex = dot ? "edit3d.png"_spr : "edit3a.png"_spr; break;
        case 2: tex = "edit2.png"_spr; break;
        case 1: tex = "edit1.png"_spr; break;
        case 0: tex = "edit0.png"_spr; break;
    }
    setObjIcon(obj, tex);
}

void TextureUtils::updateOffsetCamTexture(CameraTriggerGameObject* obj, bool color) {
    if (!obj) return;

    if (obj->m_positionXOffset != 0 && obj->m_positionYOffset != 0)
        return;

    const char* tex;

    if (color) {
        tex = "offset.png"_spr;

        if (obj->m_positionXOffset!= 0)
            tex = "offsetX.png"_spr;
        else if (obj->m_positionYOffset != 0)
            tex = "offsetY.png"_spr;
    }

    else {
        tex = "Coffset.png"_spr;

        if (obj->m_positionXOffset != 0)
            tex = "coffsetX.png"_spr;
        else if (obj->m_positionYOffset != 0)
            tex = "coffsetY.png"_spr;
    }

    setObjIcon(obj, tex);
}

void TextureUtils::updateRotateCamTexture (CameraTriggerGameObject* obj, bool color) {
    if (!obj) return;

    const char* tex;
    if (color) {
        if (obj->m_rotationDegrees >= 0.f)
            tex = "rotatecam.png"_spr;
        if (obj->m_rotationDegrees < 0.f)
            tex = "rotatecamR.png"_spr;
    }
    else {
        if (obj->m_rotationDegrees >= 0.f)
            tex = "crotate.png"_spr;
        if (obj->m_rotationDegrees < 0.f)
            tex = "crotateR.png"_spr;
    }
    setObjIcon(obj, tex);
}

void TextureUtils::updateEdgeCamTexture (CameraTriggerGameObject* obj) {
    if (!obj) return;
    const char* tex = "edge.png"_spr;
    switch (obj->m_edgeDirection) {
        case 4: tex = "edgeD.png"_spr; break;
        case 3: tex = "edgeT.png"_spr; break;
        case 2: tex = "edge.png"_spr; break;
        case 1: tex = "edgeL.png"_spr; break;
    }
    setObjIcon(obj, tex);
}    

void TextureUtils::updateSFXTexture(SFXTriggerGameObject* obj) {
    if (!obj) return;
    float vol = obj->m_volume;
    
    static auto getSfxVal = [](const char* key) { return Mod::get()->getSettingValue<float>(key); };
    
    const char* tex = "sfx1.png"_spr;
    if (vol > getSfxVal("sfx5")) tex = "sfx5.png"_spr;
    else if (vol > getSfxVal("sfx4")) tex = "sfx4.png"_spr;
    else if (vol > getSfxVal("sfx3")) tex = "sfx3.png"_spr;
    else if (vol > getSfxVal("sfx2")) tex = "sfx2.png"_spr;
    
    setObjIcon(obj, tex);
}

void TextureUtils::updateStartTexture(StartPosObject* obj) {
    if (!obj) return;
    
    auto settings = obj->m_startSettings;
    if (!settings) return;

    auto sprMain = CCSprite::create("start_title.png"_spr);
    if (!sprMain) return;

    float gap = 12.f; 

    const char* modeTex = "start_cube.png"_spr;
    switch (settings->m_startMode) {
        case 0: modeTex = "start_cube.png"_spr; break;
        case 1: modeTex = "start_ship.png"_spr; break;
        case 2: modeTex = "start_ball.png"_spr; break;
        case 3: modeTex = "start_ufo.png"_spr; break;
        case 4: modeTex = "start_wave.png"_spr; break;
        case 5: modeTex = "start_robot.png"_spr; break;
        case 6: modeTex = "start_spider.png"_spr; break;
        case 7: modeTex = "start_swing.png"_spr; break;
    }
    auto sprMode = CCSprite::create(modeTex);
    if (sprMode && settings->m_startMini) {
        sprMode->setScale(0.75f);
    }

    const char* speedTex = "start_s1.png"_spr;
    int speedVal = static_cast<int>(settings->m_startSpeed);
    switch (speedVal) {
        case 1: speedTex = "start_s0.png"_spr; break; 
        case 0: speedTex = "start_s1.png"_spr; break; 
        case 2: speedTex = "start_s2.png"_spr; break; 
        case 3: speedTex = "start_s3.png"_spr; break; 
        case 4: speedTex = "start_s4.png"_spr; break; 
    }
    auto sprSpeed = CCSprite::create(speedTex);

    auto sprRot = CCSprite::create("start_path.png"_spr); 
    if (sprRot) {
        if (settings->m_reverseGameplay) sprRot->setFlipX(true);
        sprRot->setFlipY(!settings->m_isFlipped);
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
}

void TextureUtils::updateUiTexture(UISettingsGameObject* obj) {
    if (!obj) return;
    
    auto sprUiel = CCSprite::create("uiel.png"_spr);
    auto sprTitle = CCSprite::create("uititle.png"_spr);
    if (!sprUiel || !sprTitle) return;

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
    rt->beginWithClear(0,0,0,0);
    sprTitle->visit();
    sprUiel->visit();

    if (obj->m_xRelative) {
        if (auto s = CCSprite::create("uix.png"_spr)) {
            s->setPosition({cx, cy}); s->setFlipY(true); s->visit();
        }
    }
    if (obj->m_yRelative) {
        if (auto s = CCSprite::create("uiy.png"_spr)) {
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
}

void TextureUtils::updateEventTexture(EventLinkTrigger* obj, float gap) {
    if (!obj) return;
    const auto& eids = obj->m_eventIDs;
    std::vector<const char*> singleTex, combinedTex;

    auto add = [&](const char* s, const char* c) {
        bool found = false;
        for(auto ptr : singleTex) if(ptr == s) { found = true; break; }
        if (!found) {
            singleTex.push_back(s);
            combinedTex.push_back(c);
        }
    };

    if (eids.empty()) {
        add("ev.png"_spr, "evs.png"_spr);
    } else {
        for (int id : eids) {
            if (id >= 1 && id <= 5) add("evland.png"_spr, "evlands.png"_spr);
            else if (id == 6) add("evhit.png"_spr, "evhits.png"_spr);
            else if ((id >= 7 && id <= 8) || (id >= 34 && id <= 44)) add("evorb.png"_spr, "evorbs.png"_spr);
            else if (id == 9 || (id >= 45 && id <= 49)) add("evpad.png"_spr, "evpads.png"_spr);
            else if ((id >= 10 && id <= 11) || (id >= 50 && id <= 52)) add("evgravity.png"_spr, "evgravitys.png"_spr);
            else if (id >= 12 && id <= 22) add("evjump.png"_spr, "evjumps.png"_spr);
            else if (id == 62 || id == 63) add("evcoin.png"_spr, "evcoins.png"_spr);
            else if (id >= 65 && id <= 68) add("evfall.png"_spr, "evfalls.png"_spr);
            else if (id == 69) add("evtop.png"_spr, "evtops.png"_spr);
            else if (id == 70) add("evup.png"_spr, "evups.png"_spr);
            else if (id == 71) add("evleft.png"_spr, "evlefts.png"_spr);
            else if (id == 72) add("evlef.png"_spr, "evlefs.png"_spr);
            else if (id == 73) add("evright.png"_spr, "evrights.png"_spr);
            else if (id == 74) add("evrig.png"_spr, "evrigs.png"_spr);
            else if (id == 75) add("evreverse.png"_spr, "evreverses.png"_spr);
            else if (id == 60 || id == 64) add("evsave.png"_spr, "evsaves.png"_spr);
            else if ((id >= 26 && id <= 33) || (id >= 50 && id <= 59)) add("evportal.png"_spr, "evportals.png"_spr);
            else add("ev.png"_spr, "evs.png"_spr);
        }
    }

    if (singleTex.size() == 1) {
        setObjIcon(obj, singleTex[0]);
        return;
    }

    auto spr1 = CCSprite::create(combinedTex[0]);
    auto spr2 = CCSprite::create(combinedTex[1]);
    auto sprText = CCSprite::create("evtitles.png"_spr);
    if (!spr1 || !spr2 || !sprText) return;

    float w = 100.f, h = 50.f;
    float cx = w/2, cy = h/2;
    spr1->setFlipY(true); spr2->setFlipY(true); sprText->setFlipY(true);
    spr1->setPosition({cx - gap, cy});
    spr2->setPosition({cx + gap, cy});
    sprText->setPosition({cx, cy});

    auto rt = CCRenderTexture::create(w, h);
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
}

void TextureUtils::applyDynamicUpdates(EffectGameObject* obj, const DynamicSettings& s) {
    int id = obj->m_objectID;

    if (id == 3604 && s.ev) {
         updateEventTexture(typeinfo_cast<EventLinkTrigger*>(obj), s.offEv);
    }
    else if (id == 3602 && s.sfx) {
         updateSFXTexture(typeinfo_cast<SFXTriggerGameObject*>(obj));
    }
    else if (id == 3620 && s.comp) {
         updateCompTexture(typeinfo_cast<ItemTriggerGameObject*>(obj));
    }
    else if (id == 3619 && s.comp) {
         updateEditTexture(typeinfo_cast<ItemTriggerGameObject*>(obj), s.dotEdit);
    }
    else if (id == 3613 && s.ui) {
         updateUiTexture(typeinfo_cast<UISettingsGameObject*>(obj));
    }
    else if (id == 31 && s.start) {
         updateStartTexture(typeinfo_cast<StartPosObject*>(obj));
    }
    else if (s.cam) {
         switch(id) {
            case 1916: 
                updateOffsetCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj), s.color); 
                break;
            case 2015: 
                updateRotateCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj), s.color); 
                break;
            case 2062: 
                updateEdgeCamTexture(typeinfo_cast<CameraTriggerGameObject*>(obj)); 
                break;
         }
    }
}

void TextureUtils::applyDynamicChangesGlobal() {
    auto lel = LevelEditorLayer::get();
    if (!lel || !lel->m_objects) return;
    
    bool isDynamic = Mod::get()->getSavedValue<bool>("dynamic", false);
    if (!isDynamic) return;

    DynamicSettings settings;
    settings.ev = getSwitchValue("dyn-ev");
    settings.sfx = getSwitchValue("dyn-sfx");
    settings.comp = getSwitchValue("dyn-comp");
    settings.ui = getSwitchValue("dyn-ui");
    settings.start = getSwitchValue("dyn-start");
    settings.dotEdit = getSwitchValue("dot-edit");
    settings.cam = getSwitchValue("dyn-cam");
    settings.color = getSwitchValue("color-cam");
    settings.offEv = Mod::get()->getSettingValue<float>("off-ev");

    if (!settings.ev && !settings.sfx && !settings.comp && !settings.ui) return;

    Ref<CCArray> arr = lel->m_objects;
    for (auto obj : CCArrayExt<EffectGameObject*>(arr)) {
         if (obj) applyDynamicUpdates(obj, settings);
    }
}

const std::unordered_map<int, std::pair<std::string, std::string>> TextureUtils::iconMap = {
    // SHADER
    {2904, {"shader.png"_spr, "do-shader"}}, {2905, {"shock.png"_spr, "do-shader"}},
    {2907, {"line.png"_spr, "do-shader"}}, {2909, {"glitch.png"_spr, "do-shader"}},
    {2910, {"chromatic.png"_spr, "do-shader"}}, {2911, {"chrglitch.png"_spr, "do-shader"}},
    {2912, {"pixelate.png"_spr, "do-shader"}}, {2913, {"circles.png"_spr, "do-shader"}},
    {2914, {"radial.png"_spr, "do-shader"}}, {2915, {"motion.png"_spr, "do-shader"}},
    {2916, {"bulge.png"_spr, "do-shader"}}, {2917, {"pinch.png"_spr, "do-shader"}},
    {2919, {"blind.png"_spr, "do-shader"}}, {2920, {"sepia.png"_spr, "do-shader"}},
    {2921, {"negative.png"_spr, "do-shader"}}, {2922, {"hue.png"_spr, "do-shader"}},
    {2923, {"color.png"_spr, "do-shader"}}, {2924, {"screen.png"_spr, "do-shader"}},
    
    // DEFAULT
    {901, {"move.png"_spr, "do-default"}}, {1006, {"pulse.png"_spr, "do-default"}},
    {1007, {"alpha.png"_spr, "do-default"}}, {1346, {"rotate.png"_spr, "do-default"}},
    {2067, {"scale.png"_spr, "do-default"}}, {1585, {"animate.png"_spr, "do-default"}},
    {3016, {"advfollow.png"_spr, "do-default"}}, {3660, {"editadv.png"_spr, "do-default"}},
    {3661, {"target.png"_spr, "do-default"}}, {1814, {"followy.png"_spr, "do-default"}},
    {1935, {"timewarp.png"_spr, "do-default"}}, {1932, {"control.png"_spr, "do-default"}},
    {2999, {"mg.png"_spr, "do-default"}}, {3606, {"bgs.png"_spr, "do-default"}},
    {3612, {"mgs.png"_spr, "do-default"}}, {3613, {"ui.png"_spr, "do-default"}},
    {2899, {"options.png"_spr, "do-default"}}, {3602, {"sfx.png"_spr, "do-default"}},
    {3603, {"esfx.png"_spr, "do-default"}}, {3600, {"end.png"_spr, "do-default"}},
    {2901, {"gpoff.png"_spr, "do-default"}}, {1917, {"reverse.png"_spr, "do-default"}},
    {1934, {"song.png"_spr, "do-default"}}, {3605, {"editsong.png"_spr, "do-default"}},
    {3029, {"bgc.png"_spr, "do-default"}}, {3030, {"gc.png"_spr, "do-default"}},
    {3031, {"mgc.png"_spr, "do-default"}}, {3604, {"ev.png"_spr, "do-default"}},

    // LOGIC
    {1616, {"stop.png"_spr, "do-logic"}}, {1817, {"pickup.png"_spr, "do-logic"}},
    {1268, {"spawn.png"_spr, "do-logic"}}, {1347, {"follow.png"_spr, "do-logic"}},
    {1912, {"random.png"_spr, "do-logic"}}, {2068, {"advrandom.png"_spr, "do-logic"}},
    {1611, {"count.png"_spr, "do-logic"}}, {1811, {"advcount.png"_spr, "do-logic"}},
    {1595, {"touch.png"_spr, "do-logic"}}, {3619, {"edit.png"_spr, "do-logic"}},
    {3620, {"comp.png"_spr, "do-logic"}}, {3641, {"pers.png"_spr, "do-logic"}},
    {1812, {"dead.png"_spr, "do-logic"}}, {1815, {"colis.png"_spr, "do-logic"}},
    {3609, {"advcolis.png"_spr, "do-logic"}},

    // AREA
    {3006, {"amove.png"_spr, "do-area"}}, {3007, {"arotate.png"_spr, "do-area"}},
    {3008, {"ascale.png"_spr, "do-area"}}, {3009, {"aalpha.png"_spr, "do-area"}},
    {3010, {"apulse.png"_spr, "do-area"}}, {3011, {"eamove.png"_spr, "do-area"}},
    {3012, {"earotate.png"_spr, "do-area"}}, {3013, {"eascale.png"_spr, "do-area"}},
    {3014, {"eaalpha.png"_spr, "do-area"}}, {3015, {"eapulse.png"_spr, "do-area"}},
    {3017, {"emove.png"_spr, "do-area"}}, {3018, {"erotate.png"_spr, "do-area"}},
    {3019, {"escale.png"_spr, "do-area"}}, {3020, {"ealpha.png"_spr, "do-area"}},
    {3021, {"epulse.png"_spr, "do-area"}},

    // COLIS
    {3640, {"colisin.png"_spr, "do-colis"}}, {1816, {"colisblock.png"_spr, "do-colis"}},
    {3643, {"colistouch.png"_spr, "do-colis"}}
};