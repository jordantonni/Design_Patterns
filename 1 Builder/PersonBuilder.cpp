#include "PersonBuilder.h"
#include "PersonJobBuilder.h"
#include "PersonAddressBuilder.h"


PersonAddressBuilder PersonBuilder::lives()
{
    return PersonAddressBuilder { person };
}

PersonJobBuilder PersonBuilder::works()
{
    return PersonJobBuilder { person };
}
