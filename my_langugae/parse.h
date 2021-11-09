#include <string>

struct Variable
{
    std::string type;
    std::string variable;
    std::string value;
};

class Parse
{
public:
    Parse() = default;
    ~Parse() = default;
public:
    void parsing();
private:
    std::vector<Variable> v;
    std::vector<std::string> token;
};

