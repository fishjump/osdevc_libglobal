#pragma once

template <typename T>
class lazyload {
private:
    using TYPE = char[sizeof(T) / sizeof(char)];
    TYPE data  = {0};
    T *  ptr   = nullptr;

public:
    bool isInitialized() const {
        return ptr != nullptr;
    }

    template <typename... ARGS>
    void init(ARGS... args) {
        static_assert(sizeof(T) == sizeof(TYPE));
        if(ptr == nullptr) {
            ptr  = (T *)(&data);
            *ptr = T(args...);
        }
    }

    T *get() {
        return ptr;
    }
};
