#include "validator.h"

void run() {
    Arg("notie", false);
    int x = Int(2, 4); Space();
    int y = Int(2, 3); Endl();
    for (int i = 0; i < 4; i++) {
        Int(0, 25); Space();
        Int(0, 5); Endl();
    }
    // TODO: no tie group
    Eof();
}
