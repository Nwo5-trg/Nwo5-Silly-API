#pragma once

#include "settings-manager.hpp"
#include "saved-setting.hpp"

namespace nwo5::settings {
    namespace prelude {
        template<typename T>
        using Setting = nwo5::settings::Setting<T>;
        using nwo5::settings::GenericSetting, nwo5::settings::SettingBase, 
        nwo5::settings::SavedSettingBase, nwo5::settings::SavedSetting,
        nwo5::settings::SettingsManager, nwo5::settings::Category,
        nwo5::settings::SettingType;

        using GeodeSetting = geode::Setting;
    }
}