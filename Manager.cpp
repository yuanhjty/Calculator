#include "Manager.h"


std::map<std::string, COMMAND> Manager::commands =
{
    {"c-binary"  , C_BINARY  }, {"c-octal" , C_OCTAL }, {"c-decimal"    , C_DECIMAL    }, {"c-hex" , C_HEX },
    {"c-weight"  , C_WEIGHT  }, {"c-length", C_LENGTH}, {"c-volume"     , C_VOLUME     }, {"c-area", C_AREA},
    {"c-velocity", C_VELOCITY}, {"c-time"  , C_TIME  }, {"c-temperature", C_TEMPERATURE},
    {"c-science" , C_SCIENCE },
    {"c-evaluate", C_EVALUATE}
};

void Manager::executeCommand(const std::string &command)
{
    if (command.empty())
        return;

    auto it = commands.find(command);
    if (it == commands.end()) { // If true, the input will be treated as an expression.
        evaluate();
    } else {
        switch (it->second) {
        case C_BINARY:
        case C_OCTAL:
        case C_DECIMAL:
        case C_WEIGHT:
        case C_LENGTH:
        case C_VOLUME:
        case C_AREA:
        case C_VELOCITY:
        case C_TIME:
        case C_TEMPERATURE:
        case C_SCIENCE:
        case C_EVALUATE:
            evaluate();
            break;
        default:
            std::cerr << "Invalid input" << std::endl;
            break;
        }
    }
}

void Manager::evaluate()
{
    m_calculator->scanInput(m_input);
    m_calculator->evaluate();
}

void Manager::process(const std::string &input)
{
    setInput(input);
    executeCommand(getCommand());
}

