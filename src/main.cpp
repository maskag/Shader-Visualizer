#include <Geode/Geode.hpp>
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/CCSpriteBatchNode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/SetupSFXPopup.hpp>
#include <Geode/binding/SFXTriggerGameObject.hpp>
#include <Geode/binding/ToggleTriggerAction.hpp>
#include <Geode/modify/SetupEventLinkPopup.hpp>
#include <Geode/binding/EventLinkTrigger.hpp>
#include <Geode/modify/SetupTriggerPopup.hpp>
#include <Geode/loader/SettingV3.hpp>
using namespace geode::prelude;

class $modify(SetupTriggerPopup) {
    void onClose(cocos2d::CCObject* sender) {
        this->applyChangesToObjects();
        SetupTriggerPopup::onClose(sender);
    }

     void applyChangesToObjects() {

		auto ev = Mod::get()->getSettingValue<bool>("dyn-ev");

		if (!ev) return;

        auto lel = LevelEditorLayer::get();
        if (!lel) return;

        auto arr = lel->m_objects;
        if (!arr) return;

        for (int i = 0; i < arr->count(); i++) {
            auto obj = static_cast<EffectGameObject*>(arr->objectAtIndex(i));
            if (!obj || obj->m_objectID != 3604) continue;

            updateObjectTexture(typeinfo_cast<EventLinkTrigger*>(obj));
        }
    }

	static void updateObjectTexture(EventLinkTrigger* obj) {
		if (!obj) return;

		const auto& eids = obj->m_eventIDs;
		const char* texture = "ev.png"_spr; // дефолтная текстура

		for (int id : eids) {
			if (id >= 1 && id <= 5) {
				texture = "evland.png"_spr;
				break;
			} 
			else if (id == 6) {
				texture = "evhit.png"_spr;
				break;
			} 
			else if (id == 7 || id == 8) {
				texture = "evorb.png"_spr;
				break;
			} 
			else if (id == 9) {
				texture = "evpad.png"_spr;
				break;
			} 
			else if (id == 10 || id == 11) {
				texture = "evgravity.png"_spr;
				break;
			} 
			else if (id >= 12 && id <= 22) {
				texture = "evjump.png"_spr;
				break;
			} 
			else if (id >= 34 && id <= 44) {
				texture = "evorb.png"_spr;
				break;
			} 
			else if (id >= 45 && id <= 49) {
				texture = "evpad.png"_spr;
				break;
			} 
			else if (id >= 50 && id <= 52) {
				texture = "evgravity.png"_spr;
				break;
			} 
			else if (id == 62 || id == 63) {
				texture = "evcoin.png"_spr;
				break;
			} 
			else if (id >= 65 && id <= 68) {
				texture = "evfall.png"_spr;
				break;
			} 
			else if (id == 69 || id == 70) {
				texture = "evtop.png"_spr;
				break;
			} 
			else if (id == 71 || id == 72) {
				texture = "evleft.png"_spr;
				break;
			} 
			else if (id == 73 || id == 74) {
				texture = "evright.png"_spr;
				break;
			}
			else if (id == 60 || id == 64) {
				texture = "evsave.png"_spr;
				break;
			}
			else if (id >= 26 && id <= 33 || id >= 50 && id <= 59) {
				texture = "evportal.png"_spr;
				break;
			} 
		}

		
		if (!texture) return;

		if (auto spr = CCSprite::create(texture)) {
			obj->setTexture(spr->getTexture());
			obj->setTextureRect(spr->getTextureRect());
		}
	}
};

class $modify(SetupSFXPopup) {
    void onClose(cocos2d::CCObject* sender) {
        this->applyChangesToObjects();
        SetupSFXPopup::onClose(sender);
    }

     void applyChangesToObjects() {
		
		auto sfx = Mod::get()->getSettingValue<bool>("dyn-sfx");

		if (!sfx) return;

        auto lel = LevelEditorLayer::get();
        if (!lel) return;

        auto arr = lel->m_objects;
        if (!arr) return;

        for (int i = 0; i < arr->count(); i++) {
            auto obj = static_cast<EffectGameObject*>(arr->objectAtIndex(i));
            if (!obj || obj->m_objectID != 3602) continue;

            updateObjectTexture(typeinfo_cast<SFXTriggerGameObject*>(obj));
        }
    }

