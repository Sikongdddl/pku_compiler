#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "../head/ast.h"
#include "koopa.h"

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
    //yyout = freopen(output,"w",stdout);

    assert(yyin);

    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(!ret);
    // cout << *ast << endl;
    // ast -> Traverse();
    vector<string> res = ast -> toIR();
    
    // for(int i = 0; i < res.size(); ++i){
    //     cout<<res[i]<<endl;
    // }
    //fclose(stdout);
    koopa_program_t program;
    koopa_error_code_t ret = koopa_parse_from_string(res, &program);
    assert(ret == KOOPA_EC_SUCCESS);
    return 0;

}
