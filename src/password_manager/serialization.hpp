#pragma once

#include <string>

template <class T> struct Serializer {
    std::string serialize(const T &obj) = delete;
    T deserialize(const std::string &str) = delete;
};

template <class T>
concept Serializable = std::convertible_to<T, std::string> || requires(T obj) {
    { Serializer<T>().serialize(obj) } -> std::convertible_to<std::string>;
    { Serializer<T>().deserialize("") } -> std::same_as<T>;
};
