#pragma once

#include "../export.hpp"

namespace nwo5::cache {
    template<typename T>
    class ValueCache {
    protected:  
        geode::Mod* m_mod = nullptr;
        bool m_loaded = false;
        std::string m_key;
        geode::ListenerHandle m_listener;
        T m_value{};
        T m_default{};

        void load() {
            if (m_loaded || !m_mod) {
                return;
            }

            m_value = m_mod->getSavedValue<T>(m_key, m_default);

            m_listener.destroy();

            m_loaded = true;
        }

    public:
        using Type = T;

        ValueCache(std::string pKey, T pDefault = T{}, geode::Mod* pMod = geode::Mod::get())
            : m_default(pDefault), m_key(pKey), m_mod(pMod)
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
        auto operator==(const T& pVal) {
            return m_value == pVal;
        }
        auto operator<=>(const T& pVal) const requires std::three_way_comparable<T> {
            return m_value <=> pVal;
        }
        auto& operator=(const T& pVal) {
            this->set(pVal);

            return *this;
        }

        /// set value and sync
        /// @returns old value
        T set(T pVal) {
            const auto ret = m_value;

            m_value = pVal;
            this->sync();

            return ret;
        }
        /// get value
        const T& get() const {
            return m_value;
        }
        /// reset value to default and sync
        /// @returns old value
        T reset() {
            const auto ret = m_value;

            m_value = m_default;
            this->sync();

            return ret;
        }
        /// get key
        auto key() {
            return m_key;
        }

        /// sync the underlying setting value with cached value
        void sync() {
            if (m_mod) {
                m_mod->setSavedValue(m_key, m_value);
            }
        }
    };
}