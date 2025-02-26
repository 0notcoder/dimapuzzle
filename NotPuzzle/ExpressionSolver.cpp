#include "ExpressionSolver.hpp"
#include <cctype>
#include <cmath>

Expression::Expression(const std::string &token) : m_token(token) {}

Expression::Expression(const std::string &token, const std::initializer_list<Expression> &args)
    : m_token(token), m_args(args) {}

std::vector<Expression> Expression::getArgs() const {
    return m_args;
}

std::string Expression::getToken() const {
    return m_token;
}

Parser::Parser(std::deque<std::string> tokens) : m_tokens(std::move(tokens)) {}

Expression Parser::parse() {
    return parseBinaryExpression(0);
}

std::string Parser::getToken() {
    if (m_tokens.empty()) throw std::runtime_error("Unexpected end of input");
    std::string token = m_tokens.front();
    m_tokens.pop_front();
    return token;
}

void Parser::putToken(const std::string &token) {
    m_tokens.push_front(token);
}

Expression Parser::parseSimpleExpression() {
    std::string token = getToken();
    if (token.empty()) throw std::runtime_error("Invalid token");

    // число
    if (std::isdigit(token[0])) return Expression(token);

    // выражение в скобках
    if (token == "(") {
        Expression result = parse();
        if (getToken() != ")") throw std::runtime_error("Expected ')'");
        return result;
    }

    // унарная операция
    return Expression(token, { parseSimpleExpression() });
}

uint8_t getPriority(const std::string &token) {
    if (token == "+" || token == "-") return 1;
    if (token == "*" || token == "/") return 2;
    if (token == "^") return 3;
    return 0;
}

Expression Parser::parseBinaryExpression(uint8_t minPriority) {
    Expression leftExpression = parseSimpleExpression();

    while (true) {
        std::string binaryOperator = getToken();
        uint8_t priority = getPriority(binaryOperator);

        if (priority <= minPriority) {
            putToken(binaryOperator);
            return leftExpression;
        }

        Expression rightExpression = parseBinaryExpression(priority);
        leftExpression = Expression(binaryOperator, { leftExpression, rightExpression });
    }
}

double eval(const Expression &e) {
    switch (e.getArgs().size()) {
        case 2: {
            auto a = eval(e.getArgs()[0]);
            auto b = eval(e.getArgs()[1]);
            if (e.getToken() == "+") return a + b;
            if (e.getToken() == "-") return a - b;
            if (e.getToken() == "*") return a * b;
            if (e.getToken() == "/") return a / b;
            if (e.getToken() == "^") return pow(a, b);
            throw std::runtime_error("Unknown binary operator");
        }
        case 1: {
            auto a = eval(e.getArgs()[0]);
            if (e.getToken() == "+") return +a;
            if (e.getToken() == "-") return -a;
            if (e.getToken() == "abs") return fabs(a);
            if (e.getToken() == "sin") return sin(a);
            if (e.getToken() == "cos") return cos(a);
            throw std::runtime_error("Unknown unary operator");
        }
        case 0:
            return strtod(e.getToken().c_str(), nullptr);
    }
    throw std::runtime_error("Unknown expression type");
}
