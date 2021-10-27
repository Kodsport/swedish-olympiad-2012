/* Utility functions for writing output validators for the Kattis
 * problem format.
 *
 * The primary functions and variables available are the following.
 * In many cases, the only functions needed are "init_io",
 * "wrong_answer", and "accept".
 *
 * - init_io(argc, argv):
 *        initialization
 *
 * - judge_in, judge_ans, author_out:
 *        std::istream objects for judge input file, judge answer
 *        file, and submission output file.
 *
 * - accept():
 *        exit and give Accepted!
 *
 * - accept_with_score(double score):
 *        exit with Accepted and give a score (for scoring problems)
 *
 * - judge_message(const char* msg, ...):
 *        printf-style function for emitting a judge message (a
 *        message that gets displayed to a privileged user with access
 *        to secret data etc).
 *
 * - wrong_answer(const char* msg, ...):
 *        printf-style function for exitting and giving Wrong Answer,
 *        and emitting a judge message (which would typically explain
 *        the cause of the Wrong Answer)
 *
 * - judge_error(const char* msg, ...):
 *        printf-style function for exitting and giving Judge Error,
 *        and emitting a judge message (which would typically explain
 *        the cause of the Judge Error)
 *
 * - author_message(const char* msg, ...):
 *        printf-style function for emitting an author message (a
 *        message that gets displayed to the author of the
 *        submission).  (Use with caution, and be careful not to let
 *        it leak information!)
 *
 */
#pragma once

#include <sys/stat.h>
#include <cassert>
#include <cstdarg>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

typedef void (*feedback_function)(const char*, ...);

const int EXITCODE_AC = 42;
const int EXITCODE_WA = 43;
const std::string FILENAME_AUTHOR_MESSAGE = "teammessage.txt";
const std::string FILENAME_JUDGE_MESSAGE = "judgemessage.txt";
const std::string FILENAME_JUDGE_ERROR = "judgeerror.txt";
const std::string FILENAME_SCORE = "score.txt";

#define USAGE "%s: judge_in judge_ans feedback_dir < author_out\n"

std::ifstream judge_in, judge_ans;
std::istream author_out(std::cin.rdbuf());

char *feedbackdir = NULL;

void vreport_feedback(const std::string &category,
                      const char* msg,
                      va_list pvar) {
	// First print the message to stderr, to aid debugging.
	va_list pvar2;
	va_copy(pvar2, pvar);
	fprintf(stderr, "%s: ", category.c_str());
	vfprintf(stderr, msg, pvar2);
	fprintf(stderr, "\n");
	va_end(pvar2);
	// Then print it to the expected file.
    std::ostringstream fname;
    if (feedbackdir)
        fname << feedbackdir << '/';
    fname << category;
    FILE *f = fopen(fname.str().c_str(), "a");
    assert(f);
    vfprintf(f, msg, pvar);
    fclose(f);
}

void report_feedback(const std::string &category, const char* msg, ...) {
    va_list pvar;
    va_start(pvar, msg);
    vreport_feedback(category, msg, pvar);
	va_end(pvar);
}

void author_message(const char* msg, ...) {
    va_list pvar;
    va_start(pvar, msg);
    vreport_feedback(FILENAME_AUTHOR_MESSAGE, msg, pvar);
	va_end(pvar);
}

void judge_message(const char* msg, ...) {
    va_list pvar;
    va_start(pvar, msg);
    vreport_feedback(FILENAME_JUDGE_MESSAGE, msg, pvar);
	va_end(pvar);
}

[[noreturn]]
void wrong_answer(const char* msg, ...) {
    va_list pvar;
    va_start(pvar, msg);
    vreport_feedback(FILENAME_JUDGE_MESSAGE, msg, pvar);
	va_end(pvar);
    exit(EXITCODE_WA);
}

[[noreturn]]
void judge_error(const char* msg, ...) {
    va_list pvar;
    va_start(pvar, msg);
    vreport_feedback(FILENAME_JUDGE_ERROR, msg, pvar);
	va_end(pvar);
	abort();
	exit(1);
}

[[noreturn]]
void accept() {
    exit(EXITCODE_AC);
}

[[noreturn]]
void accept_with_score(double scorevalue) {
    report_feedback(FILENAME_SCORE, "%.9le", scorevalue);
    exit(EXITCODE_AC);
}


bool is_directory(const char *path) {
    struct stat entry;
    return stat(path, &entry) == 0 && S_ISDIR(entry.st_mode);
}

void init_io(int argc, char **argv) {
    if(argc < 4) {
        fprintf(stderr, USAGE, argv[0]);
        judge_error("Usage: %s judgein judgeans feedbackdir [opts] < userout", argv[0]);
    }

    // Set up feedbackdir first, as that allows us to produce feedback
    // files for errors in the other parameters.
    if (!is_directory(argv[3])) {
        judge_error("%s: %s is not a directory\n", argv[0], argv[3]);
    }
    feedbackdir = argv[3];

    judge_in.open(argv[1], std::ios_base::in);
    if (judge_in.fail()) {
        judge_error("%s: failed to open %s\n", argv[0], argv[1]);
    }

    judge_ans.open(argv[2], std::ios_base::in);
    if (judge_ans.fail()) {
        judge_error("%s: failed to open %s\n", argv[0], argv[2]);
    }

    author_out.rdbuf(std::cin.rdbuf());
}
