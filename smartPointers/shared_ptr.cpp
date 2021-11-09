#include "shared_ptr.h"
#include <iostream>
#include <exception>

namespace sptr
{
    template <typename T>
    Shared_ptr<T>::Shared_ptr()
    {
        m_ptr = nullptr;
    }

    template <typename T>
    Shared_ptr<T>::Shared_ptr(T* ptr) noexcept
    {
        m_block = new ControlBlock<>();
        m_ptr = ptr;
        m_block->RC++;
    }

    template <typename T>
    Shared_ptr<T>::Shared_ptr(const Shared_ptr<T>& src) noexcept
    {
        if (src.m_ptr != nullptr) {
            m_ptr = src.m_ptr;
            m_block = src.m_block;
            m_block->RC++;
        }
    }

/*    template <typename T>
    Shared_ptr<T>::Shared_ptr(T* ptr, std::function<void(T*)> deleter)
    {
        m_block = new ControlBlock();
        m_ptr = ptr;
        m_block->RC++;
        m_block->deleter = deleter;
    }*/

    template <typename T>
    Shared_ptr<T>::Shared_ptr(Shared_ptr<T>&& src) noexcept
    {
        if (src.m_ptr != nullptr) {
            m_block = src.m_block;
            m_ptr = src.m_ptr;
            src.m_block = nullptr;
            src.m_ptr = nullptr;
        }
    }

    template <typename T>
    Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<T>& rhs) noexcept
    {
        if (rhs.m_ptr == m_ptr) {
            return *this;
        }
        if (rhs.m_ptr != nullptr)
        {
            m_block->RC--;
            if (m_block->RC == 0) {
                delete m_ptr;
            }
            m_ptr = rhs.m_ptr;
            m_block = rhs.m_block;
            m_block->RC++;
        }
        return *this;
    }

    template <typename T>
    Shared_ptr<T>& Shared_ptr<T>::operator=(Shared_ptr<T>&& rhs) noexcept
    {
        if (rhs.m_ptr == m_ptr) {
            return *this;
        }
        if (rhs.m_ptr != nullptr)
        {
            m_block->RC--;
            if (m_block->RC == 0) {
                delete m_ptr;
            }
            m_ptr = rhs.m_ptr;
            m_block = rhs.m_block;
            rhs.m_ptr = nullptr;
            rhs.m_block = nullptr;
        }
        return *this;
    }

    template <typename T>
    void Shared_ptr<T>::swap(Shared_ptr<T>& r) noexcept
    {
        std::swap(m_ptr, r.m_ptr);
        std::swap(m_block, r.m_block);
    }


    template <typename T>
    T* Shared_ptr<T>::get() const noexcept
    {
        return m_ptr;
    }

    template <typename T>
    T& Shared_ptr<T>::operator*() noexcept
    {
        return *m_ptr;
    }

    template <typename T>
    T* Shared_ptr<T>::operator->() const noexcept
    {
        return m_ptr;
    }

    template <typename T>
    void Shared_ptr<T>::reset() noexcept
    {
        helpDelete();
    }

    template <typename T>
    void Shared_ptr<T>::reset(T* ptr)
    {
        helpDelete();
        if (ptr != nullptr) {
            m_block = new ControlBlock<>();
            m_ptr = ptr;
        } else {
            throw std::invalid_argument(R"(error: no matching function for call to
                                          'Shared_ptr<Foo>::reset(std::nullptr_t)')");
        }
    }

    template <typename T>
    Shared_ptr<T>::~Shared_ptr()
    {
        if (m_ptr != nullptr && m_block->deleter != nullptr) {
            m_block->deleter(m_ptr);
            return;
        }
        helpDelete();
    }

    template <typename T>
    unsigned long Shared_ptr<T>::use_count() const noexcept
    {
        if (m_block == nullptr) {
            return 0;
        }
        return m_block->RC;
    }

    template <typename T>
    bool Shared_ptr<T>::unique() const noexcept
    {
        if (m_block == nullptr || m_block->RC != 1) {
            return false;
        }
        return true;
    }

    template <typename T>
    Shared_ptr<T>::operator bool() const noexcept
    {
        return bool(m_ptr);
    }


    template <typename T>
    void Shared_ptr<T>::helpDelete() {
        if (m_ptr != nullptr) {
            --m_block->RC;
            if (m_block->RC == 0) {
                delete m_ptr;
            }
            m_ptr = nullptr;
        }
    }
}

void deleter(int * p)
{
    std::cout << "deleter " << std::endl;
}

int delet(int* p) {
    std::cout << "return type 'int'" << std::endl;
    return 0;
}

int main()
{
    sptr::Shared_ptr<int> sh (new int());
    *sh = 12;
    sptr::Shared_ptr<int> sh1 (sh);
    *sh1 = 23;
    std::cout << *sh << std::endl;
    sptr::Shared_ptr<int> sh2 (std::move(sh));
    std::cout << *sh1 << std::endl;
    std::cout << *sh2 << std::endl;
    sptr::Shared_ptr<int> sh3 (std::move(new int()));
    sh3 = std::move(sh3);
    std::cout << *sh3 << std::endl;
    sptr::Shared_ptr<int> sptr(new int, deleter);
    *sptr = 1;
    std::cout << *sptr << "\n";

    sptr::Shared_ptr<int> sptr1(sptr);
    sptr.reset();
    std::cout << *sptr1 << "\n";
    sptr::Shared_ptr<int> sptr2(nullptr);
    sptr.reset(new int);
    std::cout << *sptr << "\n";

    if (sptr2) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
    sptr.swap(sptr2);
    std::cout << *sptr2 << "\n" << sptr2.get() << "\n";
    //std::cout << *sptr << "\n"; //error segmentation fault -> sptr == nullptr
    //sptr.reset(nullptr);   //error ^_^
    sptr::Shared_ptr<int> sptr5(new int, [](int* ptr) {
            std::cout << *ptr << std::endl;});
    sptr::Shared_ptr<int> newInt(new int, delet);
    return 0;
}
