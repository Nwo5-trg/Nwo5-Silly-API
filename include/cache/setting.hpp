#pragma once

#include "../export.hpp"

namespace nwo5::cache {
    template<typename T>
    requires requires { typename geode::SettingTypeForValueType<T>::SettingType; }
    class SettingCache {
    protected:  
        using GeodeSettingType = typename geode::SettingTypeForValueType<T>::SettingType;
        
        geode::Mod* m_mod = nullptr;
        std::shared_ptr<GeodeSettingType> m_setting = nullptr;
        std::string m_key;
        geode::ListenerHandle m_listener;
        T m_value{};

        void load() {
            if (m_setting || !m_mod) {
                return;
            }

            m_setting = geode::cast::typeinfo_pointer_cast<GeodeSettingType>(m_mod->getSetting(m_key));

            if (!m_setting) {
                return;
            }

            m_value = m_setting->getValue();

            m_listener = geode::SettingChangedEventV3(m_mod, m_key).listen([this] (std::shared_ptr<geode::SettingV3> setting) {
                if (auto ty = geode::cast::typeinfo_pointer_cast<GeodeSettingType>(setting)) {
                    m_value = ty->getValue();
                }
            }, geode::Priority::First);
        }

    public:
        using Type = T;

        SettingCache(std::string key, geode::Mod* mod = geode::Mod::get())
            : m_key(key), m_mod(mod)
        {
            if (m_mod && m_mod->isLoaded()) {
                this->load();
            }

            // lol this just gets overwritten but i only rly need it for the inital loading
            m_listener = geode::ModStateEvent(geode::ModEventType::DataLoaded, m_mod).listen([this] {
                this->load();
            });
        }
        
        const T& operator*() const {
            return m_value;
        }
        operator const T&() const {
            return m_value;
        }
        auto operator==(const T& val) {
            return m_value == val;
        }
        auto operator<=>(const T& val) const requires std::three_way_comparable<T> {
            return m_value <=> val;
        }
        auto& operator=(const T& val) {
            this->set(val);

            return *this;
        }

        /// set value and sync
        /// @returns old value
        T set(T val) {
            const auto ret = m_value;

            m_value = val;
            this->sync();

            return ret;
        }
        /// get value
        const T& get() const {
            return m_value;
        }

        /// get underlying setting
        auto data() const {
            return m_setting.get();
        }

        /// sync the underlying setting value with cached value
        void sync() {
            if (m_setting) {
                m_setting->setValue(m_value);
            }
        }
    };
}