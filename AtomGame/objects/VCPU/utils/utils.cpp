#include "utils.h"

utils::ostream::ostream (std::ostream &out, int displacement) : displacement_ (displacement), out_ (&out)
{
}

utils::ostream &utils::ostream::operator+= (int displacement)
{
    displacement_ += displacement;
    return *this;
}

utils::ostream &utils::ostream::operator-= (int displacement)
{
    displacement_ -= displacement;
    return *this;
}

utils::ostream &utils::ostream::println ()
{
    out_->put ('\n');
    return *this;
}

utils::ostream &utils::ostream::operator++ ()
{
    displacement_++;
    return *this;
}

utils::ostream &utils::ostream::operator-- ()
{
    displacement_--;
    return *this;
}