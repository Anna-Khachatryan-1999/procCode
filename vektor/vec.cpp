#include <iostream>
#include <vector>

template <typename T>
void print(std::vector<T> out)
{
    for(int i = 0; i < out.size(); ++i) {
        std::cout << out[i] << " ";
    }
    std::cout << std::endl;

}

void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}

int main()
{
    std::cout << "\n################# constructors, assignment operators ###############" << std::endl;
    std::vector<int> v1;
    std::cout << "v1: ";
    print(v1);

    std::vector<int> v2 = {1, 2, 3, 4, 5};
    std::cout << "v2: ";
    print(v2);

    std::vector<std::string> v3(5, "hi");
    std::cout << "v3: ";
    print(v3);

    std::vector<std::string> v4(v3);
    std::cout << "v4: ";
    print(v4);

    std::vector<int> v5(v2.begin(), v2.end());
    std::cout << "v5: ";
    print(v5);

    v1 = v2;
    std::cout << "v1: ";
    print(v1);

    v3 = {"I", "am", "Ann"};
    std::cout << "v3: ";
    print(v3);

    std::cout << "\n################# element access  ###############" << std::endl;
    v1.at(3) = 88; //with bounds checking.
    v1[0] = 65;    //No bounds checking is performed.
    std::cout << "v1: ";
    print(v1);

    std::cout << "\n################# front,back ###############" << std::endl;
    std::vector<char> letters {'o', 'm', 'g', 'w', 't', 'f'};
    if (!letters.empty()) {
        std::cout << "The first character is '" << letters.front() << "'.\n";
        std::cout << "The last character is '" << letters.back() << "'.\n";
    }

    std::cout << "\n################# data ###############" << std::endl;
    pointer_func(v1.data(), v1.size());
    std::vector<std::string> fruits {"orange", "apple", "raspberry"};
    if (!fruits.empty()) {
        std::cout << "First fruit: " << *fruits.begin() << '\n';
        std::cout << "rbegin fruit: " << *fruits.rbegin() << '\n';
    }

    std::cout << "\n################# size, max_size, resize, clear, shrink_to_fit ###############" << std::endl;
    std::vector<char> s = {'c'};
    std::cout << "Size of a 'vector' is " << s.size() << "\n";
    std::cout << "Maximum size of a 'vector' is " << s.max_size() << "\n";

    std::vector<int> v;
    std::cout << "Default-constructed capacity is " << v.capacity() << '\n';
    v.resize(100);
    v.push_back(1);
    std::cout << "Capacity after resize(50) is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
    v.clear();
    std::cout << "Capacity after clear() is " << v.capacity() << '\n';

    std::cout << "\n################# insert ###############" << std::endl;
    std::vector<int> vec(3,100);
    print(vec);

    auto it = vec.begin();
    it = vec.insert(it, 200);
    print(vec);

    vec.insert(it,2,300);
    print(vec);

    it = vec.begin();

    std::vector<int> vec2(2,400);
    vec.insert(it+2, vec2.begin(), vec2.end());
    print(vec);

    int arr[] = { 501,502,503 };
    vec.insert(vec.begin(), arr, arr+3);
    print(vec);

    std::cout << "\n################# erase ###############" << std::endl;
    std::vector<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print(c);

    c.erase(c.begin());
    print(c);

    c.erase(c.begin()+2, c.begin()+5);
    print(c);

    for (auto it = c.begin(); it != c.end(); ) {
        if (*it % 2 == 0) {
            it = c.erase(it);
        } else {
            ++it;
        }
    }
    print(c);

    std::cout << "\n################# swap ###############" << std::endl;
    std::vector<int> a1{1, 2, 3}, a2{4, 5};

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int& ref1 = a1.front();
    int& ref2 = a2.front();

    a1.swap(a2);
    std::cout << "a1: ";
    print(a1);
    std::cout << "a2: ";
    print(a2);
}
