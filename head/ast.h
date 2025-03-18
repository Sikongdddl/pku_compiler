#ifndef AST_H
#define AST_H

#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

/*
We have EBNF in following ways:
CompUnit  ::= FuncDef;

FuncDef   ::= FuncType IDENT "(" ")" Block;
FuncType  ::= "int";

Block     ::= "{" Stmt "}";
Stmt      ::= "return" Number ";";
Number    ::= INT_CONST;
*/ 

class BaseAST{
public:
    virtual ~BaseAST() = default;
    virtual void Traverse() const = 0;
};

class CompUnitAST : public BaseAST{
public:
    std::unique_ptr<BaseAST> func_def;
    void Traverse() const override{
        std::cout<<"CompUnitAST { ";
        func_def -> Traverse();
        std::cout<<" } ";
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
};

class FuncTypeAST : public BaseAST{
public:
    std::string TypeString = "int";
    void Traverse() const override{
        std::cout<<" FuncTypeAST { ";
        std::cout<<" "<<TypeString<<" ";
        std::cout<<" } ";
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
};

class StmtAST : public BaseAST{
public:
    int number;
    void Traverse() const override{
        std::cout<<" StmtAST { ";
        std::cout<<number;
        std::cout<<" } ";
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