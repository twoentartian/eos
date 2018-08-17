#include "grid_command.hpp"

extern int eos_main( int argc, char** argv );

namespace eos_grid
{
    // Class Command
    int Command::Execute(int argc, char** argv)
    {
        throw new std::logic_error("Base command cannot access Execute()\r\n");
    }

    std::string Command::GetAbbr()
    {
        throw new std::logic_error("Base command cannot access GetAbbr()\r\n");
        return "Error";
    }

    // Class CleosCommand
    CleosCommand* CleosCommand::_instance = nullptr;
    pthread_mutex_t CleosCommand::m_mutex;

    CleosCommand::CleosCommand()
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    CleosCommand::~CleosCommand()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    Command* CleosCommand::GetInstance()
    {
        pthread_mutex_lock(&m_mutex);
        if(_instance==nullptr)
        {
            _instance = new CleosCommand();
        }
        pthread_mutex_unlock(&m_mutex);
        return _instance;
    }

    int CleosCommand::Execute(int argc, char** argv)
    {
        eos_main(argc,argv);
        return 0;
    }

    std::string CleosCommand::GetAbbr()
    {
        return "origin";
    }

    // Class CommandInterpreter
    std::map<std::string,Command*> CommandInterpreter::commandMap;

    int CommandInterpreter::Interpreter(int argc, char** argv)
    {
        std::string subCommand(argv[1]);
        int newArgc = argc-1;
        char** newArgv = argv;
        if(argc>2)
        {
            for(int i=2;i<argc;i++)
            {
                newArgv[i-1] = argv[i];
            }
        }

        auto iter = commandMap.find(subCommand);

        if(iter!=commandMap.end())
        {
            return iter->second->Execute(newArgc,newArgv);
        }
        else
        {
            return 1;
        }
    }

    int CommandInterpreter::Register(Command* instance)
    {
        commandMap[instance->GetAbbr()]=instance;

        return 0;
    }

    void CommandInterpreter::Init()
    {
        Register(CleosCommand::GetInstance());
        //TODO: Further command
    }
}