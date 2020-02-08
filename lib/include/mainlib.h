#ifndef _MAIN_LIB_H_
#define _MAIN_LIB_H_

#include <iostream>
#include <iomanip>
#include <string>

class CHello {
    private:
    std::string m_Greeting;

    public:
    CHello();
    void sayHello();
    void sayHello(const std::string& Greeting);
};

#endif // #ifndef _MAIN_LIB_H_