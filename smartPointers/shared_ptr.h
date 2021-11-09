#ifndef SHARED_PTR
#define SHARED_PTR

#include <iostream>
#include <functional>

namespace sptr{

    /*template <typename T>
    struct ControlBlock
    {
        unsigned long RC{0};
        std::function<void(T*)> deleter = nullptr;
    };
*/
template <typename T>
    class Shared_ptr
    {
    private:
        template <class Deleter = void(*)(T*)>
        struct ControlBlock
        {
            unsigned long RC{0};
            //std::function<void(T*)> deleter = nullptr;
            Deleter deleter = nullptr;
        };


    public:
        //constructs new shared_ptr
        Shared_ptr();
        constexpr Shared_ptr(std::nullptr_t) noexcept{};
        Shared_ptr(T* ptr) noexcept;
        template <class Deleter = void(*)(T*)>
        Shared_ptr(T* ptr, Deleter deleter) {
            m_block = new ControlBlock<>();
            m_ptr = ptr;
            m_block->RC++;
            m_block->deleter = deleter;
        }
     //   Shared_ptr(T* ptr, std::function<void(T*)> deleter);
        Shared_ptr(const Shared_ptr<T>& src) noexcept;
        Shared_ptr(Shared_ptr<T>&& src) noexcept;
        //destructs the owned object if no more shared_ptrs link to it
        ~Shared_ptr();
        //assigns the shared_ptr
        Shared_ptr<T>& operator=(const Shared_ptr<T>& rhs) noexcept;
        Shared_ptr<T>& operator=(Shared_ptr<T>&& rhs) noexcept;

    public:
        //replaces the managed object
        void reset() noexcept;
        void reset(T* ptr);
        //swaps the managed objects
        void swap(Shared_ptr<T>& r) noexcept;

    public:
        //returns the stored pointer
        T* get() const noexcept;
        //dereferences the stored pointer
        T& operator*() noexcept;
        T* operator->() const noexcept;
        //returns the number of shared_ptr objects referring to the same managed object
        unsigned long use_count() const noexcept;
        //checks whether the managed object is managed only by the current shared_ptr instance
        bool unique() const noexcept;
        //checks if the stored pointer is not null
        explicit operator bool() const noexcept;

    private:
        void helpDelete();

    private:
        T* m_ptr = nullptr;
        ControlBlock<>* m_block = nullptr;
    };
}
#endif //SHARED_PTR
