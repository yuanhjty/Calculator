#include "Interpreter.h"

#include <utility>

Interpreter::Interpreter() :
    _calculator(new ScienceCalculator),
    _calculatorID(CAL_SCIENCE),
    _calculatorPool{std::make_pair(_calculatorID, _calculator)} { }

Interpreter::~Interpreter() {
    for (const auto calcator : _calculatorPool)
        delete calcator.second;
    _calculatorPool.clear();
}

COMMAND Interpreter::interpret(const std::string &input) {
    setInput(input);
    return execute(parseCommand());
}

void Interpreter::setInput(const std::string &input) {
    auto firstNotBlankPos = input.find_first_not_of(" \t");
    auto lastNotBlankPos = input.find_last_not_of(" \t");

    if (std::string::npos == firstNotBlankPos || std::string::npos == lastNotBlankPos)
        _input = std::string("");
    else
        _input = input.substr(firstNotBlankPos, lastNotBlankPos - firstNotBlankPos + 1);
}

std::string Interpreter::parseCommand() const {
    if (_input.empty())
        return std::string("empty");

    if (_input.find_first_of(" \t") != std::string::npos)
        return std::string("evalute");

    return _input;
}

COMMAND Interpreter::execute(const std::string &command) {
    const auto it = _commands.find(command);
    COMMAND cmd = (it != _commands.cend()) ? it->second : CMD_EVALUATE;

    switch (cmd) {
    // switch calculator
    case CMD_SCIENCE:
        switchCalculator(CAL_SCIENCE);
        break;
    case CMD_PROGRAMMER:
        switchCalculator(CAL_PROGRAMMER);
        break;
    case CMD_LENGTH:
        switchCalculator(CAL_LENGTH);
        break;
    case CMD_AREA:
        switchCalculator(CAL_AREA);
        break;
    case CMD_VOLUME:
        switchCalculator(CAL_VOLUME);
        break;
    case CMD_WEIGHT:
        switchCalculator(CAL_WEIGHT);
        break;
    case CMD_TIME:
        switchCalculator(CAL_TIME);
        break;
    case CMD_VELOCITY:
        switchCalculator(CAL_VELOCITY);
        break;
    case CMD_POWER:
        switchCalculator(CAL_POWER);
        break;
    case CMD_ENERGY:
        switchCalculator(CAL_ENERGY);
        break;
    case CMD_PRESSURE:
        switchCalculator(CAL_PRESSURE);
        break;
    case CMD_DATA:
        switchCalculator(CAL_DATA);
        break;
    case CMD_ANGLE:
        switchCalculator(CAL_ANGLE);
        break;

    // switch angle format of science calculator
    case CMD_DEGREE:
        _calculator->setNumeralFormat(NF_DEGREE);
        break;
    case CMD_RADIAN:
        _calculator->setNumeralFormat(NF_RADIAN);
        break;

    // switch notation of science calculator
    case CMD_DEFAULT:
        _calculator->setNumeralFormat(NF_DEFAULT);
        break;
    case CMD_FIXED:
        _calculator->setNumeralFormat(NF_FIXED);
        break;
    case CMD_SCIENTIFIC:
        _calculator->setNumeralFormat(NF_SCIENTIFIC);
        break;

    // switch numeral base of programmer calculator
    case CMD_BINARY:
        _calculator->setNumeralFormat(NF_BINARY);
        break;
    case CMD_OCTAL:
        _calculator->setNumeralFormat(NF_OCTAL);
        break;
    case CMD_DECIMAL:
        _calculator->setNumeralFormat(NF_DECIMAL);
        break;
    case CMD_HEX:
        _calculator->setNumeralFormat(NF_HEX);
        break;

    // evaluate
    case CMD_EMPTY:     // evaluate empty expression
    case CMD_EVALUATE:
        _calculator->evaluate(_input);
        break;

    // clear history
    case CMD_CLEAR:
        _calculator->clearHistory();
        break;

    // update history
    case CMD_COMPLETE:
        if ((ErrorState)(_calculator->errorState() & ERROR_FIELD) == ERROR_NOERROR)
            _calculator->updateHistory();
        break;

    default:
        break;
    }
    return cmd;
}

void Interpreter::switchCalculator(CALCULATOR id) {
    if (id == _calculatorID)
        return;

    _calculatorID = id;
    auto it = _calculatorPool.find(id);
    if (_calculatorPool.end() != it)
        _calculator = it->second;
    else {
        switch (id) {
        case CAL_SCIENCE:
            _calculator = new ScienceCalculator;
            break;
        case CAL_PROGRAMMER:
            _calculator = new ProgrammerCalculator;
            break;
        case CAL_LENGTH:
            _calculator = new LengthConverter;
            break;
        case CAL_AREA:
            _calculator = new AreaConverter;
            break;
        case CAL_VOLUME:
            _calculator = new VolumeConverter;
            break;
        case CAL_WEIGHT:
            _calculator = new WeightConverter;
            break;
        case CAL_TIME:
            _calculator = new TimeConverter;
            break;
        case CAL_VELOCITY:
            _calculator = new VelocityConverter;
            break;
        case CAL_POWER:
            _calculator = new PowerConverter;
            break;
        case CAL_ENERGY:
            _calculator = new EnergyConverter;
            break;
        case CAL_PRESSURE:
            _calculator = new PressureConverter;
            break;
        case CAL_DATA:
            _calculator = new DataConverter;
            break;
        case CAL_ANGLE:
            _calculator = new AngleConverter;
            break;
        default:
            throw InnerError("inner error: undefined calculator");
            break;
        }
        _calculatorPool.insert(std::make_pair(id, _calculator));
    }
}

std::unordered_map<std::string, COMMAND> Interpreter::_commands = {
    // Switch calculator type
    // calculator
    {"science", CMD_SCIENCE}, {"programmer",CMD_PROGRAMMER},
    // converter
    {"length", CMD_LENGTH}, {"area", CMD_AREA}, {"volume", CMD_VOLUME},
    {"weight",CMD_WEIGHT}, {"time", CMD_TIME}, {"velocity", CMD_VELOCITY},
    {"power", CMD_POWER}, {"energy", CMD_ENERGY}, {"pressure", CMD_PRESSURE},
    {"data", CMD_DATA}, {"angle", CMD_ANGLE},

    // Switch data format
    // For science calculator
    {"degree", CMD_DEGREE}, {"radian", CMD_RADIAN},
    {"default", CMD_DEFAULT}, {"fixed", CMD_FIXED}, {"scientific", CMD_SCIENTIFIC},
    // For programmer calculator
    {"binary", CMD_BINARY}, {"octal", CMD_OCTAL},
    {"decimal", CMD_DECIMAL}, {"hex", CMD_HEX},

    // evaluate
    {"evaluate", CMD_EVALUATE},

    // clear history
    {"clear", CMD_CLEAR},

    // Others
    {"complete", CMD_COMPLETE}, {"empty", CMD_EMPTY}, {"quit", CMD_QUIT},
};
