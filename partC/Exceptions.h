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

    class GameException : public Exception {
        std::string str_err;

    public:
        GameException(std::string error = "") : str_err(error) {}

        virtual ~GameException() = default;
        virtual const char *what() const noexcept override {
            return str_err.c_str();
        }
    };
    //-----------------------------------------------------------------------------------//
    class IllegalArgument : public GameException {
    public:
        IllegalArgument() : GameException("A game related error has occurred: IllegalArgument") {}
    };

    class IllegalCell : public GameException {
    public:
        IllegalCell() : GameException("A game related error has occurred: IllegalCell") {}
    };

    class CellEmpty : public GameException {
    public:
        CellEmpty() : GameException("A game related error has occurred: CellEmpty") {}
    };

    class MoveTooFar : public GameException {
    public:
        MoveTooFar() : GameException("A game related error has occurred: MoveTooFar") {}
    };

    class CellOccupied : public GameException {
    public:
        CellOccupied() : GameException("A game related error has occurred: CellOccupied") {}
    };

    class OutOfRange : public GameException {
    public:
        OutOfRange() : GameException("A game related error has occurred: OutOfRange") {}
    };

    class OutOfAmmo : public GameException {
    public:
        OutOfAmmo() : GameException("A game related error has occurred: OutOfAmmo") {}
    };

    class IllegalTarget : public GameException {
    public:
        IllegalTarget() : GameException("A game related error has occurred: IllegalTarget") {}
    };

}

#endif