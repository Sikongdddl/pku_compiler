#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "../head/ast.h"

using namespace std;

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(unique_ptr<BaseAST> &ast);

int main(int argc, const char *argv[]){
    assert(argc == 5);
    auto mode = argv[1];
    auto input = argv[2];
    auto output = argv[4];

    yyin = fopen(input, "r");
    yyout = freopen(output,"w",stdout);

    assert(yyin);

    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(!ret);
    // cout << *ast << endl;
    // ast -> Traverse();
    ast -> toIR();
    fclose(stdout);
    return 0;

}
