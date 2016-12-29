#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <memory>
#include <ostream>
using namespace std;
#include <boost/lexical_cast.hpp>

/*
 * ABSTRACT:
 * Simple interpreter that tokenizes an input text expression via lexical analysis.
 * Then iterates though the tokens, parsing them into pre-defined constructs that make expressions.
 * 
 * The expression "tree" is then evaluated.
 */


// Models what each item in the text can be. A token is a predefined thing that constitutes a single entity in the string that means something.
struct Token
{
    string text;

    enum class Type
    {
        integer,
        plus,
        minus,
        lparen,
        rparen
    } type;

    Token(const Type type, const string& text)
        : text{ text }
        , type{ type }
    {}


    friend ostream& operator<<(ostream& os, const Token& obj)
    {
        return os << "`" << obj.text << "`";
    }
};

// Iterate though the string and create a token for each item we come across.
// multi digit token, integer, adds each digit to a buffer then creates a token from it once the next char is no longer a digit
vector<Token> tokenize(const string& text)
{
    vector<Token> result;

    for (size_t i = 0; i < text.length(); ++i)
    {
        switch (text[i])
        {
        case '+':
            result.emplace_back(Token(Token::Type::plus, "+"));
            break;
        case '-':
            result.emplace_back(Token(Token::Type::minus, "-"));
            break;
        case '(':
            result.emplace_back(Token(Token::Type::lparen, "("));
            break;
        case ')':
            result.emplace_back(Token(Token::Type::rparen, ")"));
            break;
        default:
            {
                ostringstream buffer;
                buffer << text[i];

                for (size_t j = i + 1; j < text.length(); ++j)
                {
                    if (isdigit(text[j]))
                    {
                        buffer << text[j];
                        ++i;
                    }
                    else
                    {
                        result.emplace_back(Token(Token::Type::integer, buffer.str()));
                        break;
                    }
                }
                break;
            }
        }
    }
    return result;
}

/*
 * Data structures we turn each token into.
 * Can either be a single value element or a binary expression consisting two elements.
 */
struct IElement
{
    virtual ~IElement() = default;
    virtual int eval() = 0;
};

struct Integer : IElement
{
    int value;

    explicit Integer(const int v)
        : value{ v }
    {}

    int eval() override
    {
        return value;
    }
};

struct BinaryOperation : IElement
{
    shared_ptr<IElement> lhs, rhs;

    enum class Type
    {
        addition,
        subtraction
    } type;

    int eval() override
    {
        if (type == Type::addition)
            return lhs->eval() + rhs->eval();

        return lhs->eval() - rhs->eval();
    }
};

/*
 * Go thought the tokens
 * Creating a binary expression of the elements.
 */
shared_ptr<IElement> parse(const vector<Token>& tokens)
{
    auto result = make_shared<BinaryOperation>();
    bool have_lhs = false;

    for (int i = 0; i < tokens.size(); ++i)
    {
        Token token = tokens[i];

        switch (token.type)
        {
        case Token::Type::integer:
            {
                int value = boost::lexical_cast<int>(token.text);
                auto integer = make_shared<Integer>(value);

                if (!have_lhs)
                {
                    result->lhs = integer;
                    have_lhs = true;
                }
                else
                {
                    result->rhs = integer;
                }
            }
            break;
        case Token::Type::plus:
            result->type = BinaryOperation::Type::addition;
            break;
        case Token::Type::minus:
            result->type = BinaryOperation::Type::subtraction;
            break;
        case Token::Type::lparen:
            {
                int j = i;
                for (; j < tokens.size(); ++j)
                    if (tokens[j].type == Token::Type::rparen)
                        break;
                vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
                auto element = parse(subexpression);

                if (!have_lhs)
                {
                    result->lhs = element;
                    have_lhs = true;
                }
                else
                {
                    result->rhs = element;
                    i = j;
                }
            }
            break;
        }
    }

    return result;
}

void test_interpreter()
{
    string input { "(13-4)-(12+1)" };
    auto tokens = tokenize(input);

    for (const auto& t : tokens)
        cout << t << "    ";
    cout << endl;

    auto parsed = parse(tokens);

    cout << input << " = " << parsed->eval() << endl;
}
