#include <main.h>

int main(int argc, char *argv[])
{
  CHello myGreeter;

  myGreeter.sayHello();

  myGreeter.sayHello("Hello, World!");
  
  return 0;
} // int main(int argc, char *argv[])