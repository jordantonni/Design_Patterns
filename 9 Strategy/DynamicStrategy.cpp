#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

/*
 * ABSTRACT:
 * TextProcessor class is the high level algorithim section. It drives the overall algorihim by defining what to do.
 * 
 * Both Markdown and Html strategies derive from the ListStrategy, which is what the TextProcessor invokes for the implmentation of the low level strategies.
 * 
 * NOTE: TextProcessor is able to change strategy dynamically at run time by passing it a different strategy.
 */

enum class OutputFormat
{
    Markdown,
    Html
};

class ListStrategy
{
public:
    virtual ~ListStrategy() = default;
    virtual void Start(ostringstream& oss) = 0;
    virtual void End(ostringstream& oss) = 0;
    virtual void Append(ostringstream& oss, const string& s) = 0;
};

class MarkdownStrategy : public ListStrategy
{
public:
    void Start(ostringstream& oss) override
    {}

    void End(ostringstream& oss) override
    {}

    void Append(ostringstream& oss, const string& s) override
    {
        oss << "*** " << s << "\n";
    }
};

class HtmlStrategy : public ListStrategy
{
public:
    void Start(ostringstream& oss) override
    {
        oss << "<html> \n\t<body>\n\t\t<ul>\n";
    }

    void End(ostringstream& oss) override
    {
        oss << "\t\t</ul>\n\t</body>\n</html>\n";
    }

    void Append(ostringstream& oss, const string& s) override
    {
        oss << "\t\t\t<li> " << s << " </li>\n";
    }
};

class TextProcessor
{
    ostringstream oss;
    unique_ptr<ListStrategy> strategy_used;
public:

    void append_list_items(const vector<string> items)
    {
        strategy_used->Start(oss);
        for (const auto& i : items)
            strategy_used->Append(oss, i);
        strategy_used->End(oss);
    }


    void set_strategy(OutputFormat strategy)
    {
        switch (strategy)
        {
        case OutputFormat::Html:
            strategy_used = make_unique<HtmlStrategy>();
            break;
        case OutputFormat::Markdown:
            strategy_used = make_unique<MarkdownStrategy>();
            break;
        }
    }

    void clear_strategy()
    {
        oss.str("");
        oss.clear();
    }

    friend ostream& operator<<(ostream& oss, const TextProcessor& tp)
    {
        return oss << tp.oss.str();
    }
};

void test_dynamic_strategy()
{
    TextProcessor tp;
    tp.set_strategy(OutputFormat::Markdown);
    tp.append_list_items({ "Kitten Food", "Cat Litter", "Treats", "Play Toy" });
    cout << tp << endl << endl;
    tp.clear_strategy();

    tp.set_strategy(OutputFormat::Html);
    tp.append_list_items({ "Kitten Food", "Cat Litter", "Treats", "Play Toy" });
    cout << tp << endl;

}
