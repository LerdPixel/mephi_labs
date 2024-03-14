#pragma once
#include <utility>
#include "Pair.h"

template <typename TKey, typename TValue>
struct std::hash<Pair<TKey, TValue>> {
	std::size_t operator()(Pair<TKey, TValue>& pair) {
		std::size_t first = std::hash<TKey>()(pair.GetKey());
		std::size_t second = std::hash<TValue>()(pair.GetValue());
		return first ^ second;
	}
};