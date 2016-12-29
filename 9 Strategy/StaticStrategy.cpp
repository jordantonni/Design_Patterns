#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

/*
 * ABSTRACT:
 * Static method is achieved by making the strategy objects a templated parameter instead of a pointer.
 * 
 * 
 */

enum class OutputFormat2
{
    Markdown,
    Html
};

class ListStrategy2
{
public:
    virtual ~ListStrategy2() = default;
    virtual void Start(ostringstream& oss) = 0;
    virtual void End(ostringstream& oss) = 0;
    virtual void Append(ostringstream& oss, const string& s) = 0;
};

class MarkdownStrategy2 : public ListStrategy2
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

class HtmlStrategy2 : public ListStrategy2
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

template <typename POLICY>
class TextProcessor2
{
    ostringstream oss;
    unique_ptr<POLICY> strategy_used;
public:

    TextProcessor2()
        : strategy_used { make_unique<POLICY>() }
    {}

    void append_list_items(const vector<string> items)
    {
        strategy_used->Start(oss);
        for (const auto& i : items)
            strategy_used->Append(oss, i);
        strategy_used->End(oss);
    }

    friend ostream& operator<<(ostream& oss, const TextProcessor2& tp)
    {
        return oss << tp.oss.str();
    }
};


void test_static_strategy()
{
    TextProcessor2<MarkdownStrategy2> tp;
    tp.append_list_items({ "Kitten Food", "Cat Litter", "Cat Toys", "Treats" });
    cout << tp << endl << endl;
    
    
    TextProcessor2<HtmlStrategy2> tp2;
    tp2.append_list_items({ "Kitten Food", "Cat Litter", "Cat Toys", "Treats" });
    cout << tp2 << endl << endl;
}
