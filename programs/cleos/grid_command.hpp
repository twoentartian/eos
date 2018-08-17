#pragma once

#include <iostream>
#include <string>
#include <map>
#include <exception>

namespace eos_grid
{
    class Command
    {
    private:
        

    public:
        virtual int Execute(int argc, char** argv);

        virtual std::string GetAbbr();
    };

    class CleosCommand final: public Command
    {
    protected:
        CleosCommand();

        ~CleosCommand();

    private:
        static CleosCommand* _instance;

        static pthread_mutex_t m_mutex;

    public:
        static Command* GetInstance();

        int Execute(int argc, char** argv);

        std::string GetAbbr();
    };

    class CommandInterpreter
    {
    private:
        static std::map<std::string,Command*> commandMap;

        static int Register(Command* instance);

    public:
        static int Interpreter(int argc, char** argv);

        static void Init();
    };
}