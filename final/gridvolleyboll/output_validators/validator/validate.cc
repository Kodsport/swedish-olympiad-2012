#include <vector>
#include <tuple>
#include <cstring>
#include <cmath>
#include "validate.h"

using namespace std;

int main(int argc, char **argv) {
    init_io(argc, argv);

    string judgeResult;
    int judgeDtw = -1;
    judge_ans >> judgeResult;
    if (judgeResult != "tie") judge_ans >> judgeDtw;

    string teamResult;
    int teamDtw = -1;
    if (!(cin >> teamResult)) wrong_answer("could not parse result!");

    if (!std::equal(judgeResult.begin(), judgeResult.end(), teamResult.begin(), teamResult.end(), [](char a, char b) { return tolower(a) == tolower(b); })) {
        wrong_answer("incorrect result");
    }

    if (judgeResult != "tie" && !(cin >> teamDtw) && !cin.eof()) {
        // OK if this fails beacause of EOF to be nice
        wrong_answer("could not read depth to win");
    }
    string trail;
    if (cin >> trail) wrong_answer("trailing output");

    if (argc == 5 && string(argv[4]) == "sample") {
        accept_with_score(0);
        }

    if (judgeResult != "tie" && teamDtw != judgeDtw) {
        accept_with_score(30);
    } else {
        accept_with_score(50);
    }
}
