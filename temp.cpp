template <typename T>
bool f(T elem)
{
    return true;
}

template <>
bool f(void)
{
    return false;
}

int main()
{
    f (4);
    //f(void);---
}


int main() {}
