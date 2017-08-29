#ifndef __SIGNAL_HPP__
#define __SIGNAL_HPP__

#define JUCE_CALLASYNC_VER 0x30100

#if JUCE_APP_VERSION_HEX >= JUCE_CALLASYNC_VER
#include <JuceHeader.h>
#endif
#include <functional>
#include <map>
#include <set>

namespace Utils {

    enum class ConnectionType {
        DirectConnection = 0
#if JUCE_APP_VERSION_HEX >= JUCE_CALLASYNC_VER
        , QueuedConnection
#endif
    };

    template <typename... Args>
    class Signal {
    public:
        Signal() {}

        void connect(void(*func)(Args...), ConnectionType type = ConnectionType::DirectConnection) {
            connect(SlotId{ 0, reinterpret_cast<size_t>(*((void**)(&func))), type }, ([=](Args... args) {
                (*func)(args...);
            }));
        }

        template <typename T>
        void connect(void (T::*func)(Args...), ConnectionType type = ConnectionType::DirectConnection) {
            connect(SlotId{ 0, reinterpret_cast<size_t>(*((void**)(&func))), type }, ([=](Args... args) {
                (T::func)(args...);
            }));
        }

        template <typename T>
        void connect(T *inst, void (T::*func)(Args...), ConnectionType type = ConnectionType::DirectConnection) {
            connect(SlotId{ reinterpret_cast<size_t>(inst), reinterpret_cast<size_t>(*((void**)(&func))), type }, ([=](Args... args) {
                (inst->*func)(args...);
            }));
        }

        template <typename T>
        void connect(T *inst, void (T::*func)(Args...) const, ConnectionType type = ConnectionType::DirectConnection) {
            connect(SlotId{ reinterpret_cast<size_t>(inst), reinterpret_cast<size_t>(*((void**)(&func))), type }, ([=](Args... args) {
                (inst->*func)(args...);
            }));
        }

        void disconnect(void(*func)(Args...)) {
            disconnect(0, reinterpret_cast<size_t>(*((void**)(&func))));
        }

        template <typename T>
        void disconnect(T *inst, void (T::*func)(Args...)) {
            disconnect(reinterpret_cast<size_t>(inst), reinterpret_cast<size_t>(*((void**)(&func))));
        }

        template <typename T>
        void disconnect(T *inst, void (T::*func)(Args...) const) {
            disconnect(reinterpret_cast<size_t>(inst), reinterpret_cast<size_t>(*((void**)(&func))));
        }

        void disconnect_all() {
            slots_.clear();
        }

        void emit(Args... p) {
            if (m_blocked) return;
            for (auto it : slots_) {
#if JUCE_APP_VERSION_HEX >= JUCE_CALLASYNC_VER
                if (ConnectionType::QueuedConnection == it.first.m_connectionType) {
                    MessageManager::getInstance()->callAsync([=](){ it.second(p...); });
                    return;
                }
#endif
                it.second(p...);
            }

            for (auto sig : m_chainedSignals)
                sig->emit(p...);
        }

        void block() {
            m_blocked = true;
        }

        void unblock() {
            m_blocked = false;
        }

        void chain(Signal<Args...>& sig) {
            m_chainedSignals.insert(&sig);
        }

        void unchain(Signal<Args...>& sig) {
            m_chainedSignals.erase(&sig);
        }

        void unchain_all(Signal<Args...>& sig) {
            m_chainedSignals.clear();
        }

    private:
        struct SlotId {
            SlotId(size_t receiverId,
            size_t slotId)
            : m_receiverId(receiverId)
            , m_slotId(slotId) { }

            SlotId(size_t receiverId,
            size_t slotId,
            ConnectionType connectionType)
            : m_receiverId(receiverId)
            , m_slotId(slotId)
            , m_connectionType(connectionType) { }

            bool operator< (const SlotId &o) const {
                return (m_receiverId < o.m_receiverId) ? true : ((m_receiverId == o.m_receiverId) ? (m_slotId < o.m_slotId) : false);
            }

            size_t m_receiverId;
            size_t m_slotId;
            ConnectionType m_connectionType;
        };

        std::map<SlotId, std::function<void(Args...)>> slots_;
        std::set<Signal<Args...>*> m_chainedSignals;
        bool m_blocked = false;

        void connect(SlotId id, std::function<void(Args...)> func) {
            slots_.insert(std::make_pair(id, func));
        }

        void disconnect(size_t receiverId, size_t slotId) {
            slots_.erase(SlotId{ receiverId, slotId });
        }
    };

}

#endif //__SIGNAL_HPP__

#include<iostream>

class  Test
{
public:
     Test() {}

     static void slotFunc(int i = 9) {
        std::cout << i << std::endl;
     }
};

int main () {
    Utils::Signal<int> intSig;
    intSig.connect(Test::slotFunc);
    intSig.emit(4);
}
