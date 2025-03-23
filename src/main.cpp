#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include "../head/ast.h"
#include "../head/koopaUtil.h"
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
    yyout = freopen(output,"w",stdout);

    assert(yyin);

    unique_ptr<BaseAST> ast;
    auto ret = yyparse(ast);
    assert(!ret);
    // cout << *ast << endl;
    // ast -> Traverse();
    vector<string> res = ast -> toIR();
    
    for(int i = 0; i < res.size(); ++i){
        cout<<res[i]<<endl;
    }
    
    koopa_program_t program;
    koopa_error_code_t ir_ret = koopa_parse_from_file("./hello.o", &program);
    assert(ir_ret == KOOPA_EC_SUCCESS);
    koopa_raw_program_builder_t builder = koopa_new_raw_program_builder();
    koopa_raw_program_t raw = koopa_build_raw_program(builder, program);

    koopa_delete_program(program);

    //do sth to raw program
    Visit(raw);
    koopa_delete_raw_program_builder(builder);
    fclose(stdout);
    return 0;

}
