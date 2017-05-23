//
// Created by svuatoslav on 4/4/17.
//

#include "VCPU.h"

VCPU::VCPU ()
{
    instruction_vector_.push_back (0);
    ip_ = instruction_vector_.cbegin ();
    sign = -1;
    for (int i = 0; i < AMOUNT_OF_REGISTERS; ++i)
        registers[i] = 0;
    INFO (*this);
}

VCPU::~VCPU ()
{
    INFO (*this);
    ip_ = instruction_vector_.cbegin () - 1;
    sign = POISON_INT;
}

bool VCPU::load (std::ifstream &in)
{
    INFO (*this);
    if (!in.is_open () || !in.good ())
        return false;
    instruction_vector_.clear ();
    while (in.good ())
    {
        int val;
        in.read ((char *) &val, 4);
        if (in.good ())
            instruction_vector_.push_back (val);
    }
    ip_ = instruction_vector_.cbegin ();
    reset ();
    INFO (*this);
    return true;
}

void VCPU::setInstructions (std::vector<int> instructions)
{
    INFO (*this);
    instruction_vector_ = instructions;
    ip_ = instruction_vector_.cbegin ();
    INFO (*this);
}

void VCPU::reset ()
{
    INFO (*this);
    ip_ = instruction_vector_.cbegin ();
    data_stack_ = std::stack<int> ();
    call_stack_ = std::stack<int> ();
    INFO (*this);
}

int VCPU::execute ()
{
    INFO (*this);
    int ret;
    while ((ret = executeOne ()) == -1);
    INFO (*this);
    return ret;
}

void VCPU::push (int val)
{
    INFO (*this);
    data_stack_.push (val);
    INFO (*this);
}

int VCPU::pop ()
{
    INFO (*this);
    int ret = 0;
    if (data_stack_.size () > 0)
    {
        ret = data_stack_.top ();
        data_stack_.pop ();
    }
    INFO (*this);
    return ret;
}

int VCPU::executeOne ()
{
    INFO (*this);
    int first;
    int second;
    switch (*(ip_++))
    {
        case 0:
            INFO (*this);
            return 0;
        case 1:
            if (*ip_ >= regnum_)
            {
                INFO (*this);
                return 2;
            }
            push (registers[*ip_]);
            ++ip_;
            break;
        case 2:
            push (*(ip_++));
            break;
        case 3:
            if (*ip_ >= regnum_)
            {
                INFO (*this);
                return 2;
            }
            if (data_stack_.empty ())
            {
                INFO (*this);
                return 3;
            }
            registers[*ip_] = pop ();
            ++ip_;
            break;
        case 4:
            if (data_stack_.empty ())
            {
                INFO (*this);
                return 3;
            }
            pop ();
            break;
        case 5:
            if (data_stack_.size () < 2)
            {
                INFO (*this);
                return 3;
            }
            first = pop ();
            second = pop ();
            push (first);
            push (second);
            break;
        case 6:
            if (data_stack_.empty ())
            {
                INFO (*this);
                return 3;
            }
            first = pop ();
            push (first);
            push (first);
            break;
        case 7:
            if (data_stack_.size () < 2)
            {
                INFO (*this);
                return 3;
            }
            first = pop ();
            second = pop ();
            push (first + second);
            break;
        case 8:
            first = pop ();
            second = pop ();
            if (first == second)
                sign = 0;
            else if (first < second)
                sign = 1;
            else
                sign = 2;
            push (first - second);
            break;
        case 9:
            first = pop ();
            second = pop ();
            if (first == second)
                sign = 0;
            else if (first < second)
                sign = 1;
            else
                sign = 2;
            push (second);
            push (first);
            break;
        case 10:
            first = pop ();
            second = pop ();
            push (first * second);
            break;
        case 11:
            first = pop ();
            second = pop ();
            push (first / second);
            break;
        case 12:
            ip_ = instruction_vector_.cbegin () + *ip_;
            break;
        case 13:
            if (sign == 0)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 14:
            if (sign == 1 || sign == 2)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 15:
            if (sign == 2)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 16:
            if (sign == 1)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 17:
            if (sign == 0 || sign == 2)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 18:
            if (sign == 0 || sign == 1)
                ip_ = instruction_vector_.cbegin () + *ip_;
            else
                ip_++;
            break;
        case 19:
            call_stack_.push (ip_ + 1 - instruction_vector_.cbegin ());
            ip_ = instruction_vector_.cbegin () + *ip_;
            break;
        case 20:
            if (call_stack_.empty ())
            {
                INFO (*this);
                return 4;
            }
            ip_ = instruction_vector_.cbegin () + call_stack_.top ();
            call_stack_.pop ();
            break;
        default:
            INFO (*this);
            return 5;

    }
    INFO (*this);
    if (ip_ >= instruction_vector_.cend () || ip_ < instruction_vector_.cbegin ())
        return 1;
    return -1;
}

bool VCPU::ok () const
{
    return ip_ >= instruction_vector_.cbegin () && ip_ <= instruction_vector_.cend () && sign != POISON_INT;
}

void VCPU::dump (utils::ostream out)
{
    out.println ("VCPU @ ", this);
    ++(out.println ('{'));
    out.println ("ip_ -> ", &(*ip_), " (", ((int) (ip_ - instruction_vector_.cbegin ())), ')');
    out.println ("instruction_vector_ = ");
    ++(out.println ('{'));
    for (std::vector<int>::const_iterator i = instruction_vector_.cbegin (); i != instruction_vector_.cend (); i++)
        out.println (*i);
    (--out).println ('}');
    std::stack<int> buffer = data_stack_;
    out.println ("data_stack_ = ");
    ++(out.println ('{'));
    while (!buffer.empty ())
    {
        out.println (buffer.top ());
        buffer.pop ();
    }
    (--out).println ('}');
    buffer = call_stack_;
    out.println ("call_stack_ = ");
    ++(out.println ('{'));
    while (!buffer.empty ())
    {
        out.println (buffer.top ());
        buffer.pop ();
    }
    (--out).println ('}');
    out.println ("sign_ = ", sign,
                 (sign == 0 ? " ( \'==\' )" : (sign == 1 ? " ( \'<\' )" : (sign == 2 ? " ( \'>\' )" : (sign ==
                                                                                                       POISON_INT
                                                                                                       ? "( POISON )"
                                                                                                       : "")))));
    (--out).println ('}');
}

void VCPU::setReg (int value, size_t index)
{
    if (index < AMOUNT_OF_REGISTERS)
        registers[index] = value;
}

int VCPU::getReg (size_t index)
{
    if (index < AMOUNT_OF_REGISTERS)
        return registers[index];
    return -1;
}
