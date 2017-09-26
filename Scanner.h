#ifndef SCANNER_H
#define SCANNER_H

#include <string>

class Scanner
{
public:
    Scanner();

    void init();
    std::string scan(const std::string& input);
};

#endif // SCANNER_H
