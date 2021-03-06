// Copyright (c) 2001 Syntext, Inc. All Rights Reserved.
//
/*! \file
    Test of fixed decimal arithmetic type (FixedDecimal)
 */
#include "common/common_defs.h"
#include "common/FixedDecimal.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

CVSID(FIXED_TEST_CPP, "");

USING_COMMON_NS
using namespace std;

int
main(int ac, char **av)
{
    char cmd[256];
    FixedDecimal x, y, fr;
    int64 ir;
    double dr;
    char result[256];
    enum {
        NEG = 0200, NOP,
        EQ, NE, GE, LE,
        SETNAN
    };
    int op = 0;
    int iarg = 0;
    char *p;
    int errcnt = 0;
    istream *in = &cin;
    ostream *record = 0;
    int manual = 1;

    //
    // If argument is given, treat it as a file name
    //
    if (ac > 1) {
        in = new ifstream(av[1]);

        if (!in) {
            cerr << "Cannot open test data file " << av[1] << " for reading\n";
            exit(100);
        }
        manual = 0;
    }
    else {
        cout << "? ";
        record = new ofstream("fixed.tmp", ofstream::app);
        if (!record)
            cerr << "Warning: cannot open recorder file fixed.tmp\n";
        else {
            time_t t = time(0);
            *record << "# MANUAL TEST DATA INPUT: " << ctime(&t);
        }
    }

    while( in->getline(cmd, sizeof cmd) ) {
        // Isolate the command
        p = cmd;
        while (!isspace(*p) && *p)
             p++;

        try {
            //
            // Parse the command and operands
            //
            op = cmd[0];
            switch (op) {
            case 0:
            case '#':       // Comment...
                if (manual)
                    cout << "? ";
                continue;

            case 'q':
                exit(0);

            default:
            error:
                cerr << "*** Unknown test command '" << cmd << "'\n";
                errcnt++;
                if (manual)
                    cout << "? ";
                continue;

            case '>':
                switch (cmd[1]) {
                default:
                    goto error;

                case '=':
                    op = GE;
                    break;

                case ' ':
                    break;
                }
                goto binary;

            case '<':
                switch (cmd[1]) {
                default:
                    goto error;

                case '=':
                    op = LE;
                    break;

                case ' ':
                    break;
                }
                goto binary;

            case '=':
                if (cmd[1] == '=') {
                    op = EQ;
                    goto binary;
                }
                goto error;

            case '!':
                if (cmd[1] == '=') {
                    op = NE;
                    goto binary;
                }
                goto error;

            case '+':
            case '-':
            case '*':
            case '/':
            case '?':
                if (cmd[1] != ' ')
                    goto error;

            binary:
                p = &p[x.fromString(p)];
                p = &p[y.fromString(p)];
                break;

            case 'm':
            case 'd':
                p = &p[x.fromString(p)];
                p = &p[y.fromString(p)];
                iarg = strtol(p, &p, 10);
                break;

            case '^':
                p = &p[x.fromString(p)];
                iarg = strtol(p, &p, 10);
                break;

            case 'u':
                switch (cmd[1]) {
                default:
                    goto error;

                case '+': op = NOP; break;
                case '-': op = NEG; break;
                }
                p = &p[x.fromString(p)];
                break;

            case 'c':
            case 'f':
            case 't':
            case 'r':
                p = &p[x.fromString(p)];
                break;

            case 'F':
                iarg = strtol(p, &p, 10);
                p = &p[x.fromString(p, iarg)];
                break;

            case 'T':
                iarg = strtol(p, &p, 10);
                p = &p[x.fromString(p)];
                break;

            case 'n':
                op = SETNAN;
                break;
            }

            switch( op ) {
            // FixedDecimal-point result
            case 'm':   fr = mul(x, y, iarg); goto f_res;
            case 'd':   fr = div(x, y, iarg); goto f_res;
            case NEG:   fr = -x; goto f_res;
            case NOP:   fr = +x; goto f_res;
            case SETNAN: fr.setNaN(); goto f_res;
            case '+':   fr = x + y; goto f_res;
            case '-':   fr = x - y; goto f_res;
            case '*':   fr = x * y; goto f_res;
            case '/':   fr = x / y; goto f_res;
            case '^':   fr = x ^ iarg; goto f_res;
            case 'F':   fr = x;
            f_res:
                fr.toString(result, sizeof result);
                break;

            // Integer result
            case '>':   ir = (x > y); goto i_res;
            case '<':   ir = (x < y); goto i_res;
            case EQ:    ir = (x == y); goto i_res;
            case NE:    ir = (x != y); goto i_res;
            case GE:    ir = (x >= y); goto i_res;
            case LE:    ir = (x <= y); goto i_res;
            case '?':   ir = compare(x, y); goto i_res;
            case 'c':   ir = x.ceil(); goto i_res;
            case 'f':   ir = x.floor(); goto i_res;
            case 'r':   ir = x.round(); goto i_res;
            case 't':   ir = x.trunc();
            i_res:
#if defined (_WINDOWS_)
                _snprintf(result, sizeof result, "%I64d", ir);
#else
                snprintf(result, sizeof result, "%lld", ir);
#endif
                break;

            // Double result
            case 'e':
                dr = x;
#if defined (_WINDOWS_)
                _snprintf(result, sizeof result, "%10g", dr);
#else
                snprintf(result, sizeof result, "%10g", dr);
#endif
                break;

            // Result with length
            case 'T':
                if (iarg > (int)(sizeof result) || iarg < 0)
                    iarg = sizeof result;
                x.toString(result, iarg);
                break;

            default:
                cerr << "*** Unknown op: " << cmd << "\n";
                errcnt++;
            }
        }
        catch (NumericError &err) {
            static const char* EIDS[] = {
                    "NAN", "OVERFLOW", "UNDERFLOW", "ZERODIV",
                    "BIGNUM", "BADNUM", "CONVARG",
            };

            strcpy(result, EIDS[err.getErrorType()]);
        }

        if (record) {
            *record << cmd << " : " << result << "\n";
            record->flush();
        }

        if (manual) {
            cout << "result: '" << result << "'\n";
            cout << "? ";
        }
        else {
            // End of string is the expected result
            p = strchr(cmd, ':');
            if (!p) {
                cerr << "*** Missing expected value: '" << cmd << "'\n";
                errcnt++;
            }
            else {
                while (isspace(*++p))
                    ;

                if (strcmp(result, p)) {
                    cerr << "MISMATCH: " << cmd << "\n";
                    cerr << "      result: '" << result << "'\n";
                    cerr << "    expected: '" << p << "'\n";
                    errcnt++;
                }
            }
        }
    }
    if (!manual && errcnt == 0)
        cerr << "FixedDecimal test passed.\n";
    exit(errcnt != 0);
}
