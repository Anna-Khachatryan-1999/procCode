#include <iostream>
#include "interpreter1.h"

std::vector<Variable> Parser::s_variable;

Parser::Parser(const char* str) : m_fstr {str}
{
    if (!m_fstr.is_open()) {
        std::cout << "cann't open file" << std::endl;
        abort();
    }
    int count = 0;
    while(std::getline(m_fstr, m_str)) {
        if (m_str.find("#") == 0) continue;
        std::size_t found = m_str.find("#");
        if (found!=std::string::npos) {
            m_str = m_str.substr (0, found);
        }
        if (m_str == "") continue;
        if (m_str.find ("ete") == 0 || m_str.find ("cikl") == 0) {
            temprorybool = true;
        }
        if (temprorybool) {
            temproryLine.push_back(m_str);
            if (m_str.find("->") !=std::string::npos && m_str.find("elq")==std::string::npos) {
                ++count;
            }
            if (m_str.find("<-")!=std::string::npos && m_str.find("mutq") ==std::string::npos) {
                --count;
            }
            if (count == 0) {
                conditionAndLoop();
            }
        } else {
            pars(m_variable);
            m_token.clear();
        }
    }
}

void Parser::helpCoditionAndLoop (int& index) {
    ++index;
   while (temproryLine[index].find("<-") == std::string::npos &&
           temproryLine[index].find("mutq")==std::string::npos) {
    if (temproryLine[index].find("->") != std::string::npos &&
            temproryLine[index].find("elq")==std::string::npos) {
        helpCoditionAndLoop(index);
    }
       ++index;
    }
    ++index;
}

void Parser::conditionAndLoop()
{
    print();
    m_str = temproryLine[0];
    pars_token();
    if (m_token[0] == "ete" || m_token[0] == "cikl") {
        int index = 0;
        std::vector<Variable> t_variable;
        parsTemproryIfOrFor(index, t_variable);
    } else {
        std::cout << "incomprehensible expression" << std::endl;
        abort();
    }
    m_token.clear();
    temprorybool = false;
    temproryLine.clear();
}

void Parser::parsTemproryIfOrFor(int& index, std::vector<Variable>& t_variable)
{
    while (index < temproryLine.size()) {
        m_token.clear();
        m_str = temproryLine[index];
        pars_token();
        if (m_token[0] != "<-") {
            if (m_token[0] == "ete") {
                if (condition(false)) {
                        std::vector<Variable> t_variable;
                    m_token.clear();
                    ++index;
                    parsTemproryIfOrFor(index, t_variable);
                } else {
                    helpCoditionAndLoop(index);
                }
                m_token.clear();
            } else if (m_token[0] == "cikl") {
                    int index1 = index;
                if (condition(false)) {
                    while (condition(false)) {
                        std::vector<Variable> t_variable;
                        m_token.clear();
                        index = index1 + 1;
                        parsTemproryIfOrFor(index, t_variable);
                        m_token.clear();
                        m_str = temproryLine[index1];
                        pars_token();
                    }
                } else {
                    helpCoditionAndLoop(index);
                }
                m_token.clear();
            } else {
                m_token.clear();
                pars(t_variable, false);
                ++index;
                m_token.clear();
            }
        } else {
            for (int i = 0; i < t_variable.size(); ++i) {
                s_variable.pop_back();
                t_variable.pop_back();
            }
            t_variable.clear();
            ++index;
            return;
        }
    }
}

void Parser::print()
{
    for (int i = 0; i < temproryLine.size(); i++) {
        std::cout << temproryLine[i] << "  " << i << std::endl;
    }
}

bool Parser::isNumberI(const std::string& str) const
{
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] < '0' || str[i] > '9') {
            if ((str[i] == '-') && (i == 0)) {
                continue;
            }
            return false;
        }
    }
    return true;
}

