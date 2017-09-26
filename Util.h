#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <memory>

std::string trimEndsWhites(const std::string& str);
void printResult(const std::shared_ptr<std::string>& message,
                 const std::shared_ptr<std::string>& result);
void printWelcom();

#endif // UTIL_H
