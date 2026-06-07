# <cg>v3.0.0-beta.4</c>
## TOGGLE SPRITE, I HATE YOU
- Removed the toggle sprite, which wasn't supposed to be in the mod

# <cg>v3.0.0-beta.3</c>
## Theme System & Area Trigger Label
- Added **label for Area triggers**
- Added a new **texture theme system**
  - Trigger Visualizer textures are no longer limited to a single visual style
  - The texture resolver, previews, and dynamic textures now work with the selected theme
  - Themes can be changed from the mod settings
- Added two initial themes:
  - **Visualizer** - the usual Trigger Visualizer theme, which redesigned trigger icons
  - **Standard** - keeps the original Geometry Dash style while retaining supported dynamic texture behavior
- This is **most likely the penultimate beta** before the **3.0.0 release**
  - The remaining work is focused primarily on stability improvements and polishing
  - Barring any major issues, the next update is expected to be the final beta before release 3.0.0

# <cg>v3.0.0-beta.2</c>
## Bug Fixes
- Fixed a crash when **closing the MG2 color popup** with **Better Touch Prio** installed
- Fixed dynamic textures being applied to trigger groups added by the **Object Groups** mod
- Added **new labels** 
  - Item Comp
  - Item Edit
  - Item Pers

# <cg>v3.0.0-beta.1</c>
## Trigger Labels Expansion & Refactoring
- Expanded **trigger label support**
  - Some triggers that previously had no numbers now display IDs directly on them
  - Added support for:
    - Event Trigger -> target groups
    - UI Trigger -> group ID
    - Static Camera Trigger -> target group
    - Time / Time Event / Time Control -> item ID
    - Song / Song Edit -> channel
  - More triggers will receive support in future updates
- Reworked and simplified **settings**
  - Removed unnecessary options
  - Cleaner organization
- Massive **code refactoring**
  - Cleaner and more maintainable codebase
  - Better folder structure
  - Improved namespace organization
- Updated **logo**
- Updated **mod description**
- Various minor improvements and fixes

# <cj>v2.2.3</c>
## New logo (ignore patch 3)
- New **logo**
- Fixed **Radial blur name** (Radical blur)
- Fixed a bug where the game could **crash when copying multiple objects**

# <cj>v2.2.2</c>
## New logo (ignore patch 2)
- New **logo** (again)
- Small changes
- Updated **mod description**
- Fixed some **trigger sprite**

# <cj>v2.2.1</c>
## Visual Refresh Patch
- Redrew **shader trigger sprites**
- New **logo**
- Updated **mod description**

# <cb>v2.2.0</c>
## Dynamic Texture Expansion & Improvements
- Added **new dynamic textures for Area triggers**
- Added **4 new trigger textures**
- Updated **10 existing trigger textures**
- Small **settings adjustments**
- Updated **mod description**
- Fixed various **bugs and issues**

# <cb>v2.1.0</c>
## Dynamic Texture & Settings Update
- Added **two new dynamic textures**
  - Pulse trigger - displays its color
  - Color trigger - displays its color
- Added **sprites for old Color triggers**
- Updated **Event trigger sprites**
- Small **settings adjustments**
- Fixed a **crash on Android** that occurred when enabling Free Mode on portals
- Fixed an **iOS startup issue** where the game would not launch with the mod enabled
- Various minor fixes and tweaks

# <cl>v2.0.1</c>
## Mini patch
- Added one dynamic texture (stop trigger)
- Small changes in the code

# <cp>v2.0.0</c>
## Massive Visual & Performance Update
- Reworked **131 trigger textures** to match original trigger resolutions  
  (near 1:1 accuracy with vanilla sizing)
- Enhanced **21 trigger textures** with improved visuals and alignment
- Added **7 dynamic textures**
  - Move trigger
  - Rotate trigger
  - Count trigger
  - Pickup trigger
  - Spawn trigger
  - Collision trigger
  - Gravity trigger
- **~5x performance improvement** from a partial rewrite and smarter update logic
- Large optimization pass
  - Reduced overhead
  - Fewer refresh cycles
  - Smoother editor performance
- Dynamic texture toggle moved to settings  
  (editor button removed)
- Dynamic item settings merged into a unified system
- Dynamic textures now update automatically on placement, copy, and setting changes
- Updated Geode to the latest version
- Added support for game version **2.2081**

# <cl>v1.6.1</c>
## Micro patch
- FPS message now appears **only once**

# <cb>v1.6.0</c>
## Dynamic Performance & Texture System Update
- Added **dynamic texture for StartPos** with ~2300 unique variations depending on settings and context
- Added **dynamic textures for Camera triggers**, reacting to their parameters
- Updated **collision block textures** with clearer visuals and better editor readability
- **Major code optimization**
  - Reduced editor draw calls
  - Optimized dynamic texture evaluation logic
  - Lower memory usage for texture caching
- General code cleanup and **refactoring** for better maintainability and stability
- Added **FPS monitoring system**
  - Detects low FPS situations
  - Displays a warning suggesting disabling certain dynamic textures

# <cb>v1.5.0</c>
## Visual Refresh Update
- Added **5 completely new trigger sprites**
- Updated and replaced **25 old trigger sprites**
- Improved overall visual consistency between trigger categories
- Minor tweaks to sprite alignment and scaling in the editor

# <cl>v1.4.2</c>
## Editor Interaction Fixes & Tweaks
- Added **dynamic texture for Item Edit triggers**
- Added **two new settings** for Item Edit textures
- Updated some trigger textures
- Dynamic button now disappears during Playtest

# <cb>v1.4.0</c>
## Dynamic Texture Expansion
- Added new dynamic textures
  - UI trigger
  - Item comp trigger
- Added new settings to configure dynamic textures
  - Enable Item comp dynamic texture
  - Enable UI dynamic texture
- Added a button in the editor to **toggle dynamic textures**

# <cl>v1.3.3</c>
## Smart Event Composition
- Added a new feature: **automatic texture combining** for Event triggers with multiple actions
- Added a new setting to enable or configure this behavior

# <cl>v1.3.2</c>
## Visual Settings Overhaul
- Added **Visual settings** section

# <cl>v1.3.1</c>
## Trigger Sprite Settings
- Added new trigger textures
  - Song
  - Song Edit
  - Shake
- Added new settings
  - Reset StartPos trigger texture
  - Reset Shake trigger texture
  - Reset Area Stop trigger texture

# <cb>v1.3.0</c>
## Dynamic Behavior Update
- Added **dynamic texture updates** for SFX and Event triggers
  - SFX textures now change depending on volume
  - Event textures change based on their settings
  - Settings allow disabling dynamic updates
  - Added **volume threshold setting** for SFX triggers
- Added several new textures for triggers that previously had no custom visuals

# <cb>v1.2.0</c>
## Camera & Visual Additions
- Added new **Camera trigger texture**
- Added several new trigger textures
- Added new settings

# <cb>v1.1.0</c>
## Trigger Visualizer
- Added new trigger textures
  - Gameplay triggers
  - Area triggers
  - Logical triggers
- Added mod settings
  - Toggle texture replacement per trigger category
- Fixed shader trigger icon offset in the editor
- Improved overall editor visual clarity

# <cl>v1.0.1</c>
## Platform Compatibility Patch
- **Cross-platform release**

# <cp>v1.0.0</c>
## Shader Visualizer
- Initial release
