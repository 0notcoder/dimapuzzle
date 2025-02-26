#pragma once
#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <initializer_list>

// Дима это пиздец
// Код со стековэрфлоу
// я почти понимаю как это работает
// полностью переписал немного исправил
// но я понимаю что это ужасный код ))0
// но как бы похуй!!

struct Expression {
private:
    std::string m_token;
    std::vector<Expression> m_args;
public:
    Expression(const std::string &token);
    Expression(const std::string &token, const std::initializer_list<Expression> &args);

    std::vector<Expression> getArgs() const;
    std::string getToken() const;
};

class Parser {
private:
    std::deque<std::string> m_tokens;
public:
    Parser(std::deque<std::string> tokens);
    Expression parse();
private:
    Expression parseSimpleExpression();
    Expression parseBinaryExpression(uint8_t priority);

    std::string getToken();
    void putToken(const std::string &token);
};

uint8_t getPriority(const std::string &token);
double eval(const Expression &e);
