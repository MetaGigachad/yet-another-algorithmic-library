#include "../src/hash_map.hpp"

#include <cassert>
#include <map>
#include <string>

static void single_insert() {
    HashMap<std::string, std::string> map;
    map.insert("first", "1");
    assert(map.get("first") == "1");
}

static void overwrite() {
    HashMap<std::string, std::string> map;
    map.insert("first", "1");
    map.insert("first", "2");
    assert(map.get("first") == "2");
}

static void multiple_insertions() {
    HashMap<int, int> map;
    std::map<int, int> std_map;
    int value = 1;
    for (int key = 0; key < 1000; ++key) {
        value *= -1;
        value += key;
        map.insert(key, value);
        std_map.insert({key, value});
    }
    for (const auto& [key, value] : std_map) {
        assert(map.get(key) == value);
    }
}

static void invalid_key() {
    HashMap<std::string, std::string> map;
    map.insert("fourth", "4");
    assert(map.get("fourth") == "4");
    bool success = false;
    try {
        map.get("fifth");
    } catch (std::exception&) {
        success = true;
    }
    assert(success);
}

void hash_map_test() {
    single_insert();
    overwrite();
    multiple_insertions();
    invalid_key();
}
