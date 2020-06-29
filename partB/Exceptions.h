#ifndef EXEPTION_H
#define EXEPTION_H
#include "Auxiliaries.h"

namespace mtm {
    class Exception : public std::exception {
        std::string str_err;
    public:
        Exception(std::string error = "") : str_err(error) {}
        
        virtual ~Exception() = default;
        virtual const char *what() const noexcept override {
            return str_err.c_str();
        }
    };
}

#endif