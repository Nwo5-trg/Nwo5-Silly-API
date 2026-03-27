#pragma once

#include <Geode/loader/ModSettingsManager.hpp>
#include "../export.hpp"

namespace nwo5::settings {
    enum class SettingType {
        Custom = 0,
        Bool = 1,
        Int = 2,
        Float = 3,
        RGB = 4,
        RGBA = 5,
        File = 6,
        String = 7
    };

    // ill come up with smth better later cuz this is very flawed but works fine for now !
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::Custom);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires std::same_as<T, bool>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::Bool);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires (!std::same_as<T, bool>) && std::is_integral_v<T>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::Int);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires std::is_floating_point_v<T>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::Float);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires std::same_as<T, cocos2d::ccColor3B>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::RGB);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires std::same_as<T, cocos2d::ccColor4B>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::RGBA);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires std::same_as<T, std::filesystem::path>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::File);
    }
    template<typename ImplT, typename T = std::decay_t<ImplT>>
    requires std::same_as<T, std::string>
    constexpr int getSettingType() {
        return static_cast<int>(SettingType::String);
    }

    class Category;

    class SILLY_API_DLL GenericSetting {
    protected:
        bool m_loaded = false;
        bool m_isGeodeSetting;

        std::string m_key;

        std::vector<std::string> m_categories;

    public:    
        GenericSetting(std::string_view pKey, bool pIsGeodeSetting);

        virtual ~GenericSetting() = default;

        friend class SettingsManager;

        GenericSetting(const GenericSetting&) = delete;
        GenericSetting& operator=(const GenericSetting&) = delete;
        GenericSetting(GenericSetting&&) = delete;
        GenericSetting& operator=(GenericSetting&&) = delete;

        /// get setting name
        /// @returns setting name, or setting key if setting doesnt have a name, or empty string if setting not loaded
        virtual std::string name() const = 0;
        /// see if setting has a name
        /// @note returns false if setting only has a key and no name
        virtual bool hasName() const = 0;
        /// get setting description
        /// @returns settting description, or empty string if setting not loaded or setting doesnt have a description
        virtual std::string description() const = 0;
        /// see if setting has a description
        virtual bool hasDescription() const = 0; 

        /// get setting key
        std::string key() {
            return m_key;
        }
        /// see if setting is loaded, using an unloaded setting will make things go all cattywampus so
        bool loaded() const {
            return m_loaded;
        }
        /// see if setting is a geode setting cache, or a custom saved value setting
        bool isGeodeSetting() const {
            return m_isGeodeSetting;
        }
        /// get categories setting belongs to
        const auto& categories() const {
            return m_categories;
        }
        /// see if setting belongs to a category
        bool categorized() const {
            return !m_categories.empty();
        }
        
        /// @brief try loading a setting
        /// loads setting and its categories, and sets loaded to true if everything went well :3
        virtual void load() = 0;
        /// set setting/saved value
        virtual void save() = 0;

         /// gets type enum for templated type
        virtual SettingType type() const = 0;
    };

    template<typename Data>
    class SettingData {
    protected:
        Data m_data{};
    
    public:
        /// gets data
        auto& data() {
            return m_data;
        }
    };
    template<>
    class SettingData<void> {};

    template<typename T>
    class SettingBase : public GenericSetting {
    protected:
        using GeodeSettingType = geode::SettingTypeForValueType<T>::SettingType;

        std::shared_ptr<GeodeSettingType> m_setting = nullptr;
        
        T m_value;

    public:
        SettingBase(std::string_view pKey) 
            : GenericSetting(pKey, true) {}

        operator const T&() {
            return m_value;
        }
        
        /// get setting name
        /// @returns setting name, or setting key if setting doesnt have a name, or empty string if setting not loaded
        virtual std::string name() const override {
            return m_setting ? m_setting->getDisplayName() : "";
        }
        /// see if setting has a name
        /// @note returns false if setting only has a key and no name
        virtual bool hasName() const override {
            return m_setting ? m_setting->getName().has_value() : false;
        }
        /// get setting description
        /// @returns settting description, or empty string if setting not loaded or setting doesnt have a description
        virtual std::string description() const override {
            return m_setting && m_setting->getDescription().has_value() ? m_setting->getDescription().value() : "";
        }
        /// see if setting has a description
        virtual bool hasDescription() const override {
            return m_setting ? m_setting->getDescription().has_value() : false;
        }

        /// get value
        const auto& get() const {
            return m_value;
        }
        /// get default value
        auto getDefault() const {
            return m_setting ? static_cast<T>(m_setting->getDefaultValue()) : T{};
        }
        /// set value to pVal and cooresponding geode setting
        /// @returns old setting value
        auto set(const T& pVal) {
            const auto ret = m_value;

            m_value = pVal;
            save();

            return ret;
        }

        /// gets underlying geode setting
        auto getSetting() {
            return m_setting;
        }

        /// @brief try loading a setting
        /// tries to find setting for key, 
        /// loads value and event listener if key is valid
        /// sets loaded to true if everything went well :3
        virtual void load() override {

            if (m_loaded || !(m_setting = geode::cast::typeinfo_cast<GeodeSettingType*>(geode::Mod::get()->getSetting(m_key)))) {
                return;
            }

            m_value = m_setting->getValue();

            geode::listenForSettingChanges<T>(key(), [this] (T pVal) {
                m_value = pVal;
            });

            m_loaded = true;
        }
        /// sets setting if loaded
        virtual void save() override {
            if (m_loaded) {
                m_setting->setValue(m_value);
            }
        }

        /// gets type enum for templated type
        virtual SettingType type() const override {
            return static_cast<SettingType>(getSettingType<T>());
        }
    };

    template<typename T, typename Data = void>
    class Setting : public SettingBase<T>, public SettingData<Data> {
    public:
        Setting(std::string_view pKey) 
            : SettingBase<T>(pKey) {}
        Setting(std::string_view pKey, std::string_view pCategory) 
            : SettingBase<T>(pKey) 
        {
            this->m_categories.emplace_back(pCategory);
        }
        Setting(std::string_view pKey, std::initializer_list<std::string> pCategories) 
            : SettingBase<T>(pKey) 
        {
            for (auto category : pCategories) {
                this->m_categories.push_back(category);
            }
        }

        Setting& operator=(const T& pVal) {
            set(pVal);

            return *this;
        }
    };
}