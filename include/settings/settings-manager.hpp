#pragma once

#include "category.hpp"

namespace nwo5::settings {
    class SILLY_API_DLL SettingsManager final {
    private:
        std::vector<GenericSetting*> m_queuedSettings;
        std::vector<GenericSetting*> m_allSettings;

        // make ptr shenanigans a lil safer w/ deque
        std::deque<Category> m_categories;
        std::vector<Category*> m_sortedCategories;
        Category m_uncategorized {"Uncategorized", "", std::numeric_limits<int>::min()};

        SettingsManager() = default;
        ~SettingsManager() = default;
        
    public:
        SettingsManager(const SettingsManager&) = delete;
        SettingsManager& operator=(const SettingsManager&) = delete;
        SettingsManager(SettingsManager&&) = delete;
        SettingsManager& operator=(SettingsManager&&) = delete;

        static auto* get() {
            static SettingsManager inst;
            return &inst;
        };

        /// adds setting to queued settings
        /// @returns if the setting was successfully registered
        bool registerSetting(GenericSetting* pSetting) {
            if (!pSetting || std::ranges::contains(m_allSettings, pSetting)) {
                return false;
            }

            m_queuedSettings.push_back(pSetting);

            return false;
        }
        /// gets setting with key
        /// @tparam T return type casted to T*, by default GenericSetting but you can specify Setting<float> or SavedSetting<bool> or smth
        /// @returns setting or nullptr if not found
        template<typename ImplT = GenericSetting, typename T = std::remove_pointer_t<ImplT>>
        T* getSetting(std::string_view pKey) const {
            auto it = std::ranges::find_if(m_allSettings, [&] (const auto& pSetting) {
                return pSetting->key() == pKey;
            });
            
            return static_cast<T*>(it == m_allSettings.end() ? nullptr : *it);
        }
        /// gets setting with name
        /// @tparam T return type casted to T*, by default GenericSetting but you can specify Setting<float> or SavedSetting<bool> or smth
        /// @returns setting or nullptr if not found
        template<typename ImplT = GenericSetting, typename T = std::remove_pointer_t<ImplT>>
        T* getSettingName(std::string_view pName) const {
            auto it = std::ranges::find_if(m_allSettings, [&] (const auto& pSetting) {
                return pSetting->name() == pName;
            });
            
            return static_cast<T*>(it == m_allSettings.end() ? nullptr : *it);
        }

        /// registers a category
        /// @returns ptr to registered category or nullptr if category couldnt be registered
        Category* registerCategory(Category pCategory) {
            if (getCategory(pCategory.name())) {
                return nullptr;
            }

            m_categories.push_back(std::move(pCategory));
            
            auto ptr = &m_categories.back();

            m_sortedCategories.push_back(ptr);

            std::ranges::sort(m_sortedCategories, [] (const auto& pA, const auto& pB) {
                return pA->priority() < pB->priority();
            });
            
            return ptr;
        }
        /// the not scuffed way to register categories
        template<typename... Args>
        void registerCategories(Args... pArgs) {
            (registerCategory(std::move(pArgs)), ...);
        }
        /// get a category by name
        /// @returns category or nullptr if no category by that name is registered
        Category* getCategory(std::string_view pName) {
            auto it = std::ranges::find_if(m_sortedCategories, [&] (const auto& pCategory) {
                return pCategory->name() == pName;
            });

            return it == m_sortedCategories.end() ? nullptr : *it;
        } 
        /// get uncategorized category (ironic ik)
        Category* getUncategoried() {
            return &m_uncategorized;
        }

        /// get a vector of all settings
        const auto& allSettings() const {
            return m_allSettings;
        }
        /// get a vector of all categories (sorted)
        const auto& getCategories() const {
            return m_sortedCategories;
        }

        /// load all queued settings 
        void load() {
            for (auto setting : m_queuedSettings) {
                bool categorized = false;

                if (!setting->categorized()) {
                    m_uncategorized.registerSetting(setting);

                    categorized = true;
                }
                else {
                    for (const auto& category : setting->m_categories) {
                        if (auto ptr = getCategory(category)) {
                            ptr->registerSetting(setting);

                            categorized = true;
                        }
                        else if (registerCategory({category})) {
                            getCategory(category)->registerSetting(setting);

                            categorized = true;
                        }
                    }
                }

                if (!categorized) {
                    m_uncategorized.registerSetting(setting);
                }

                m_allSettings.push_back(setting);

                setting->load();
            }

            m_queuedSettings.clear();
        }
    };

    inline GenericSetting::GenericSetting(std::string_view pKey, bool pIsGeodeSetting)
        : m_key(pKey), m_isGeodeSetting(pIsGeodeSetting) 
    {
        SettingsManager::get()->registerSetting(this);
    }
}