#ifndef MYUTILS_LIBRARY_H
#define MYUTILS_LIBRARY_H

//---------------------------------------
//! @file library.h
//! Contains some additional utilities
//---------------------------------------

#include <iostream>
#include <cassert>

//---------------------------------------
//! @brief A stream that is used to log errors
//---------------------------------------

#define ERROR_STREAM utils::ostream(std::cerr)

//---------------------------------------
//! @brief A stream that is used to log the general information
//---------------------------------------

#define LOG_STREAM utils::ostream(std::cout)

//---------------------------------------
//! @brief Macro to test object integrity
//---------------------------------------

#ifdef FULL_LOG

#define INFO(object)                                      \
if(!(object).ok())                                          \
{                                                           \
    ERROR_STREAM.println("In ",__PRETTY_FUNCTION__," :");   \
    (object).dump(ERROR_STREAM);                            \
    assert(!"Object is OK");                                \
}                                                           \
else                                                        \
{                                                           \
    LOG_STREAM.println("In ",__PRETTY_FUNCTION__," :");     \
    (object).dump(LOG_STREAM);                              \
}

#else
#ifdef ERROR_LOG

#define INFO(object)                                      \
if(!(object).ok())                                          \
{                                                           \
    ERROR_STREAM.println("In ",__PRETTY_FUNCTION__," :");   \
    (object).dump(ERROR_STREAM);                            \
    assert(!"Object is ok");                                \
}

#else
#define INFO( object )
#endif
#endif

namespace utils
{

//---------------------------------------
//! @brief A poison value for int
//---------------------------------------

#define POISON_INT 0xEDAEDAED

//---------------------------------------
//! @brief A poison value for pointers
//---------------------------------------

#define POISON_PTR (void *) 0xEDAEDAEDAEDA

//---------------------------------------
//! @class ostream is used to log data in an appropriate format
//---------------------------------------

    class ostream
    {
        int displacement_;
        std::ostream *out_;
    public:

//---------------------------------------
//! @brief Prints a value
//! @param value A value to be printed
//! @note Similar in function to std::ostream::operator<<
//! @returns This ostream
//---------------------------------------

        template<typename T>
        ostream &print (T &&value);

//---------------------------------------
//! @brief Prints a custom amount of values
//! @param value A value to be printed first
//! @param ... Values to be printed
//! @note Similar in function to std::ostream::operator<<
//! @returns This ostream
//---------------------------------------

        template<typename T, typename... Args>
        ostream &print (T &&value, Args...);

//---------------------------------------
//! @brief Prints the line padding, a custom amount of values and moves the cursor to the next line
//! @param value A value to be printed first
//! @param ... Values to be printed
//! @returns This ostream
//---------------------------------------

        template<typename T, typename... Args>
        ostream &println (T &&value, Args...);

//---------------------------------------
//! @brief Moves the cursor to the next line
//! @returns This ostream
//---------------------------------------

        ostream &println ();

//---------------------------------------
//! @brief Constructor
//! @param out std::ostream that is used to print into
//! @param displacement A length of the padding
//---------------------------------------

        ostream (std::ostream &out, int displacement = 0);

//---------------------------------------
//! @brief Increments the length of the padding
//! @param displacement A value to add to the current padding length
//! @returns This ostream
//---------------------------------------

        ostream &operator+= (int displacement);

//---------------------------------------
//! @brief Decrements the length of the padding
//! @param displacement A value to subtract from the current padding length
//! @returns This ostream
//---------------------------------------

        ostream &operator-= (int displacement);

//---------------------------------------
//! @brief Increments the length of the padding by one
//! @returns This ostream
//---------------------------------------

        ostream &operator++ ();

//---------------------------------------
//! @brief Decrements the length of the padding
//! @returns This ostream
//---------------------------------------

        ostream &operator-- ();
    };

    template<typename T>
    ostream &ostream::print (T &&value)
    {
        (*out_) << value;
        return *this;
    }

    template<typename T, typename... Args>
    utils::ostream &utils::ostream::print (T &&value, Args... args)
    {
        (*out_) << value;
        print (args...);
        return *this;
    }

    template<typename T, typename... Args>
    ostream &ostream::println (T &&value, Args... args)
    {
        for (int i = 0; i < displacement_; i++)
            out_->put ('\t');
        print (value, args...);
        out_->put ('\n');
        return *this;
    }
}

#endif