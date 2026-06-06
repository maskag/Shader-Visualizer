#pragma once

#include "theme.hpp"
#include <Geode/Geode.hpp>
#include <array>
#include <string_view>
#include <unordered_map>

using namespace geode::prelude;

bool getSwitchValue(std::string const& key);

namespace texture {
    inline constexpr auto spriteKeys = std::to_array<std::string_view>({
        "advRand", "random",
        "alpha", "animate",

        "areaFade", "areaMove", "areaRotate", "areaScale", "areaStop", "areaTint",
        "area_type1", "area_type2", "area_type3", "area_type4", "area_type5",
        "area_type6", "area_type7", "area_type8", "area_type9", "area_type10",
        "color_areaStop",

        "enterFade", "enterMove", "enterRotate", "enterScale", "enterStop", "enterTint",
        "color_enterStop",

        "bgChange", "bgEffect", "bgEffectDisable", "bgSpeed",
        "mg", "mgChange", "mgSpeed",

        "col", "col_3dl", "col_bg", "col_empty", "col_grnd", "col_grnd2",
        "col_line", "col_obj", "col_preset",
        "collision", "collision_exit", "collisionBlock", "InsCollision",

        "comp", "comp_eq", "comp_gt", "comp_gte", "comp_lt", "comp_lte", "comp_neq",
        "count", "controlTime",

        "edit", "edit_add", "edit_div", "edit_dot", "edit_mul", "edit_set", "edit_sub",
        "editAdv", "editColor", "editColor_preset", "editSfx", "editSong",
        "editAreaFade", "editAreaMove", "editAreaRotate", "editAreaScale", "editAreaTint",

        "event", "eventTime", "event_titles", "event_other",
        "event_checkpoint", "event_checkpoint2", "event_coin", "event_coin2",
        "event_fall", "event_fall2", "event_gravity", "event_gravity2",
        "event_hit", "event_hit2", "event_jump", "event_jump2",
        "event_land", "event_land2", "event_orb", "event_orb2",
        "event_pad", "event_pad2", "event_portal", "event_portal2",
        "event_reverse", "event_reverse2",
        "event_left", "event_left2", "event_leftRelease", "event_leftRelease2",
        "event_right", "event_right2", "event_rightRelease", "event_rightRelease2",
        "event_up", "event_up2", "event_upRelease", "event_upRelease2",

        "follow", "followAdv", "followY", "retargetAdv",
        "gravity", "gravity_high", "gChange",

        "edgeCam_down", "edgeCam_left", "edgeCam_right", "edgeCam_up",
        "guideCam", "modeCam", "offsetCam", "OffsetCam_x", "OffsetCam_y",
        "RotateCam_left", "RotateCam_right", "staticCam", "staticCam_follow", "zoomCam",

        "move", "move_direction", "move_lock", "move_target",
        "rotate", "rotate_aim", "rotate_follow", "rotateGameplay", "scale",

        "pickup", "pickup_add", "pickup_div", "pickup_mul", "pickup_set", "pickup_sub",
        "insCount", "insCount_eq", "insCount_gt", "insCount_lt",

        "pulse", "pulse_empty",
        "sfx", "sfx_0", "sfx_1", "sfx_2", "sfx_3", "sfx_4", "song",

        "spawn", "spawn_remap", "spawnParticle",
        "start", "start_ball", "start_cube", "start_path", "start_preset",
        "start_robot", "start_ship", "start_spider", "start_swing",
        "start_ufo", "start_wave", "start_titles",
        "start_speed0", "start_speed1", "start_speed2", "start_speed3", "start_speed4",
        "stop", "stop_pause", "stop_resume", "end",

        "ui", "ui_element", "ui_preset", "ui_titles", "ui_xRel", "ui_yRel",

        "bulge", "chromatic", "chromaticGlitch", "glitch", "gradient", "grayScale", "hue",
        "invertColor", "motionBlur", "pinch", "pixelate", "radialBlur",
        "sepia", "shader", "shockLine", "shockWave", "splitScreen",

        "ghost", "ghostDisable", "hidePLayer", "showPlayer",
        "gpOffCam", "lineCircles", "onDeath", "pers", "playerControl",

        "bpm", "key", "keyframe", "linkVisible", "options", "reset", "reverse", "sequence",
        "shake", "stateBlock", "teleport", "time", "timewarp", "toggle", "toggleBlock", "touch",
    });

    extern const std::unordered_map<int, std::string> iconMap;

    void setObjIcon(EffectGameObject* obj, const std::string& texture);

    std::string sprite(std::string const& key);
    CCSprite* createSprite(std::string const& key);
    std::string rawSprite(std::string const& key);
    std::string rawSprite(std::string const& key, theme::Themes selectedTheme);
    CCSprite* createRawSprite(std::string const& key);
    CCSprite* createRawSprite(std::string const& key, theme::Themes selectedTheme);
}
