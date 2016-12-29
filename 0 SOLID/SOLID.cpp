#include "stdafx.h"
#include "E:\Work\Libraries\boost\experimental\di\include\boost\di.hpp"

void OCP_TEST();
void SRP_TEST();
void LSP_TEST();
void ISP_TEST();

struct ILogger
{
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() = 0;
};

struct ConsoleLogger : public ILogger
{
    void log(const std::string& msg) override
    {
        std::cout << "LOG: " << msg << std::endl;
    }
};

class Engine
{
    int horse_power_ {450};
    int volume_ {4};

    //    explicit Engine(int horse_power, int volume)
    //        : horse_power_(horse_power)
    //        , volume_(volume)
    //    {}

    friend std::ostream& operator<<(std::ostream& ost, const Engine& eng)
    {
        return ost << "Engine stats:\n\tHorse Power: " << eng.horse_power_ <<
                "\n\tVolume: " << eng.volume_ << std::endl;
    }
};

class Car
{
    std::shared_ptr<Engine> engine_;
//    shared_ptr<ILogger> logger_;

public:
    explicit Car(std::shared_ptr<Engine>& engine) //, shared_ptr<ILogger>& logger)
        : engine_(engine)
        //, logger_(logger)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Car& car)
    {
        return os << "Car has the following specs:\n\n" << *car.engine_;
    }
};

int main()
{
    using namespace boost;

//    auto injector = di::make_injector(
//                                      di::bind<ILogger>().to<ConsoleLogger>()
//                                     );
    auto injectorl = di::make_injector();
    auto car = injectorl.create<std::shared_ptr<Car>>();

    std::cout << *car << std::endl;

    return 0;
}
