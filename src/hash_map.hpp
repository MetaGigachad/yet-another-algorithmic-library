#include <exception>
#include <functional>
#include <vector>

template <typename Key, typename Value>
class HashMap {
private:
    using size_t = std::size_t;

public:
    explicit HashMap() : data_(2), size_(0) {}

    void insert(Key key, Value value) {
        if (size_ == data_.size()) {
            resize_(data_.size() * 2 - 1);
        }
        auto& block = data_[hash_(key, data_.size())];
        if (!block.empty()) {
            for (auto& record : block) {
                if (record.first == key) {
                    record.second = value;
                    return;
                }
            }
        }
        block.push_back({std::move(key), std::move(value)});
        ++size_;
    }

    Value get(Key key) const {
        for (const auto& record : data_[hash_(key, data_.size())]) {
            if (record.first == key) {
                return record.second;
            }
        }
        throw std::exception();
    }

private:
    void resize_(size_t new_size) {
        std::vector<std::vector<std::pair<Key, Value>>> new_data(new_size);
        if (new_size == 0) {
            data_ = new_data;
            return;
        }
        for (const auto& block : data_) {
            for (const auto& record : block) {
                new_data[hash_(record.first, new_size)].push_back(record);
            }
        }
        data_ = new_data;
    }

    static inline size_t hash_(Key key, size_t mod) {
        return std::hash<Key> {}(key) % mod;
    }

private:
    std::vector<std::vector<std::pair<Key, Value>>> data_;
    size_t size_;
};