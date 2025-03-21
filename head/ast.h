#ifndef AST_H
#define AST_H

#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*
We have EBNF in following ways:
CompUnit  ::= FuncDef;

FuncDef   ::= FuncType IDENT "(" ")" Block;
FuncType  ::= "int";

Block     ::= "{" Stmt "}";
Stmt      ::= "return" Number ";";
Number    ::= INT_CONST;
*/ 
using namespace std;

class BaseAST{
public:
    virtual ~BaseAST() = default;
    virtual void Traverse() const = 0;
    virtual vector<string> toIR() const = 0;
};

class CompUnitAST : public BaseAST{
public:
    std::unique_ptr<BaseAST> func_def;
    void Traverse() const override{
        std::cout<<"CompUnitAST { ";
        func_def -> Traverse();
        std::cout<<" } ";
    }
    vector<string> toIR() const override{
        return func_def -> toIR();
    }
};

class FuncDefAST : public BaseAST{
public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;
    void Traverse() const override{
        std::cout<<" FuncDefAST { ";
        func_type -> Traverse();
        std::cout<<" , " << ident << ", ";
        block->Traverse();
        std::cout<<" } ";
    }

    vector<string> toIR() const override{
        vector<string> res;
        string headline = "fun @" + ident + "(): i32 {";
        res.push_back(headline);
        vector<string> block_res = block -> toIR();
        for(int i = 0; i < block_res.size(); ++i){
            res.push_back(block_res[i]);
        }
        string endline = "}";
        res.push_back(endline);
        return res;
    }
};

class FuncTypeAST : public BaseAST{
public:
    std::string TypeString = "int";
    void Traverse() const override{
        std::cout<<" FuncTypeAST { ";
        std::cout<<" "<<TypeString<<" ";
        std::cout<<" } ";
    }

    vector<string> toIR() const override{
        vector<string> res;
        return res;
    }
};

class BlockAST : public BaseAST{
public:
    std::unique_ptr<BaseAST> stmt;
    void Traverse() const override{
        std::cout<<" BlockAST { ";
        stmt->Traverse();
        std::cout<<"}";
    }

    vector<string> toIR() const override{
        vector<string> res;
        string headline = "%entry:";
        res.push_back(headline);
        vector<string> stmt_res = stmt->toIR();
        for(int i = 0; i < stmt_res.size(); ++i){
            res.push_back(stmt_res[i]);
        }
        return res;
    }
};

class StmtAST : public BaseAST{
public:
    int number;
    void Traverse() const override{
        std::cout<<" StmtAST { ";
        std::cout<<number;
        std::cout<<" } ";
    }

    vector<string> toIR() const override{
        vector<string> res;
        string headline = "  ret " + to_string(number);
        res.push_back(headline);
        return res;
    }
};

// class NumberAST : public BaseAST{
// public:
//     std::int64_t number_int;
//     void Traverse() const override{
//         std::cout<<" "<<number_int<<" ";
//     }
// };

#endif