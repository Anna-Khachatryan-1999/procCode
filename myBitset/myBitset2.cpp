#include <iostream>
#include <string>
#include <vector>

template <std::size_t N>

class Bitset
{
public:
    Bitset();
    Bitset(const std::string& number, char zero = '0', char one = '1');
    Bitset(unsigned long long int value);
    Bitset(const Bitset&);
    Bitset(Bitset&&);
    Bitset& operator=(const Bitset&);
    Bitset& operator=(Bitset&&);
    ~Bitset();
public:
    std::vector<bool>::reference operator[](std::size_t index);
    Bitset operator|(Bitset<N> lhs);
    Bitset operator&(Bitset<N> lhs);
    Bitset operator^(Bitset<N> lhs);
    friend std::ostream& operator<<(std::ostream& os, const Bitset& b){
        for (int i = 0; i < N; ++i) {
            os << b.m_bits[i];
        }
        return os;
    }
public:
    Bitset<N>& operator|=(Bitset<N> lhs);
    Bitset<N>& operator&=(Bitset<N> lhs);
    Bitset<N>& operator^=(Bitset<N> lhs);
public:
    void set();
    void set(std::size_t index);
    void reset();
    void reset(std::size_t index);
    void flip();
    void flip(std::size_t index);
public:
    std::string to_string (char zero = '0', char one = '1');
public:
    std::size_t size() const;
    void print() const;
protected:
    std::vector<bool> m_bits;
};

template <std::size_t N>
Bitset<N>::Bitset() : m_bits{0}
{ }

template <std::size_t N>
Bitset<N>::Bitset(unsigned long long int value)
{
    for(int i = 0; i < N; ++i) {
        m_bits.insert(m_bits.begin(), value % 2);
        value /= 2;
    }
}

template <std::size_t N>
Bitset<N>::Bitset(const std::string& number, char zero, char one)
{
    for (int i = number.size() - 1; i >= 0; --i) {
        if (number[i] == zero) {
            m_bits.insert(m_bits.begin(), 0);
        } else if (number[i] == one) {
            m_bits.insert(m_bits.begin(), 1);
        } else {
            std::cout << "error: invalid_argument" << std::endl;
            abort();
        }
    }
    for (int i = number.size(); i < N; ++i) {
        m_bits.insert(m_bits.begin(), 0);
    }
}

template <std::size_t N>
Bitset<N>::~Bitset() {}

template <std::size_t N>
Bitset<N>::Bitset(const Bitset& src)
{
    m_bits = src.m_bits;
}

template <std::size_t N>
Bitset<N>::Bitset(Bitset&& src)
{
    m_bits = src.m_bits;
    src.~Bitset();
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator=(const Bitset& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    m_bits = rhs.m_bits;
    return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator=(Bitset&& rhs)
{
    m_bits = rhs.m_bits;
    rhs.~Bitset();
    return *this;
}

template <std::size_t N>
void Bitset<N>::set()
{
    for (int i = 0; i < N; ++i) {
        m_bits[i] = 1;
    }
}

template <std::size_t N>
void Bitset<N>::set(std::size_t index)
{
    m_bits[N-index-1] = 1;
}

template <std::size_t N>
void Bitset<N>::reset()
{
    for (int i = 0; i < N; ++i) {
        m_bits[i] = 0;
    }
}

template <std::size_t N>
void Bitset<N>::reset(std::size_t index)
{
    m_bits[N-index-1] = 0;
}

template <std::size_t N>
void Bitset<N>::flip()
{
    for (int i = 0; i < N; ++i) {
        m_bits[i] = !m_bits[i];
    }
}

template <std::size_t N>
void Bitset<N>::flip(std::size_t index)
{
    m_bits[N-index-1] = !(m_bits[N-index-1]);
}

template <std::size_t N>
std::size_t Bitset<N>::size() const
{
    return N;
}

template <std::size_t N>
void Bitset<N>::print() const
{
    for (int i = 0; i < N; ++i) {
        std::cout << m_bits[i];
    }
    std::cout << std::endl;
}

template <std::size_t N>
std::vector<bool>::reference Bitset<N>::operator[](std::size_t index)
{
    return m_bits[index];
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator|(Bitset<N> lhs)
{
    Bitset<N> current;
    for (int i = 0; i < N; ++i) {
        current[i] = (lhs[i] | m_bits[i]);
    }
    return current;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator&(Bitset<N> lhs)
{
    Bitset<N> current;
    for (int i = 0; i < N; ++i) {
        current[i] = (lhs[i] & m_bits[i]);
    }
    return current;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator^(Bitset<N> lhs)
{
    Bitset<N> current;
    for (int i = 0; i < N; ++i) {
        current[i] = (lhs[i] ^ m_bits[i]);
    }
    return current;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator|=(Bitset<N> lhs)
{
    for (int i = 0; i < N; ++i) {
        m_bits[i] = (lhs[i] | m_bits[i]);
    }
    return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator&=(Bitset<N> lhs)
{
    for (int i = 0; i < N; ++i) {
        m_bits[i] = (lhs[i] & m_bits[i]);
    }
    return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator^=(Bitset<N> lhs)
{
    for (std::size_t i = 0; i < N; ++i) {
        m_bits[i] = (lhs[i] ^ m_bits[i]);
    }
    return *this;
}

template <std::size_t N>
std::string Bitset<N>::to_string (char zero, char one)
{
    std::string str;
    for (int i = 1; i < N; ++i) {
        if (m_bits[i] == 0) {
            str += zero;
        } else if (m_bits[i] == 1) {
            str += one;
        }
    }
    return str;
}


int main()
{
    Bitset<8> b1;
    b1.print();
    b1.set(5);
    b1.print();
    Bitset<8> b2 = (12);
    b2.print();
    b2.flip();
    b2.print();
    Bitset<8> b3 = {"AbAAAb", 'A', 'b'};
    b3.print();
    b3 ^ b2;
    b3 ^ Bitset<8>{12};
    b3 ^= Bitset<8>{12};
    b3.print();
    std::cout << b3 << std::endl;
    return 0;
}