bool Parser::isNumberD(std::string& str)
{
    int i = 0;
    bool bool_t = true;
    for (; i < str.size(); ++i) {
        if (str[i] == '.') {
            if(i == 0) {
                str.insert(0, "0");
                ++i;
            }
            bool_t = false;
            break;
        } else if (str[i] < '0' || str[i] > '9') {
            if ((str[i] == '-') && (i == 0)) {
                continue;
            }
            return false;
        }
    }
    for (++i; i < str.size(); ++i) {
         if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    if (bool_t) {
        str += ".0";
    }
    return true;
}

bool Parser::isSimbol (const std::string& str) const
{
    if(str.size() == 3 && str[0] == '<' && str[2] == '>') {
        return true;
    }
    return false;
}

bool Parser::isKey (const std::string& str) const
{
    if (str == "tivI" || str == "tivD" || str == "sim" || str == "bul") {
        return true;
    }
    return false;
}

bool Parser::haveVariable(const std::string& str) const
{
    for (int i = 0; i < m_variable.size(); ++i) {
        if (m_variable[i].variable == str) {
            return true;
        }
    }
    return false;
}

bool Parser::haveVariableInStaticVector(const std::string& str) const
{
    for (int i = 0; i < s_variable.size(); ++i) {
        if (s_variable[i].variable == str) {
            return true;
        }
    }
    return false;
}

std::string Parser::getValueHaveVariable (const std::string& str) const
{
    for (int i = 0; i < m_variable.size(); ++i) {
        if (m_variable[i].variable == str) {
            return m_variable[i].value;
        }
    }
    return " ";
}

std::string Parser::getValueHaveVariableStatic (const std::string& str) const
{
    for (int i = 0; i < s_variable.size(); ++i) {
        if (s_variable[i].variable == str) {
            return s_variable[i].value;
        }
    }
    return " ";
}

void Parser::changeValue(const std::string& str_name, std::string& str_value, bool temp)
{
    for (int i = 0; i < m_variable.size(); ++i) {
        if (m_variable[i].variable == str_name) {
            m_variable[i].value = rightValu(m_variable[i].type, str_value, temp);
        }
    }
    if (!temp) {
        for (int i = 0; i < s_variable.size(); ++i) {
            if (s_variable[i].variable == str_name) {
                s_variable[i].value = rightValu(s_variable[i].type, str_value, temp);
            }
        }
    }
}

std::string Parser::cinRightValu(const std::string& str)
{
    for (int i = 0; i < m_variable.size(); ++i) {
        if (m_variable[i].variable == str) {
            if (m_variable[i].type == "tivI") {
                int integer;
                std::cin >> integer;
                return std::to_string(integer);
            } else if (m_variable[i].type == "tivD") {
                double doubles;
                std::cin >> doubles;
                return std::to_string(doubles);
            } else if (m_variable[i].type == "bul") {
                bool bools;
                std::cin >> bools;
                return std::to_string(bools);
            } else if (m_variable[i].type == "sim") {
                char simvols;
                std::cin >> simvols;
                return std::to_string(simvols);
            }
        }
    }
    return " ";
}

std::string Parser::rightValu(const std::string& type, std::string value, bool temp)
{
    if (type == "tivI") {
        if (isNumberI(value)) {
            return value;
        } else if (isNumberD(value)) {
            std::size_t pos = value.find(".");
            return value.substr(0, pos);
        } else if (isSimbol(value)) {
            int current = value[1];
            return std::to_string(current);
        } else if (value == "true") {
            return "1";
        } else if (value == "false") {
            return "0";
        } else if (!temp && haveVariableInStaticVector(value)) {
            std::string current = getValueHaveVariableStatic(value);
            return rightValu (type, current, temp);
        } else if (haveVariable(value)) {
            std::string current = getValueHaveVariable(value);
            return rightValu (type, current, temp);
        } else {
            std::cout << "inappropriate value" << std::endl;
            abort();
        }
    } else if (type == "tivD") {
        if (isNumberD (value)) {
            return value;
        } else if (isSimbol(value)) {
            double current = value[1];
            return std::to_string(current);
        } else if (value == "true") {
            return "1.000000";
        } else if (value == "false") {
            return "0.000000";
        } else if (!temp && haveVariableInStaticVector(value)) {
            std::string current = getValueHaveVariableStatic(value);
            return rightValu (type, current, temp);
        } else if (haveVariable(value)) {
            std::string current = getValueHaveVariable(value);
            return rightValu (type, current, temp);
        } else {
            std::cout << "inappropriate value" << std::endl;
            abort();
        }
    } else if (type == "bul") {
        if (isNumberI(value)) {
            return (value != "0") ? "1" : "0";
        } else if (isNumberD(value)) {
            double current = stod(value);
            return (current > 0) ? "1" : "0";
        } else if (isSimbol(value)) {
            bool current = value[1];
            return std::to_string(current);
        } else if (value == "true") {
            return "1";
        } else if (value == "false") {
            return "0";
        } else if (!temp && haveVariableInStaticVector(value)) {
            std::string current = getValueHaveVariableStatic(value);
            return rightValu (type, current, temp);
        } else if (haveVariable(value)) {
            std::string current = getValueHaveVariable(value);
            return rightValu (type, current, temp);
        } else {
            std::cout << "inappropriate value" << std::endl;
            abort();
        }
    } else {
        if (isNumberI(value) || isNumberD(value)) {
            int current = stoi(value);
            char currentToChar = current;
            return std::string(1, currentToChar);
        } else if (isSimbol(value)) {
            return value;
        } else if (value == "true") {
            char current = int(1);
            return std::string(1, current);
        } else if (value == "false") {
            char current = int(0);
            return std::string(1, current);
            return "0";
        } else if (!temp && haveVariableInStaticVector(value)) {
            std::string current = getValueHaveVariableStatic(value);
            return rightValu (type, current, temp);
        } else if (haveVariable(value)) {
            std::string current = getValueHaveVariable(value);
            return rightValu (type, current, temp);
        } else {
            std::cout << "inappropriate value" << std::endl;
            abort();
        }
    }
}


std::string Parser::calculate(const char signOfAction, std::string nameRvalu1, std::string nameRvalu2, bool temp)
{
    double current1= 0;
    double current2 = 0;
    if (isNumberI(nameRvalu1) || isNumberD (nameRvalu1)) {
        current1 = std::stod(nameRvalu1);
    } else if (nameRvalu1 == "true") {
        current1 = 1;
    } else if (nameRvalu1 == "false") {
        current1 = 0;
    } else if (isSimbol(nameRvalu1)) {
        current1 = nameRvalu1[1];
    } else if (!temp && haveVariableInStaticVector(nameRvalu1)) {
        std::string current = getValueHaveVariableStatic(nameRvalu1);
        current1 = std::stod(rightValu("tivD", current, temp));
    } else if (haveVariable(nameRvalu1)) {
        std::string current = getValueHaveVariable(nameRvalu1);
        current1 = std::stod(rightValu("tivD", current, temp));
    } else {
        std::cout << "an unknown variable has been displayed" << std::endl;
        abort();
    }
    if (isNumberI(nameRvalu2) || isNumberD (nameRvalu2)) {
        current2 = std::stod(nameRvalu2);
    } else if (nameRvalu2 == "true") {
        current2 = 1;
    } else if (nameRvalu2 == "false") {
        current2 = 0;
    } else if (isSimbol(nameRvalu2)) {
        current2 = nameRvalu2[1];
    } else if (!temp && haveVariableInStaticVector(nameRvalu1)) {
        std::string current = getValueHaveVariableStatic(nameRvalu1);
        current1 = std::stod(rightValu("tivD", current, temp));
    } else if (haveVariable(nameRvalu2)) {
        std::string current = getValueHaveVariable(nameRvalu2);
        current2 = std::stod(rightValu("tivD", current, temp));
    } else {
        std::cout << "an unknown variable has been displayed" << std::endl;
        abort();
    }
    return std::to_string(helperOperations (signOfAction, current1, current2));
}

double Parser::helperOperations(const char sign, double elem1, double elem2)
{
    switch(sign)
    {
        case '+':
            return elem1 + elem2;
        case '-':
            return elem1 - elem2;
        case '*':
            return elem1 * elem2;
        case '/':
            return elem1 / elem2;
        case '%':
            return ((int)elem1 % (int)elem2) ;
        default:
            {
                std::cout << "ml language does not support" << sign << "operation" << std::endl;
                abort();
            }
    }
}

int Parser::indexCloseScope(int indexOpenScope)
{
    int count = 0;
    for (int i = indexOpenScope; i < m_token.size(); ++i) {
        if (m_token[i] == "(") {
            ++count;
        } else if (m_token[i] == ")") {
            --count;
        }
        if (count == 0) {
            return i;
        }
    }
    return -1;
}

std::string Parser::operation(int index, bool temp)
{
    if (m_token[index + 1] == "(") {
        int first = indexCloseScope(index + 1);
        std::string second = m_token[first + 2];
        if (m_token[first + 2] == "(") {
            second = operation(first + 2, temp);
        }
        return calculate (m_token[first + 1][0], operation(index + 1, temp), second, temp);
    } else {
        std::string second = m_token[index + 3];
        if (m_token[index + 3] == "(") {
            second = operation(index + 3, temp);
        }
        return calculate(m_token[index + 2][0], m_token[index + 1], second, temp);
    }
}

double Parser::helpExpression(std::string str, bool temp) {
    double current;
    if(isNumberI(str) || isNumberD(str)) {
        current = stod(str);
    } else if (str == "true") {
        current = 1.0000000;
    } else if (str == "false") {
        current = 0.0000000;
    } else if (str[0] == '<' && str[2] == '>') {
        current = str[1];
    } else if (!temp && haveVariableInStaticVector(str)) {
        current = std::stod(rightValu("tivD", str, temp));
    } else if (haveVariable(str)) {
        current = std::stod(rightValu("tivD", str, temp));
    } else {
        std::cout << "unknown variable" << std::endl;
        abort();
    }
    return current;
}

bool Parser::expression(std::string loperand, std::string operation, std::string roperand, bool temp)
{
    double first = helpExpression(loperand, temp);
    double second = helpExpression(roperand, temp);
    if (operation == ">") {
        return first > second;
    } else if (operation == "<") {
        return first < second;
    } else if (operation == ">=") {
        return first >= second;
    } else if (operation == "<=") {
        return first <= second;
    } else if (operation == "==") {
        return first == second;
    } else if (operation == "!=") {
        return first != second;
    } else {
        std::cout << "unknown operation" << std::endl;
        abort();
    }
}

void Parser::input(bool temp)
{
    if (m_token.size() <= 2) {
        std::cout << "syntax error ։ wrong entry" << std::endl;
        abort();
    } else if (m_token[1] == "<-") {
        if (!temp && haveVariableInStaticVector(m_token[2])) {
            std::string current = cinRightValu(m_token[2]);
            changeValue (m_token[2], current, temp);
        } else if (haveVariable(m_token[2])) {
            std::string current = cinRightValu(m_token[2]);
            changeValue (m_token[2], current, temp);
        } else {
            std::cout << "don't have '" << m_token[2] << "' variable" << std::endl;
            abort();
        }
    } else {
        std::cout << "syntax error" << std::endl;
        std::abort();
    }
}

void Parser::output(bool temp)
{
    if (m_token.size() <= 2) {
        std::cout << "syntax error" << std::endl;
        abort();
    } else if(m_token[2][0] == '[') {
        std::cout << m_token[2].substr(1, m_token[2].size() - 2) << std::endl;
    } else if (isNumberI(m_token[2]) || isNumberD(m_token[2])) {
        std::cout << m_token[2] << std::endl;
    } else if (m_token[2] == "(") {
            std::cout << operation(2, temp) << std::endl;
            if (indexCloseScope(2) + 1 < m_token.size()) {
                std::cout << "inappropriate value" << std::endl;
                abort();
            }
    } else if (isSimbol(m_token[2])) {
        std::cout << m_token[2][1] << std::endl;
    } else if (!temp && haveVariableInStaticVector(m_token[2])) {
        for (int i = 0; i < s_variable.size(); ++i) {
            if (s_variable[i].variable == m_token[2]) {
                if (isSimbol(s_variable[i].value)) {
                    std::cout << (s_variable[i].value)[1] << std::endl;
                } else {
                    std::cout << s_variable[i].value << std::endl;
                }
                break;
            }
        }
    } else if (haveVariable(m_token[2])) {
        for (int i = 0; i < m_variable.size(); ++i) {
            if (m_variable[i].variable == m_token[2]) {
                if (isSimbol(m_variable[i].value)) {
                    std::cout << (m_variable[i].value)[1] << std::endl;
                } else {
                    std::cout << m_variable[i].value << std::endl;
                }
                break;
            }
        }
    } else {
        std::cout << "an unknown variable has been displayed" << std::endl;
        abort();
    }
}

void Parser::variableStatement(std::vector<Variable>& t_variable, bool temp)
{
    if (temp && haveVariable (m_token[1])) {
        std::cout << "Repetition of variable name" << std::endl;
        abort();
    } else if (!temp && haveVariableInStaticVector(m_token[1])) {
        std::cout << "Repetition of variable name" << std::endl;
        abort();
    }
    Variable v;
    v.variable = m_token[1];
    v.type = m_token[0];
    if (m_token.size() == 2) {
        v.value = " ";
    } else if (m_token[2] == "=") {
        if (m_token[3] == "(") {
            v.value = rightValu(v.type, operation(3, temp), temp);
            if (indexCloseScope(3) + 1 < m_token.size()) {
                std::cout << "inappropriate value" << std::endl;
                abort();
            }
        } else if (m_token.size() <= 4){
            v.value = rightValu(v.type, m_token[3], temp);
        } else {
            std::cout << "Segmentation fault" << std::endl;
            abort();
        }
    }  else {
        std::cout << "unfinished announcement" << std::endl;
        abort();
    }
    if(temp) {
        m_variable.push_back(v);
    } else {
        t_variable.push_back(v);
        s_variable.push_back(v);
    }
}

void Parser::withoutTypeVariable(bool temp)
{
    if (!haveVariable(m_token[0]) && (!temp && !haveVariableInStaticVector(m_token[0]))){
        std::cout << "undeclared variable" << std::endl;
        abort();
    }
    if (m_token[1] == "=") {
        if (m_token[2] == "(") {
            std::string temprory = operation(2, temp);
            changeValue (m_token[0], temprory, temp);
        } else {
            changeValue (m_token[0], m_token[2], temp);
        }
    }
}

void Parser::pars(std::vector<Variable>& t_variable, bool temp)
{
    pars_token();
    if (m_token[0] == "mutq") {
        input();
    } else if (m_token[0] == "elq") {
        output(temp);
    } else if (isKey(m_token[0])) {
        variableStatement(t_variable, temp);
    } else {
        withoutTypeVariable(temp);
    }
}


int Parser::operationSign() const
{
    for (int i = 0; i < m_token.size(); ++i) {
        if (m_token[i] == ">" || m_token[i] == "<" || m_token[i] == "<="
                || m_token[i] == ">=" || m_token[i] == "==" || m_token[i] == "!=") {
            return i;
        }
    }
    return 0;
}

bool Parser::condition(bool temp)
{
    int indexEndIf = indexCloseScope(1);
    int indexOperations = operationSign();
    if (indexEndIf < m_token.size() - 2) {
        std::cout << "unknown expression" << std::endl;
        abort();
    } else if (indexEndIf == 3) {
        if (helpExpression(m_token[2], temp)) { return true; }
        return false;
    } if (!indexOperations) {
        if (m_token[2] != "(") {
            if (std::stod(operation(1, temp))) { return true; }
            return false;
        } else {
            if (std::stod(operation(2, temp))) { return true; }
            return false;
        }
    } else {
        std::string first = m_token[2];
        std::string second = m_token[indexOperations + 1];
        if (indexOperations > 3) {
            first = operation(2, temp);
        }
        if (m_token[indexOperations + 1] == "(") {
            second = operation(indexOperations + 1, temp);
        }
        return expression (first, m_token[indexOperations], second, temp);
    }
}

void Parser::pars_token()
{
    std::string current;
    for (int i = 0; i < m_str.size(); ++i)
    {
        if (m_str[i] != ' ' && m_str[i] != ')' && m_str[i] != '(') {
            current += m_str[i];
        } else if (!current.empty()) {
            m_token.push_back(current);
            current.clear();
        }
        if (m_str[i] == '(') {
            m_token.push_back("(");
        } else if (m_str[i] == ')') {
            m_token.push_back(")");
        }
    }
    if (!current.empty()) {
            m_token.push_back(current);
    }
}

int main(int argc, char** argv)
{
    if (argc <= 1) {
        std::cout << "don't give file" << std::endl;
        return 0;
    }
    std::string expansion;
    for (int i = 0; argv[1][i] != '\0'; ++i) {
        if (argv[1][i] == '.') {
            ++i;
            while (argv[1][i] != '\0') {
                expansion += argv[1][i];
                ++i;
            }
            break;
        }
    }
    if (expansion != "ml") {
        std::cout << "expansion is not ml" << std::endl;
        return 0;
    }
      Parser p(argv[1]);
    return 0;
}
