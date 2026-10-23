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

            Changed(m_mod, m_key).send(this);

            m_listener.destroy();

            m_loaded = true;
        }

        template<typename Marker>
        using EventType = geode::GlobalEvent<Marker, bool(geode::Mod* mod, std::string_view key, void* setting), bool(void* setting), geode::Mod*, std::string>;

    public:
        struct Changed : public EventType<Changed> {
            using EventType<Changed>::Event;
        };

        using Type = T;

        ValueCache(std::string key, T defaultValue = T{}, geode::Mod* mod = geode::Mod::get())
            : m_default(defaultValue), m_key(key), m_mod(mod)
        {
            if (m_mod && m_mod->isLoaded()) {
                this->load();
            }
            else {
                // lol this just gets overwritten but i only rly need it for the inital loading
                m_listener = geode::ModStateEvent(geode::ModEventType::Loaded, m_mod).listen([this] {
                    this->load();
                }, geode::Priority::First);
            }
        }
        
        const T& operator*() const {
            return m_value;
        }
        operator const T&() const {
            return m_value;
        }
        auto operator==(const T& val) const {
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

            Changed(m_mod, m_key).send(this);

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
        auto key() const {
            return m_key;
        }
        /// get mod
        auto mod() const {
            return m_mod;
        }

        /// listen to when this saved value changed
        /// @returns listener handle
        auto listen(geode::Function<bool(ValueCache* setting)> callback) const {
            return Changed(m_mod, m_key).listen([customCallback = std::move(callback)] (void* setting) {
                if constexpr (std::same_as<geode::utils::function::Return<decltype(callback)>, void>) {
                    customCallback(static_cast<T*>(setting));
                }
                else {
                    return customCallback(static_cast<T*>(setting));
                }

                return geode::ListenerResult::Propagate;
            });
        }

        /// sync the underlying setting value with cached value
        void sync() {
            if (m_mod) {
                m_mod->setSavedValue(m_key, m_value);
            }
        }
    };
}