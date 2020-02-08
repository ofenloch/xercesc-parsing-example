#include <mainlib.h>

CHello::CHello () {
    m_Greeting = "Class CHello, says \"Hi!\".";
}
void CHello::sayHello() {
    std::cout << m_Greeting << std::endl;
}
void CHello::sayHello(const std::string& Greeting) {
    std::cout << Greeting << std::endl;
}

