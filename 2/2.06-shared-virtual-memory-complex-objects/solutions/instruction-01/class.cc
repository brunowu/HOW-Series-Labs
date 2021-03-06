#include <cstdlib>
#include <cstdio>
#include <cstring>

class Person {
 public:
  char* c; // Pointer member - not bitwise-copyable

  Person() { c=NULL; } // Construct without memory allocation

  void Set(const char * name) {
    c=(char*) malloc(strlen(name)); // Memory alloc
    strcpy(c, name);
    printf("In  Set(): %s\n", c);
    fflush(stdout);
  }
};

Person someone;
char _Cilk_shared who[10];

_Cilk_shared void PrintString() {
#ifdef __MIC__
  printf("Who on coprocessor: %s\n", who);
#else
  printf("Who on CPU: %s\n", who);
#endif
}

int main(){
  strcpy(who, "Mary");
  PrintString();
  _Cilk_offload PrintString();
  someone.Set(who);
  printf("In main(): %s\n", someone.c);
}
