#pragma once

#include "setting.hpp"

#define SCAPI_INLINE_CATEGORY(...) \
inline auto GEODE_CONCAT(scapi_categoryDecl, GEODE_CONCAT(__LINE__, __COUNTER__)) = SettingsManager::get()->registerCategory({__VA_ARGS__});

namespace nwo5::settings {
    class SILLY_API_DLL Category final {
    private:
        std::string m_name;
        std::optional<std::string> m_description;

        std::optional<std::string> m_logo;

        int m_priority;
        
        std::vector<GenericSetting*> m_settings;

    public:
        template<typename T = int>
        requires std::is_scoped_enum_v<T> || std::is_integral_v<T>
        Category(std::string_view pName, T pPriority = 0)
            : m_name(pName), m_priority(static_cast<int>(pPriority))  {}
         template<typename T = int>
        requires std::is_scoped_enum_v<T> || std::is_integral_v<T>
        Category(std::string_view pName, std::string_view pDescription, T pPriority = 0)
            : m_name(pName), m_description(pDescription), m_priority(static_cast<int>(pPriority)) {}
        template<typename T = int>
        requires std::is_scoped_enum_v<T> || std::is_integral_v<T>
        Category(std::string_view pName, std::optional<std::string> pDescription, std::string_view pLogo, T pPriority = 0)
            : m_name(pName), m_description(std::move(pDescription)), m_logo(pLogo), m_priority(static_cast<int>(pPriority)) {}

        /// register pSetting as belonging to this category
        /// @returns if the setting was successfully added
        bool registerSetting(GenericSetting* pSetting) {
            if (!pSetting || getSetting(pSetting->name())) {
                return false;
            }

            m_settings.push_back(pSetting);

            return true;
        }

        /// gets setting with key
        /// @tparam T return type casted to T*, by default GenericSetting but you can specify Setting<float> or SavedSetting<bool> or smth
        /// @returns setting or nullptr if not found
        template<typename ImplT = GenericSetting, typename T = std::remove_pointer_t<ImplT>>
        T* getSetting(std::string_view pKey) const {
            auto it = std::ranges::find_if(m_settings, [&] (const auto& pSetting) {
                return pSetting->key() == pKey;
            });
            
            return static_cast<T*>(it == m_settings.end() ? nullptr : *it);
        }
        /// gets setting with name
        /// @tparam T return type casted to T*, by default GenericSetting but you can specify Setting<float> or SavedSetting<bool> or smth
        /// @returns setting or nullptr if not found
        template<typename ImplT = GenericSetting, typename T = std::remove_pointer_t<ImplT>>
        T* getSettingName(std::string_view pName) const {
            auto it = std::ranges::find_if(m_settings, [&] (const auto& pSetting) {
                return pSetting->name() == pName;
            });
            
            return static_cast<T*>(it == m_settings.end() ? nullptr : *it);
        }

        /// gets category name
        auto name() const {
            return m_name;
        }
        /// gets category description
        /// @returns description or empty string if description not specified
        auto description() const {
            return m_description.value_or("");
        }
        /// see if category has description
        bool hasDescription() const {
            return m_description.has_value();
        }
        /// gets category logo (path)
        /// @returns logo or empty string if logo not specified
        auto logo() const {
            return m_logo.value_or("");
        }
        /// see if category has logo
        bool hasLogo() const {
            return m_logo.has_value();
        }
        /// get categories priority
        auto priority() const {
            return m_priority;
        }
        /// get all settings that belong to the category
        const auto& getSettings() const {
            return m_settings;
        }
    };
}