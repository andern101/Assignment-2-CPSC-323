#pragma once

//pragma once to avoid creating a new class
//was giving me issues implementing when i tried creating a new one
//this way it only run this header file whenever the program compiles

#define PARSER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void Rat20F(std::vector<std::string> lexemeVec, std::vector<int> count, std::vector<std::string> tokenVec, std::ofstream& output);
void Parse(std::string& analyzerlexeme, std::ofstream& output);
void OptDeclarationList(std::string& analyzerlexeme, std::ofstream& output);
void DeclarationList(std::string& analyzerlexeme, std::ofstream& output);
void DeclarationListPrime(std::string& analyzerlexeme, std::ofstream& output);
void Declaration(std::string& analyzerlexeme, std::ofstream& output);
void Qualifier(std::string& analyzerlexeme, std::ofstream& output);
void StatementList(std::string& analyzerlexeme, std::ofstream& output);
void Statement(std::string& analyzerlexeme, std::ofstream& output);
void StatementListPrime(std::string& analyzerlexeme, std::ofstream& output);
void Compound(std::string& analyzerlexeme, std::ofstream& output);
void Assign(std::string& analyzerlexeme, std::ofstream& output);
void If(std::string& analyzerlexeme, std::ofstream& output);
void Get(std::string& analyzerlexeme, std::ofstream& output);
void Put(std::string& analyzerlexeme, std::ofstream& output);
void While(std::string& analyzerlexeme, std::ofstream& output);
void Condition(std::string& analyzerlexeme, std::ofstream& output);
void Relop(std::string& analyzerlexeme, std::ofstream& output);

void Expression(std::string& analyzerlexeme, std::ofstream& output);
void ExpressionPrime(std::string& analyzerlexeme, std::ofstream& output);
void Term(std::string& analyzerlexeme, std::ofstream& output);
void TermPrime(std::string& analyzerlexeme, std::ofstream& output);
void Factor(std::string& analyzerlexeme, std::ofstream& output);
void Primary(std::string& analyzerlexeme, std::ofstream& output);


void Empty(std::string& analyzerlexeme, std::ofstream& output);

char things;
std::vector<std::string> token, lexeme;
