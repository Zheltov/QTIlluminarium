#ifndef FUNC_H
#define FUNC_H

#include <string>
#include <vector>
#include <map>


using namespace std;

namespace func {
    string to_string( int value );
    string to_string(float value, int precision);

    float randf();
    void randSetFuse( unsigned int value );
}

#endif // FUNC_H

