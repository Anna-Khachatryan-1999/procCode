#include <iostream>
#include <vector>

template <std::size_t N>
class Bitset
{
public:
    Bitset();
    ~Bitset();
    Bitset(unsigned long long int);
    Bitset(const Bitset<N>& src);
    Bitset(Bitset<N>&& src);
public:
    Bitset& operator=(const Bitset<N>& rhs);
    Bitset& operator=(Bitset<N>&& rhs);
public:
    void set();
    void set(std::size_t index);
    void reset();
    void reset(std::size_t index);
    void flip();
    void flip(std::size_t index);
    friend std::ostream& operator<<(std::ostream& os, const Bitset& obj){
        char ch;
        std::string bits;
        std::string::iterator it = bits.begin();
        int bitsInIndex = N % 32;
        for (int i = 0; i <= obj.m_size; ++i) {
            int current = obj.m_arr[i];
            while (bitsInIndex != 0) {
                ch = (current % 2) ? '1' : '0';
                current /= 2;
                it = bits.insert(it, ch);
                --bitsInIndex;
            }
            it = bits.end();
            bitsInIndex = 32;
        }
        os << bits;
        return os;
    }
public:
    Bitset& operator|=(const Bitset<N>& lhs);
    Bitset& operator&=(const Bitset<N>& lhs);
    Bitset& operator^=(const Bitset<N>& lhs);
    Bitset operator~()const;
private:
    void help();
private:
    int m_size = N / 32;
    int* m_arr = new int[m_size + 1]{0};
    unsigned long long int m_number;
};

template <std::size_t N>
void Bitset<N>::help()
{
    for(int i = m_size; i >= 0; --i) {
        int count = 31, j = 0;
        while(j <= count) {
            m_arr[i] |= ((m_number % 2) << j);
            ++j;
            m_number /= 2;
        }
        if((i*(count+1) >= N) || m_number == 0) {
            break;
        }
    }
}

//////////////////Constructors////////////////////
template <std::size_t N>
Bitset<N>::Bitset()
{
    m_number = 0;
}

template <std::size_t N>
Bitset<N>::~Bitset()
{
    delete[] m_arr;
}

template <std::size_t N>
Bitset<N>::Bitset(unsigned long long int number): m_number{number}
{
    help();
}

template <std::size_t N>
Bitset<N>::Bitset(const Bitset<N>& src)
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] = src.m_arr[i];
    }
}

template <std::size_t N>
Bitset<N>::Bitset(Bitset<N>&& src)
{
    m_arr = src.m_arr;
    src.m_arr = nullptr;
}

////////////////////Assignment Operators//////////////////
template <std::size_t N>
Bitset<N>& Bitset<N>::operator=(const Bitset<N>& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] = rhs.m_arr[i];
    }
    return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator=(Bitset<N>&& rhs)
{
    m_arr = rhs.m_arr;
    rhs.m_arr = nullptr;
    return *this;
}

////////////////////Modifiers//////////////////
template <std::size_t N>
void Bitset<N>::set()
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] = ~0;
    }
}

template <std::size_t N>
void Bitset<N>::set(std::size_t index)
{
    m_arr[N/32] |= (1 << index);
}


template <std::size_t N>
void Bitset<N>::reset()
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] = 0;
    }
}

template <std::size_t N>
void Bitset<N>::reset(std::size_t index)
{
    m_arr[N/32] &= (~(1 << index));
}

template <std::size_t N>
void Bitset<N>::flip()
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] = ~m_arr[i];
    }
}

template <std::size_t N>
void Bitset<N>::flip(std::size_t index)
{
    m_arr[N/32] ^= (1 << index);
}

//////////////////operators////////////////////
template <std::size_t N>
Bitset<N>& Bitset<N>::operator|=(const Bitset<N>& lhs)
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] |= lhs.m_arr[i];
    }
    return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator&=(const Bitset<N>& lhs)
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] &= lhs.m_arr[i];
    }
    return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator^=(const Bitset<N>& lhs)
{
    for(int i = 0; i <= m_size; ++i) {
        m_arr[i] ^= lhs.m_arr[i];
    }
    return *this;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator~() const
{
    Bitset<N> current = (*this);
    current.flip();
    return current;
}


//////////////////Non-member functions////////////////////
template< std::size_t N >
Bitset<N> operator&(const Bitset<N>& lhs, const Bitset<N>& rhs)
{
    Bitset<N> current = lhs;
    current &= rhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator&(const Bitset<N>& lhs, unsigned long long int rhs)
{
    Bitset<N> current = {rhs};
    current &= lhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator&(unsigned long long int rhs, const Bitset<N>& lhs)
{
    Bitset<N> current = {rhs};
    current &= lhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator|(const Bitset<N>& lhs, const Bitset<N>& rhs)
{
    Bitset<N> current = lhs;
    current |= rhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator|(const Bitset<N>& lhs, unsigned long long int rhs)
{
    Bitset<N> current = {rhs};
    current |= lhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator|(unsigned long long int rhs, const Bitset<N>& lhs)
{
    Bitset<N> current = {rhs};
    current |= lhs;
    return current;
}


template< std::size_t N >
Bitset<N> operator^(const Bitset<N>& lhs, const Bitset<N>& rhs)
{
    Bitset<N> current = lhs;
    current ^= rhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator^(const Bitset<N>& lhs, unsigned long long int rhs)
{
    Bitset<N> current = {rhs};
    current ^= lhs;
    return current;
}

template< std::size_t N >
Bitset<N> operator^(unsigned long long int rhs, const Bitset<N>& lhs)
{
    Bitset<N> current = {rhs};
    current ^= lhs;
    return current;
}

int main()
{
    unsigned long long int x = 1;
    Bitset<4> b(x);
    b.set(3);
    std::cout << b << std::endl;
    Bitset<4> b2 = (12);
    std::cout << b2 << std::endl;
    b2 &= b;
    std::cout << b2 << std::endl;
    Bitset<4> b3 = b2 & b;
    std::cout << b3 << std::endl;
    Bitset<4> b4 = ~b3;
    std::cout << b4 << std::endl;
    Bitset<37> b5 = Bitset<37>{12};
    std::cout << b5 << std::endl;
    b5.set(16);
    std::cout << b5 << std::endl;
    b5 = b5 & 0;
    std::cout << b5 << std::endl;
}
