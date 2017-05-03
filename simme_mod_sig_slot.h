#ifndef MOD_SIGNAL_HPP
#define MOD_SIGNAL_HPP

#include <functional>
#include <map>
#include <algorithm>

template <typename... Args>
class Signal {

    struct SlotId {
        void *receiver;
        void(*slot)();
        bool operator <(const SlotId &o) const {
            return ((receiver != o.receiver) || (slot != o.slot));
        }
    };

    int connect(SlotId id, std::function<void(Args...)> func) {
        slots_.insert(std::make_pair(id, func));
    }

    void disconnect(SlotId id) {
        auto it = slots_.find(id);
        if (it != slots_.end())
            slots_.erase(it);
    }

public:

    Signal() {}

    Signal(Signal const& other) {}

    template <typename T>
    int connect(T *inst, void (T::*func)(Args...)) {
        connect(SlotId{inst, reinterpret_cast<void(*)()>(func)}, ([=](Args... args) {
            (inst->*func)(args...);
        }));
    }

    template <typename T>
    int connect(T *inst, void (T::*func)(Args...) const) {
        connect(SlotId{inst, reinterpret_cast<void(*)()>(func)}, ([=](Args... args) {
            (inst->*func)(args...);
        }));
    }

    template <typename T>
    void disconnect(T *inst, void (T::*func)(Args...)) {
        disconnect(SlotId{inst, reinterpret_cast<void(*)()>(func)});
    }

    template <typename T>
    void disconnect(T *inst, void (T::*func)(Args...) const) {
        disconnect(SlotId{inst, reinterpret_cast<void(*)()>(func)});
    }

    void disconnect_all() {
        slots_.clear();
    }

    void emit(Args... p) {
        for(auto it : slots_) {
            it.second(p...);
        }
    }

    Signal& operator=(Signal const& other) {
        disconnect_all();
    }

private:
    std::map<SlotId, std::function<void(Args...)>> slots_;
};

#endif /* MOD_SIGNAL_HPP */


#if 0   //main.cpp
#include <simme_mod_sig_slot.h>

class TestSig {
public:
    void slot(int id, std::string str) {
        std::cout << id << ", " << str << std::endl;
    }

    void const_slot(int id, std::string str) const {
        std::cout << id << ", " << str << std::endl;
    }
};

int main(int /*argc*/, char** /*argv*/) {
    Signal<int, std::string> iss;

    TestSig *pots = new TestSig;
    iss.connect(pots, &TestSig::const_slot);
    iss.emit(33, "Mee Mee");
    iss.disconnect(pots, &TestSig::const_slot);
    iss.emit(66, "Gee Gee");
}
#endif
