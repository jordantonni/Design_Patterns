#include <memory>
#include <string>
#include <iostream>
using namespace std;

/*
 * ABSTRACT:
 * Lazy_Proxy_Bitmap is a proxy class that gives us the functionalty to lazily instantiate an object of Bitmap when it is needed.
 * It offers the same interface as the class it is proxying.
 */

struct IImage
{
    virtual ~IImage() = default;
    virtual void draw() = 0;
};

struct Bitmap : IImage
{
    string filename;

    explicit Bitmap(const string& filename)
        : filename{ filename }
    {
        cout << "Loading ... " << filename << endl;
    }


    void draw() override
    {
        cout << "Drawing Image " << filename << endl;
    }
};

void draw_image(IImage& img)
{
    cout << "About to draw image " << endl;
    img.draw();
    cout << "Image drawn" << endl;
}

struct Lazy_Proxy_Bitmap : IImage
{
    string filename;
    Bitmap* bitmap_ptr;

    Lazy_Proxy_Bitmap(const string& filename)
        : filename{ filename }
        , bitmap_ptr{ nullptr }
    {}

    void draw() override
    {
        if(!bitmap_ptr)
            bitmap_ptr = new Bitmap{filename};
        bitmap_ptr->draw();
    }


    ~Lazy_Proxy_Bitmap() override
    {
        delete bitmap_ptr;
    }
 }; 

void virtual_proxy()
{
    Bitmap img { "Pokemon.img" };
    draw_image(img);
    draw_image(img);
}

void test_lazy()
{
    virtual_proxy();
}
