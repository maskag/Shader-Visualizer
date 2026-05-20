#include "texture.hpp"

namespace texture {
    const std::unordered_map<int, std::string> iconMap = {
        // SHADER
        {2904, "shader"}, {2905, "shockWave"}, {2907, "shockLine"}, {2909, "glitch"}, {2910, "chromatic"}, {2911, "chromaticGlitch"},
        {2912, "pixelate"}, {2913, "lineCircles"},{2914, "radialBlur"},{2915, "motionBlur"},{2916, "bulge"},{2917, "pinch"},
        {2919, "grayScale"},{2920, "sepia"},{2921, "invertColor"},{2922, "hue"},{2923, "editColor"},{2924, "splitScreen"},

        // COLOR
        {899, "col"},{29, "col_bg"},{30, "col_grnd"},{105, "col_obj"},{744, "col_3dl"},
        {900, "col_grnd2"},{915, "col_line"},{1006, "pulse"},

        // DEFAULT
        {901, "move"},{1346, "rotate"},{1049, "toggle"},{1268, "spawn"},{1616, "stop"},
        {1815, "collision"},{3609, "InsCollision"},{2066, "gravity"},

        // AREA
        {3006, "areaMove"},{3007, "areaRotate"},{3008, "areaScale"},{3009, "areaFade"},{3010, "areaTint"},
        {3011, "editAreaMove"},{3012, "editAreaRotate"},{3013, "editAreaScale"},{3014, "editAreaFade"},{3015, "editAreaTint"},
        {3017, "enterMove"},{3018, "enterRotate"},{3019, "enterScale"},{3020, "enterFade"},{3021, "enterTint"},
        {3024, "areaStop"},{3023, "enterStop"},

        // CAMERA
        {1916, "offsetCam"},{1914, "staticCam"},{2062, "edgeCam_right"},{2015, "RotateCam_left"},
        {1913, "zoomCam"},{1520, "shake"},{2901, "gpOffCam"},{2925, "modeCam"},{2016, "guideCam"},

        // ITEM
        {3620, "comp"},{3619, "edit"},{3641, "pers"},{1611, "count"},{1811, "insCount"},
        {1817, "pickup"},{3614, "time"},{3615, "eventTime"},{3617, "controlTime"},

        // SPECIAL
        {3602, "sfx"},
        {3603, "editSfx"},
        {3604, "event"},
        {3613, "ui"},
        {31, "start"},

        // OTHER
        {1007, "alpha"},{2067, "scale"},{1917, "reverse"},{2900, "rotateGameplay"},
        {1347, "follow"},{1814, "followY"},{3016, "followAdv"},{3660, "editAdv"},{3661, "retargetAdv"},
        {1585, "animate"}, {3033, "keyframe"}, {3032, "key"},{1595, "touch"},{1912, "random"},{2068, "advRand"},{3607, "sequence"},
        {3029, "bgChange"},{3030, "gChange"},{3031, "mgChange"},{2999, "mg"},{3606, "bgSpeed"},{3612, "mgSpeed"},
        {3608, "spawnParticle"},{3618, "reset"},{1934, "song"},{3605, "editSong"},
        {1935, "timewarp"},{3662, "linkVisible"},{1812, "onDeath"},{3600, "end"},{2899, "options"},{3642, "bpm"},
        {2903, "gradient"},{33, "ghostDisable"},{32, "ghost"},{1613, "showPlayer"},{1612, "hidePLayer"},
        {1818, "bgEffect"},{1819, "bgEffectDisable"},{1932, "playerControl"},{1936, "teleport"},
        {3640, "stateBlock"},{1816, "collisionBlock"},{3643, "toggleBlock"}
    };
}
