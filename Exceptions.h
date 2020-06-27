#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

namespace mtm {
    class Exception : public std::exception {};

    class GameException : public Exception {
    public:
        const char* what() const noexcept override
        {
            std::string str = "A game related error has occurred: " + getType();
            return str.c_str();
        }
        virtual const std::string getType() const
        {
            return "GameException";
        }
    };

    class IllegalArgument : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "IllegalArgument";
            }
    };

    class IllegalCell : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "IllegalCell";
            }
    };

    class MoveTooFar : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "MoveTooFar";
            }
    };

    class CellEmpty : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "CellEmpty";
            }
    };

    class CellOccupied : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "CellOccupied";
            }
    };

    class OutOfRange : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "OutOfRange";
            }
    };

    class OutOfAmmo : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "OutOfAmmo";
            }
    };

    class IllegalTarget : public GameException
    {
        public:
            const std::string getType() const override
            {
                return "IllegalTarget";
            }
    };
}

#endif
