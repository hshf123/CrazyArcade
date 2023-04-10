#pragma once

#include "Allocator.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <array>
using namespace std;

template<class Type>
using Vector = vector<Type, STLAllocator<Type>>;

template<class Type>
using List = list<Type, STLAllocator<Type>>;

template<class Type>
using Deque = deque<Type, STLAllocator<Type>>;

template<class Type, class Container = Deque<Type>>
using Queue = queue<Type, Container>;

template<class Type, class Container = Vector<Type>, class Pred = less<class Container::value_type>>
using PriorityQueue = priority_queue<Type, Container, Pred>;

template<class Type, class Container = Deque<Type>>
using Stack = stack<Type, Container>;

template <class Key, class Type, class Pred = less<Key>>
using Map = map<Key, Type, Pred, STLAllocator<pair<const Key, Type>>>;

template <class Key, class Type, class Pred = less<Key>>
using MultiMap = multimap<Key, Type, Pred, STLAllocator<pair<const Key, Type>>>;

template <class Key, class Type, class Hasher = hash<Key>, class KeyEq = equal_to<Key>>
using HashMap = unordered_map<Key, Type, Hasher, KeyEq, STLAllocator<pair<const Key, Type>>>;

template<class Key, class Pred = less<Key>>
using Set = set<Key, Pred, STLAllocator<Key>>;

template <class Key, class Pred = less<Key>>
using MultiSet = multiset<Key, Pred, STLAllocator<Key>>;

template <class Key, class Hasher = hash<Key>, class KeyEq = equal_to<Key>>
using HashSet = unordered_set<Key, Hasher, KeyEq, STLAllocator<Key>>;

using String = basic_string<char, char_traits<char>, STLAllocator<char>>;

using WString = basic_string<wchar_t, char_traits<wchar_t>, STLAllocator<wchar_t>>;

template<class Type, uint32 size>
using Array = array<Type, size>;