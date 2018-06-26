#ifndef LOG_H
#define LOG_H

#include <string>

using namespace std;

class Log
{
public:
    virtual void AddMessage (const string &message ) = 0;
};

#endif // LOG_H
