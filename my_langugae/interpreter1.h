#include <string>
#include <fstream>
#include <vector>

struct Variable
{
    std::string type;
    std::string variable;
    std::string value;
};

class Parser
{
public:
    Parser(const char* str);
   ~Parser() = default;
private:
    void pars_token();
    void pars(std::vector<Variable>& variable, bool temp = true);
    void parsTemproryIfOrFor(int& index, std::vector<Variable>& m_variable);
    void input(bool temp = true);
    void output(bool temp = true);
    void variableStatement(std::vector<Variable>& m_variable, bool temp = true);
    void withoutTypeVariable(bool temp = true);
    void print();
private:
    bool isNumberI(const std::string&) const;
    bool isNumberD(std::string&);
    bool isSimbol(const std::string&) const;
    bool isKey(const std::string& str) const;
    bool haveVariable(const std::string&) const;
    bool haveVariableInStaticVector (const std::string&) const;
    std::string getValueHaveVariable (const std::string&) const;
    std::string getValueHaveVariableStatic (const std::string&) const;
    void changeValue(const std::string& str_name, std::string& str_value, bool temp = true);
    std::string cinRightValu(const std::string&);
    std::string rightValu(const std::string& type, std::string value, bool temp = true);
    std::string calculate (const char signOfAction, std::string nameRvalu1, std::string nameRvalu2, bool temp = true);
    double helperOperations (const char, double, double);
    int indexCloseScope(int indexOpenScope);
    std::string operation(int index, bool temp = true);
    double helpExpression(std::string str, bool temp = true);
    bool expression(std::string loperand, std::string operation, std::string roperand, bool temp = true);
    int operationSign() const;
    bool condition(bool temp = true);
    void conditionAndLoop();
    void helpCoditionAndLoop (int& index);
private:
    std::string m_str;
    std::vector<Variable> m_variable;
    std::vector<std::string> m_token;
    std::vector<std::string> temproryLine;
    static std::vector<Variable> s_variable;
    //std::vector<Variable> t_variable;
    std::fstream m_fstr;
    bool temprorybool = false;
};
