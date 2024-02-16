#pragma once

template <typename T>
class optional {
private:
    alignas(T) unsigned char data[sizeof(T)];
    bool m_has_value;

public:
    optional() : m_has_value(false) {}

    optional(const T& value) : m_has_value(true) {
        new(data) T(value);
    }

    optional(T&& value) : m_has_value(true) {
        new(data) T(std::move(value));
    }

    optional(const optional& other) : m_has_value(other.m_has_value) {
        if (other.m_has_value)
            new(data) T(*reinterpret_cast<const T*>(other.data));
    }

    optional(optional&& other) : m_has_value(other.m_has_value) {
        if (other.m_has_value)
            new(data) T(std::move(*reinterpret_cast<T*>(other.data)));
    }

    ~optional() {
        if (m_has_value)
            reinterpret_cast<T*>(data)->~T();
    }

    optional& operator=(const optional& other) {
        if (this != &other) {
            if (m_has_value && !other.m_has_value) {
                reinterpret_cast<T*>(data)->~T();
                m_has_value = false;
            } else if (!m_has_value && other.m_has_value) {
                new(data) T(*reinterpret_cast<const T*>(other.data));
                m_has_value = true;
            } else if (m_has_value && other.m_has_value) {
                *reinterpret_cast<T*>(data) = *reinterpret_cast<const T*>(other.data);
            }
        }
        return *this;
    }

    optional& operator=(optional&& other) {
        if (this != &other) {
            if (m_has_value && !other.m_has_value) {
                reinterpret_cast<T*>(data)->~T();
                m_has_value = false;
            } else if (!m_has_value && other.m_has_value) {
                new(data) T(std::move(*reinterpret_cast<T*>(other.data)));
                m_has_value = true;
            } else if (m_has_value && other.m_has_value) {
                *reinterpret_cast<T*>(data) = std::move(*reinterpret_cast<T*>(other.data));
            }
        }
        return *this;
    }

    bool has_value() const {
        return m_has_value;
    }
    const T& value() const {
        if (!m_has_value)
            throw std::logic_error("optional does not contain a value");
        return **this;
    }

    T& value() {
        if (!m_has_value)
            throw std::logic_error("optional does not contain a value");
        return **this;
    }

    T value_or(const T& default_value) const {
        return m_has_value ? **this : default_value;
    }

    T value_or(T&& default_value) const {
        return m_has_value ? std::move(**this) : std::move(default_value);
    }

    explicit operator bool() const {
        return m_has_value;
    }

    T& operator*() {
        return *reinterpret_cast<T*>(data);
    }

    const T& operator*() const {
        return *reinterpret_cast<const T*>(data);
    }

    T* operator->() {
        return reinterpret_cast<T*>(data);
    }

    const T* operator->() const {
        return reinterpret_cast<const T*>(data);
    }
};