    static void updateObjectTexture(SFXTriggerGameObject* obj) {
        if (!obj) return;

        float volume = obj->m_volume;

        const char* texture = nullptr;

		auto sfx2 = Mod::get()->getSettingValue<float>("sfx2");
		auto sfx3 = Mod::get()->getSettingValue<float>("sfx3");
		auto sfx4 = Mod::get()->getSettingValue<float>("sfx4");
		auto sfx5 = Mod::get()->getSettingValue<float>("sfx5");

        if (volume > sfx5) texture = "sfx5.png"_spr;
        else if (volume > sfx4) texture = "sfx4.png"_spr;
        else if (volume > sfx3) texture = "sfx3.png"_spr;
		else if (volume > sfx2) texture = "sfx2.png"_spr;
        else texture = "sfx1.png"_spr;

        if (CCSprite* spr = CCSprite::create(texture)) {
            obj->setTexture(spr->getTexture());
            obj->setTextureRect(spr->getTextureRect());
        }
    }
};

class $modify(MyEffectGameObject, EffectGameObject) {
	void customSetup() {
		EffectGameObject::customSetup();

		auto defalt = Mod::get()->getSettingValue<bool>("do-default");
		auto logic = Mod::get()->getSettingValue<bool>("do-logic");
		auto shader = Mod::get()->getSettingValue<bool>("do-shader");
		auto area = Mod::get()->getSettingValue<bool>("do-area");
		auto ccolor = Mod::get()->getSettingValue<bool>("color-cam");
		auto cam = Mod::get()->getSettingValue<bool>("do-cam");
		
		if (shader == true)
		switch(m_objectID){

			case 2904: {
				setIcon("shader.png"_spr);
				break;
			}
			case 2905: {
				setIcon("shock.png"_spr);
				break;
			}
			case 2907: {
				setIcon("line.png"_spr);
				break;
			}
			case 2909: {
				setIcon("glitch.png"_spr);
				break;
			}
			case 2910: {
				setIcon("chromatic.png"_spr);
				break;
			}
			case 2911: {
				setIcon("chrglitch.png"_spr);
				break;
			}
			case 2912: {
				setIcon("pixelate.png"_spr);
				break;
			}
			case 2913: {
				setIcon("circles.png"_spr);
				break;
			}
			case 2914: {
				setIcon("radial.png"_spr);
				break;
			}
			case 2915: {
				setIcon("motion.png"_spr);
				break;
			}
			case 2916: {
				setIcon("bulge.png"_spr);
				break;
			}
			case 2917: {
				setIcon("pinch.png"_spr);
				break;
			}
			case 2919: {
				setIcon("blind.png"_spr);
				break;
			}
			case 2920: {
				setIcon("sepia.png"_spr);
				break;
			}
			case 2921: {
				setIcon("negative.png"_spr);
				break;
			}
			case 2922: {
				setIcon("hue.png"_spr);
				break;
			}
			case 2923: {
				setIcon("color.png"_spr);
				break;
			}
			case 2924: {
				setIcon("screen.png"_spr);
				break;
			}		
			
		}
		
		if (defalt == true)
		switch(m_objectID) {
			case 901: {
				setIcon("move.png"_spr);
				break;
			}
			case 1006: {
				setIcon("pulse.png"_spr);
				break;
			}
			case 1007: {
				setIcon("alpha.png"_spr);
				break;
			}
			case 1346: {
				setIcon("rotate.png"_spr);
				break;
			}
			case 2067: {
				setIcon("scale.png"_spr);
				break;
			}
			case 1585: {
				setIcon("animate.png"_spr);
				break;
			}
			case 3016: {
				setIcon("advfollow.png"_spr);
				break;
			}
			case 3660: {
				setIcon("editadv.png"_spr);
				break;
			}
			case 3661: {
				setIcon("target.png"_spr);
				break;
			}
			case 1814: {
				setIcon("followy.png"_spr);
				break;
			}
			case 1935: {
				setIcon("timewarp.png"_spr);
				break;
			}
			case 1932: {
				setIcon("control.png"_spr);
				break;
			}
			case 2999: {
				setIcon("mg.png"_spr);
				break;
			}
			case 3606: {
				setIcon("bgs.png"_spr);
				break;
			}
			case 3612: {
				setIcon("mgs.png"_spr);
				break;
			}
			case 3613: {
				setIcon("ui.png"_spr);
				break;
			}
			case 2899: {
				setIcon("options.png"_spr);
				break;
			}
			case 3602: {
				setIcon("sfx.png"_spr);
				break;
			}
			case 3603: {
				setIcon("esfx.png"_spr);
				break;
			}
			case 31: {
				setIcon("start.png"_spr);
				break;
			}
			case 3600: {
				setIcon("end.png"_spr);
				break;
			}
			case 2901: {
				setIcon("gpoff.png"_spr);
				break;
			}
			case 1917: {
				setIcon("reverse.png"_spr);
				break;
			}
		}
		
		if (logic == true)
		switch(m_objectID) {
			case 1616: {
				setIcon("stop.png"_spr);
				break;
			}
			case 1817: {
				setIcon("pickup.png"_spr);
				break;
			}
			case 1268: {
				setIcon("spawn.png"_spr);
				break;
			}
			case 1347: {
				setIcon("follow.png"_spr);
				break;
			}
			case 1912: {
				setIcon("random.png"_spr);
				break;
			}
			case 2068: {
				setIcon("advrandom.png"_spr);
				break;
			}
			case 1611: {
				setIcon("count.png"_spr);
				break;
			}
			case 1811: {
				setIcon("advcount.png"_spr);
				break;
			}
			case 1595: {
				setIcon("touch.png"_spr);
				break;
			}
			case 3619: {
				setIcon("edit.png"_spr);
				break;
			}
			case 3620: {
				setIcon("comp.png"_spr);
				break;
			}
			case 3641: {
				setIcon("pers.png"_spr);
				break;
			}
			case 1812: {
				setIcon("dead.png"_spr);
				break;
			}
			case 1815: {
				setIcon("colis.png"_spr);
				break;
			}
			case 3609: {
				setIcon("advcolis.png"_spr);
				break;
			}
			case 3604: {
				setIcon("ev.png"_spr);
				break;
			}
		}

		if (area == true)
		switch(m_objectID) {
			case 3006: {
				setIcon("amove.png"_spr);
				break;
			}
			case 3007: {
				setIcon("arotate.png"_spr);
				break;
			}
			case 3008: {
				setIcon("ascale.png"_spr);
				break;
			}
			case 3009: {
				setIcon("aalpha.png"_spr);
				break;
			}
			case 3010: {
				setIcon("apulse.png"_spr);
				break;
			}
			case 3011: {
				setIcon("eamove.png"_spr);
				break;
			}
			case 3012: {
				setIcon("earotate.png"_spr);
				break;
			}
			case 3013: {
				setIcon("eascale.png"_spr);
				break;
			}
			case 3014: {
				setIcon("eaalpha.png"_spr);
				break;
			}
			case 3015: {
				setIcon("eapulse.png"_spr);
				break;
			}
			case 3024: {
				setIcon("astop.png"_spr);
				break;
			}
			case 3017: {
				setIcon("emove.png"_spr);
				break;
			}
			case 3018: {
				setIcon("erotate.png"_spr);
				break;
			}
			case 3019: {
				setIcon("escale.png"_spr);
				break;
			}
			case 3020: {
				setIcon("ealpha.png"_spr);
				break;
			}
			case 3021: {
				setIcon("epulse.png"_spr);
				break;
			}
			case 3023: {
				setIcon("estop.png"_spr);
				break;
			}
		}

		if (cam == true) {
			if (ccolor == false) {
				switch(m_objectID) {
					case 1913: {
						setIcon("czoom.png"_spr);
							break;
					}
					case 1914: {
						setIcon("cstatic.png"_spr);
							break;
					}
					case 1916: {
						setIcon("Coffset.png"_spr);
							break;
					}
					case 2015: {
						setIcon("crotate.png"_spr);
							break;
					}
					case 2062: {
						setIcon("edge.png"_spr);
							break;
					}
					case 2925: {
						setIcon("mode.png"_spr);
							break;
					}
					case 2016: {
						setIcon("guide.png"_spr);
							break;
					}	
				}
			}
			else {
				switch(m_objectID) {
					case 1913: {
						setIcon("zoom.png"_spr);
							break;
					}
					case 1914: {
						setIcon("static.png"_spr);
							break;
					}
					case 1916: {
						setIcon("offset.png"_spr);
							break;
					}
					case 2015: {
						setIcon("rotatecam.png"_spr);
							break;
					}
					case 2062: {
						setIcon("edge.png"_spr);
							break;
					}
					case 2925: {
						setIcon("mode.png"_spr);
							break;
					}
					case 2016: {
						setIcon("guide.png"_spr);
							break;
					}	
				}
			}	
		}
		
}
	

	void setIcon(std::string texture){
		if (CCSprite* newSpr = CCSprite::create(texture.c_str())) {
			m_addToNodeContainer = true;
			setTexture(newSpr->getTexture());
			setTextureRect(newSpr->getTextureRect());
		}
	}
};