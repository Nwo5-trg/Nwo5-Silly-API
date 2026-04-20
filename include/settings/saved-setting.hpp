#pragma once

#include "setting.hpp"

namespace nwo5::settings {
    inline std::string generateKey(std::string_view pName) {
        return geode::utils::string::replace(
            geode::utils::string::toLower(std::string{pName}), " ", "-"
        );
    }
    inline std::string generateKey(std::string_view pName, std::initializer_list<std::string> pCategories) {
        if (!pCategories.size()) {
            return generateKey(pName);
        }
        else {
            std::string str{pName};
            
            for (const auto& category : pCategories) {
                str = fmt::format("{}-{}", category, str);
            }

            return geode::utils::string::replace(geode::utils::string::toLower(str), " ", "-");
        }
    }
    inline std::string generateKey(std::string_view pName, std::string_view pCategory) {
        if (pCategory.empty()) {
            return generateKey(pName);
        }
        else {
            return geode::utils::string::replace(
                geode::utils::string::toLower(fmt::format("{}-{}", pCategory, pName)), 
                " ", "-"
            );
        }
    }

    template<typename T>
    class SavedSettingBase : public GenericSetting {
    protected:
        std::optional<std::string> m_name;
        std::optional<std::string> m_description;

        T m_value;
        T m_default;

    public:
        SavedSettingBase(std::string_view pKey, std::optional<std::string> pName, std::optional<std::string> pDescription, T pDefault, geode::Mod* pMod = geode::Mod::get()) 
            : GenericSetting(pKey, false, pMod), m_name(std::move(pName)), m_description(std::move(pDescription)), m_default(std::move(pDefault)) {}

        operator const T&() {
            return m_value;
        }

        /// get setting name
        /// @returns setting name, or setting key if setting doesnt have a name
        virtual std::string name() const override {
            return m_name.value_or(m_key);
        }
        /// see if setting has a name
        /// @note returns false if setting only has a key and no name
        virtual bool hasName() const override {
            return m_name.has_value();
        }
        /// get setting description
        /// @returns settting description, or empty string if setting doesnt have a description
        virtual std::string description() const override {
            return m_description.value_or("");
        }
        /// see if setting has a description
        virtual bool hasDescription() const override {
            return m_description.has_value();
        }

        /// get value
        const auto& get() const {
            return m_value;
        }
        /// get default value
        auto getDefault() const {
            return m_default;
        }
        /// set value to pVal and cooresponding saved value
        /// @returns old setting value
        auto set(const T& pVal) {
            const auto ret = m_value;

            m_value = pVal;
            save();

            return ret;
        }

        /// @brief try loading a setting
        /// gets saved value for key and loads the value
        /// sets loaded to true if everything went well :3
        virtual void load() override {
            if (m_loaded || !m_mod) {
                return;
            }

            if (m_mod->hasSavedValue(m_key)) {
                m_value = m_mod->getSavedValue<T>(m_key);
            }
            else {
                set(m_default);
            }

            m_loaded = true;
        }
        /// sets saved value if loaded
        virtual void save() override {
            if (m_loaded && m_mod) {
                m_mod->setSavedValue<T>(m_key, m_value);
            }
        }

        /// gets type enum for templated type
        virtual SettingType type() const override {
            return static_cast<SettingType>(getSettingType<T>());
        }
    };

    template<typename T, typename Data = void>
    class SavedSetting : public SavedSettingBase<T>, public SettingData<Data> {
    public:
        SavedSetting(std::optional<std::string> pName, T pDefault = T{}, std::optional<std::string> pDescription = std::nullopt)
            : SavedSettingBase<T>(generateKey(pName.value_or("")), std::move(pName), std::move(pDescription), std::move(pDefault)) {}
        SavedSetting(std::optional<std::string> pName, std::string_view pCategory, T pDefault = T{}, std::optional<std::string> pDescription = std::nullopt)
            : SavedSettingBase<T>(generateKey(pCategory, pName.value_or("")), std::move(pName), std::move(pDescription), std::move(pDefault))
        {
            this->m_categories.emplace_back(pCategory);
        }
        SavedSetting(std::optional<std::string> pName, std::initializer_list<std::string> pCategories, T pDefault = T{}, std::optional<std::string> pDescription = std::nullopt)
            : SavedSettingBase<T>(generateKey(pName.value_or("")), std::move(pName), std::move(pDescription), std::move(pDefault)) 
        {
            for (const auto& category : pCategories) {
                this->m_categories.push_back(category);
            }
        }
        SavedSetting(std::optional<std::string> pName, std::optional<std::string> pCategory, std::string_view pKey, T pDefault = T{}, std::optional<std::string> pDescription = std::nullopt)
            : SavedSettingBase<T>(pKey, std::move(pName), std::move(pDescription), std::move(pDefault)) 
        {
            if (pCategory.has_value()) {
                this->m_categories.push_back(pCategory.value());
            }
        }
        SavedSetting(std::optional<std::string> pName, std::initializer_list<std::string> pCategories, std::string_view pKey, T pDefault = T{}, std::optional<std::string> pDescription = std::nullopt)
            : SavedSettingBase<T>(pKey, std::move(pName), std::move(pDescription), std::move(pDefault)) 
        {
            for (const auto& category : pCategories) {
                this->m_categories.push_back(category);
            }
        }

        SavedSetting& operator=(const T& pVal) {
            set(pVal);

            return *this;
        }
    };
}