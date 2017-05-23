//---------------------------------------
//! @file VCPU.h
//! Declaration of the virtual CPU class
//---------------------------------------

#ifndef INTERPRETER_VCPU_H
#define INTERPRETER_VCPU_H

//---------------------------------------
//! @brief Amount of registers in the cpu that can be used by user
//---------------------------------------
#define AMOUNT_OF_REGISTERS 16

#include <stack>
#include <vector>
#include <fstream>

#define ERROR_LOG

#include "../utils/utils.h"

//---------------------------------------
//! @class VCPU
//! @brief Class that emulates a CPU with a strictly defined set of commands
//---------------------------------------
class VCPU
{
    const static int regnum_ = AMOUNT_OF_REGISTERS;
    int registers[regnum_];
    std::vector<int> instruction_vector_;
    std::stack<int> data_stack_;
    std::stack<int> call_stack_;
    std::vector<int>::const_iterator ip_;
    int sign;
public:

//---------------------------------------
//! @brief Default constructor
//---------------------------------------

    VCPU ();

//---------------------------------------
//! @brief Destructor
//---------------------------------------

    ~VCPU ();

//---------------------------------------
//! @brief Loads an operation set from binary file
//! @param in An open input stream of a file with the operation set
//---------------------------------------

    bool load (std::ifstream &in);

//---------------------------------------
//! @brief Sets the instruction set
//! @param set A vector with the preferred instructions
//---------------------------------------

    void setInstructions (std::vector<int> set);

//---------------------------------------
//! @brief Sets instruction pointer back to the first instruction and clears data and call stacks
//---------------------------------------

    void reset ();

//---------------------------------------
//! @brief Runs the CPU until an error occurs or the end is reached
//! @return Error code if an error has occurred or zero if the end was reached
//! @note Error codes: 0 - no errors, 1 - instruction pointer is out of the instruction set bounds,
//! 2 - reference to a non-existent register, 3 - data stack underflow, 4 - call stack underflow, 5 - illegal command
//---------------------------------------

    int execute ();

//---------------------------------------
//! @brief Runs one iteration of the loaded program
//! @return Error code if an error has occurred, zero if the end was reached, -1 if the end was not reached on this iteration
//! @note Error codes: 0 - no errors, 1 - instruction pointer is out of the instruction set bounds,
//! 2 - reference to a non-existent register, 3 - data stack underflow, 4 - call stack underflow, 5 - illegal command
//---------------------------------------

    int executeOne ();

//---------------------------------------
//! @brief Pushes a value into the data stack
//! @param value A value to be pushed into the data stack
//---------------------------------------

    void push (int value);

//---------------------------------------
//! @brief Pops a value from the top of the data stack
//! @return A value from the top of the data stack
//---------------------------------------

    int pop ();

//---------------------------------------
//! @brief Places a value into the specified register
//! @param value A value to be places
//! @param index Index of the register
//---------------------------------------

    void setReg (int value, size_t index);

//---------------------------------------
//! @brief Returns a value from the specified register
//! @param index Index of the register
//! @return A value from the specified register
//---------------------------------------


    int getReg (size_t index);

//---------------------------------------
//! @brief Silent verifier
//! @return True if object is ok
//---------------------------------------

    bool ok () const;

//---------------------------------------
//! @brief Dumper
//! @param out A stream to write the dump into
//---------------------------------------

    void dump (utils::ostream out);

};

#endif //INTERPRETER_VCPU_H
