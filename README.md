# Nwo5's Silly API
a bunch of utils for my mods to make my life easier

if ur not a dev this is useless to u

if u wanna use this mod for some reason docs are mostly in headers, otherwise heres an overview

## Editor
make fw the editor hopefully easier :3

### Basics
u can include with

```cpp
#include <nwo5.silly-api/include/editor/include.hpp>
```

editor utils are split into a couple different namespaces

- editor
    - object
    - selection
    - constants

### Editor
uncategorized/general utils related to the editor

one of the most important functions from here is `nwo5::editor::update()`
most/all editor functions in the api dont actually update stuff like editor buttons or info label
so you need to do that with this function :3

### Object
everything related to getting data from/manipulating objs

for example to scale an object

```cpp
#include <Geode/modify/EditorUI.hpp>
#include <nwo5.silly-api/include/editor/include.hpp>

using namespace geode::prelude;

class $modify(EditorUI) {
    void customScaleObjects(CCArray* pObjects, float pScale) {
        // scale pObjects to pScale (biggest obj scale will be pScale, everything else gets scaled accordingly) with undo enabled
        nwo5::editor::object::scale(pObjects, pScale, true);

        nwo5::editor::update();
    }
};
```

### Selection
makes managing the editor selection a little easier

## Settings Cache
part of this mod is a way to cache/easily access geode settings thru inline variables

### Basics
u set up a setting like this

```cpp
#include <nwo5.silly-api/include/settings/include.hpp>

namespace Settings {
    // define a bool setting that cooresponds to mod setting "silly-setting"
    inline nwo5::settings::Setting<bool> sillySetting{"silly-setting"};
}
```

and u can use it like so

```cpp
#include <Geode/modify/MenuLayer.hpp>
#include "settings.hpp"

using namespace geode::prelude;

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        // settings also have a conversion operator which works fine for most cases
        // but id reccommend just using .get(); its more explicit anyway so :3
        if (Settings::sillySetting.get()) {
            log::info("haiiii :3");
        }

        return true;
    };
};
```

somewhere in ur mod u have to load settings

```cpp
#include <nwo5.silly-api/include/settings/include.hpp>

$on_mod(Loaded) {
    nwo5::settings::SettingsManager::get()->load();
}
```

### Categories
settings can be categorized, u can define ur categories before loading settings

```cpp
#include <nwo5.silly-api/include/settings/include.hpp>

$on_mod(Loaded) {
    nwo5::settings::SettingsManager::get()->registerCategories(
        // simply define a category
        {"Silly Category"},
        // define a category with a description and set its priority
        // u can use an enum as priority itll be automatically casted
        {"Sillier Category", "is a sillier category than silly category", 10},
        // define a category with no description but with a logo
        {"Silliest Category", std::nullopt, "silliest-category-logo.png"_spr}

        // SettingsManager::get()::getCategories returns a vector of category* sorted by priority
        // category priority is by default 0
    );

    nwo5::settings::SettingsManager::get()->load();
}
```

u can add a setting to a category like so

```cpp
#include <nwo5.silly-api/include/settings/include.hpp>

namespace Settings {
    inline nwo5::settings::Setting<bool> sillyCategorizedSetting{"silly-categorized-setting", "Silly Category"};
}
```

### Data
if u wanna add some extra data to ur settings you can either inheret setting to add constructors or use an alias

```cpp
struct SillyData {
    bool isSilly = true;
};

template<typename T>
class SillySetting : public nwo5::settings::Setting<T, SillyData> {
public:
    SillySetting(std::string_view pKey, SillyData pData)
        : nwo5::settings::Setting<T, SillyData>(pKey) 
    {
        this->data() = pData;
    }
};

// alternatively just make an alias and set data whenever
template<typename T>
using MySillySetting = Setting<T, SillyData>
```

### Saved Settings
there are also saved settings that use geode saved values if u want to implement settings in ur mod completely from scratch (like silly edit)

```cpp
#include <nwo5.silly-api/include/settings/include.hpp>

namespace Settings {
    // key is automatically generated with category + name
    inline nwo5::settings::SavedSetting<bool> sillySavedSetting{"Silly Saved Setting", "Silly Category", true, "a silly saved setting"};
}
```

## Utils
the rest of the utils in this mod are prolly useless to u but i use them in my mods usually :3