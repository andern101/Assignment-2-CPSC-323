#pragma once
#include "Parser.h"
#define PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <vector>

int recIndex = 0; //Keeps track of the records
bool printSw = true; //Determines if the rules are printed or not
bool reset = true;

std::vector<std::string> parseList;
std::string userLex;

std::vector<int> lineNum;
std::vector<std::string> token2;
int Iterator;

std::string lexerCall() {
    std::string tempRec;
    if (recIndex < parseList.size() - 1)
    {
        recIndex++;
        tempRec = parseList[recIndex];
        printSw = true;
        if (token2[recIndex] == "Invalid Input")
            lexerCall();
        return tempRec;
    }
    else
        exit(0);
    return 0;

}

void Printer()
{

}

void Rat20F(std::vector<std::string> lexemeVec, std::vector<int> count, std::vector<std::string> tokenVec, std::ofstream& fileout)
{
    userLex = lexemeVec[recIndex];
    parseList = lexemeVec;
    lineNum = count;
    token2 = tokenVec;
    Parse(userLex, fileout);
}

void Parse(std::string& userLex, std::ofstream& fileout)
{
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }
    if (userLex == "$$")
    {
        std::cout << "<RAT20F> -> <Opt Function Definitions>"
            << " $$ <Opt Declaration List> <Statement List>\n";
        fileout << "<RAT20F> -> <Opt Function Definitions>"
            << " $$ <Opt Declaration List> <Statement List>\n";
        userLex = lexerCall();
    }

    OptDeclarationList(userLex, fileout);
    StatementList(userLex, fileout);
}

//R2
void OptDeclarationList(std::string& userLex, std::ofstream& fileout)
{
    if (userLex == "integer" || userLex == "boolean")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Opt Declaration List> => <Declaration List>\n";
        fileout << "<Opt Declaration List> => <Declaration List>\n";
        //No lexer call. Not nonterminal.
        DeclarationList(userLex, fileout);
    }
    else {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Opt Declaration List> => <Empty>\n";
        fileout << "<Opt Declaration List> => <Empty>\n";
    } //Blank for nothing

}

//R3
void DeclarationList(std::string& userLex, std::ofstream& fileout)
{
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }
    std::cout << "<Declaration List> -> <Declaration> ; <Declaration List Prime>\n";
    fileout << "<Declaration List> -> <Declaration> ; <Declaration List Prime>\n";

    Declaration(userLex, fileout);

    if (userLex == ";")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        userLex = lexerCall();

        DeclarationListPrime(userLex, fileout);
    }
    else 
        if (userLex == ",")
        {
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            userLex = lexerCall();

            DeclarationList(userLex, fileout);
        } 
        else{
        std::cout << "Declaration List error, expected ;\n";
        fileout << "Declaration List error, expected ;\n";
        //system("Pause");
    }
}


void DeclarationListPrime(std::string& userLex, std::ofstream& fileout)
{
    if (userLex == "integer" || userLex == "boolean")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Declaration List Prime> -> <Declaration List> \n";
        fileout << "<Declaration List Prime> -> <Declaration List> \n";

        DeclarationList(userLex, fileout);
    }

    else
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Declaration List Prime> -> Epsilon \n";
        fileout << "<Declaration List Prime> -> Epsilon \n";
    }
}


void Declaration(std::string& userLex, std::ofstream& fileout)
{
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }

    std::cout << "<Declaration> -> <Qualifier>  <Identifier>\n";
    fileout << "<Declaration> -> <Qualifier>  <Identifier>\n";

    Qualifier(userLex, fileout);
    if (token2[recIndex] == "Identifier") {
        std::cout << "<Identifier>\n";
        std::cout << "Identifier detected " << parseList[recIndex] << "\n";
        fileout << "<Identifier>\n";
        fileout << "Identifier detected " << parseList[recIndex] << "\n";
        userLex = lexerCall();
    }
    else {
        std::cout << "Error, identifier expected\n" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error, identifier expected\n" << "Error at line " << lineNum[recIndex] << std::endl;
    }
}


void Qualifier(std::string& userLex, std::ofstream& fileout)
{
    if (userLex == "integer")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Qualifier> -> integer\n";
        fileout << "<Qualifier> -> integer\n";
        userLex = lexerCall();

    }
    else if (userLex == "boolean")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Qualifier> -> boolean\n";
        fileout << "<Qualifier> -> boolean\n";

        userLex = lexerCall();
    }
    else if (userLex == "," || userLex == ";")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        userLex = lexerCall();
    }
    else
    {
        std::cout << "Error: Qualifier expected.\n" << "Error at line " << lineNum[recIndex] << std::endl;
    }
}

void Identifier(std::string& userLex, std::ofstream& fileout) {
    if (token2[recIndex] == "Identifier")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }

        std::cout << "<Identifier> -> identifier\n";
        fileout << "<Identifier> -> identifier\n";
        userLex = lexerCall();
    }
}


void StatementList(std::string& userLex, std::ofstream& fileout) {

    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }
    std::cout << "<Statement List> -> <Statement> <Statement List Prime>\n";
    fileout << "<Statement List> -> <Statement> <Statement List Prime>\n";


    Statement(userLex, fileout);
    StatementListPrime(userLex, fileout);
}


void StatementListPrime(std::string& userLex, std::ofstream& fileout) { //?


    if (userLex == "if" || userLex == "fi" || userLex == "get" ||
        userLex == "put" || userLex == "while" || userLex == "{" || token2[recIndex] == "Identifier")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<StatementListPrime> -> <StatementList>\n";
        fileout << "<StatementListPrime> -> <StatementList>\n";
        userLex = lexerCall(); //added
        StatementList(userLex, fileout);
    }

    else {
        std::cout << "<Statement List Prime> -> Epsilon\n";
        fileout << "<Statement List Prime> -> Epsilon\n";

        userLex = lexerCall();
        Parse(userLex, fileout);
    }
}


void Statement(std::string& userLex, std::ofstream& fileout) {
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }

    if (userLex == "{")
    {
        std::cout << "<Statement> -> <Compound>>\n";
        fileout << "<Statement> -> <Compound>>\n";
        Compound(userLex, fileout);
    }
    else if (token2[recIndex] == "Identifier")
    {
        std::cout << "<Statement> -> <Assign>>\n";
        fileout << "<Statement> -> <Assign>>\n";
        Assign(userLex, fileout);
    }
    else if (userLex == "if")
    {
        std::cout << "<Statement> -> <if>\n";
        fileout << "<Statement> -> <if>\n";
        If(userLex, fileout);
    }
    else if (userLex == "get")
    {
        std::cout << "<Statement> -> <Get>\n";
        fileout << "<Statement> -> <Get>\n";
        Get(userLex, fileout);
    }
    else if (userLex == "put")
    {
        std::cout << "<Statement> -> <Put>\n";
        fileout << "<Statement> -> <Put>\n";
        Put(userLex, fileout);
    }
    else if (userLex == "while")
    {
        std::cout << "<Statement> -> <While>\n";
        fileout << "<Statement> -> <While>\n";
        While(userLex, fileout);
    }
}




void Compound(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "{") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Compound> -> {  <Statement List>  }\n";
        fileout << "<Compound> -> {  <Statement List>  }\n";

        userLex = lexerCall();
        StatementList(userLex, fileout);

        if (userLex == "}") {
            userLex = lexerCall();
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
        }
        else {
            std::cout << "Error: '}' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error: '}' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            //system("Pause");
        }
    }
    else {
        std::cout << "Error: '{' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error: '{' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        //system("Pause");
    }
}


void Assign(std::string& userLex, std::ofstream& fileout) {

    if (token2[recIndex] == "Identifier") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Assign> -> <Identifier> = <Expression> ;\n";
        fileout << "<Assign> -> <Identifier> = <Expression> ;\n";


        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }

        if (userLex == "=") {
            userLex = lexerCall();
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            Expression(userLex, fileout);
            if (userLex == ";") {
                if (printSw) {
                    std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    printSw = false;
                }
                userLex = lexerCall();
            }
            else
            {
                std::cout << "Error: ';' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                fileout << "Error: ';' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            }
        }
        else if (userLex == ";" || userLex == "," || userLex == "(" || userLex == ")" || userLex == "-" || userLex == "+" || userLex == "!=") {
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            userLex = lexerCall();
        }
        else if (token2[recIndex] == "Keyword") {
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            userLex = lexerCall();
        }
        else
        {
            std::cout << "Error: '=' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error: '=' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        }

    }
}



void If(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "if")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        if (userLex == "(") {
            userLex = lexerCall();

            Condition(userLex, fileout);
            if (userLex == ")") {
                userLex = lexerCall();
                Statement(userLex, fileout);
                if (userLex == "fi") {
                    if (printSw) {
                        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        std::cout << "<If> -> if  ( <Condition>  ) <Statement>   fi \n";
                        fileout << "<If> -> if  ( <Condition>  ) <Statement>   fi \n";
                        userLex = lexerCall();
                    }
                    else {
                        std::cout << "Error: 'fi' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                        fileout << "Error: 'fi' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                    }
                }
                else if (userLex == "otherwise")
                {
                    if (printSw) {
                        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        printSw = false;
                    }
                    userLex = lexerCall();
                    if (printSw) {
                        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        printSw = false;
                    }
                    Statement(userLex, fileout);
                    if (userLex == "fi")
                    {
                        std::cout << "if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi\n";
                        fileout << "if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi\n";
                        if (printSw) {
                            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                            printSw = false;
                        }
                        userLex = lexerCall();
                    }
                    else {
                        std::cout << "Error: 'fi' expected" << "Error at line " << lineNum[recIndex] << std::endl;
                        fileout << "Error: 'fi' expected" << "Error at line " << lineNum[recIndex] << std::endl;
                    }
                }
                else {
                    std::cout << "Error: 'otherwise' expected" << "Error at line " << lineNum[recIndex] << std::endl;
                    fileout << "Error: 'otherwise' expected" << "Error at line " << lineNum[recIndex] << std::endl;
                }
            }

            else {
                std::cout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                fileout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            }

        }
        else {
            std::cout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        }
    }
    else {
        std::cout << "Error: 'if' keyword expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error: 'if' keyword expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
    }
}


void Put(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "put") {
        std::cout << "<Put> ::=     put ( <identifier> );\n";
        fileout << "<Put> ::=     put ( <identifier> );\n";

        userLex = lexerCall();
    }

    if (userLex == "(") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        userLex = lexerCall();

        Identifier(userLex, fileout);
        if (userLex == "," || userLex == "(") {
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            Put(userLex, fileout);
        }
        else
        {
            if (userLex == ")") {
                do
                {
                    if (printSw) {
                        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                        printSw = false;
                    }
                    userLex = lexerCall();
                } while (userLex == ")");
            }
            else if (userLex != ";") {
                std::cout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                fileout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            }

            if (userLex == ";") {
                if (printSw) {
                    std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    printSw = false;
                }
                userLex = lexerCall();
            }
            else {
                std::cout << "Error: ';' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                fileout << "Error: ';' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            }
        }
    }
    else {
        std::cout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
    }

    
    

}


void Get(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "get") {
        std::cout << "<Get> ::=     get ( <Identifier> );\n";
        fileout << "<Get> ::=     get ( <Identifier> );\n";
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        userLex = lexerCall();

        if (userLex == "(") {
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            userLex = lexerCall();

            Identifier(userLex, fileout);

            if (userLex == ")") {
                if (printSw) {
                    std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    printSw = false;
                }
                userLex = lexerCall();
            }
            else {
                std::cout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                fileout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            }

            if (userLex == ";") {
                if (printSw) {
                    std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                    printSw = false;
                }
                userLex = lexerCall();
            }
            else {
                std::cout << "Error: ';' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
                fileout << "Error: ';' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            }
        }
        else {
            std::cout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        }
    }
    else {
        std::cout << "Error: 'get' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error: 'get' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
    }

}


void While(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "while") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<While> ::=  while ( <Condition>  )  <Statement>\n";
        fileout << "<While> ::=  while ( <Condition>  )  <Statement>\n";

        userLex = lexerCall();

        if (userLex == "(") { userLex = lexerCall(); }
        else {
            std::cout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error: '(' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        }

        Condition(userLex, fileout);

        if (userLex == ")") { userLex = lexerCall(); }
        else {
            std::cout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error: ')' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        }

        Statement(userLex, fileout);
    }
    else {
        std::cout << "Error: 'while' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error: 'while' expected\t\t" << "Error at line " << lineNum[recIndex] << std::endl;
    }

}


void Condition(std::string& userLex, std::ofstream& fileout) {
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }
    std::cout << "<Condition> ::=     <Expression>  <Relop>   <Expression>\n";
    fileout << "<Condition> ::=     <Expression>  <Relop>   <Expression>\n";
    Expression(userLex, fileout);
    Relop(userLex, fileout);
    Expression(userLex, fileout);
}



void Relop(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "==") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Relop> -> ==" << "\n";
        fileout << "<Relop> -> ==" << "\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else if (userLex == ">") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Relop> -> >" << "\n";
        fileout << "<Relop> -> >" << "\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else if (userLex == "<") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Relop> -> <" << "\n";
        fileout << "<Relop> -> <" << "\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else if (userLex == "<=") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Relop> -> <=" << "\n";
        fileout << "<Relop> -> <=" << "\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else if (userLex == "=>") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Relop> -> =>" << "\n";
        fileout << "<Relop> -> =>" << "\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "Error, expected an operator '==', ,'<=', '=>', '>', or '<'\n" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error, expected an operator '==', ,'<=', '=>', '>', or '<'\n" << "Error at line " << lineNum[recIndex] << std::endl;
        //system("Pause");
    }
}



void Expression(std::string& userLex, std::ofstream& fileout)
{
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }
    std::cout << "<Expression> -> <Term> <Expression Prime>\n";
    fileout << "<Expression> -> <Term> <Expression Prime>\n";
    Term(userLex, fileout);

    ExpressionPrime(userLex, fileout);

}

void ExpressionPrime(std::string& userLex, std::ofstream& fileout) {
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }

    if (userLex == "+")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Expression Prime>-> + <Term> <Expression Prime>\n";
        fileout << "<Expression Prime>-> + <Term> <Expression Prime>\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        Term(userLex, fileout);
        ExpressionPrime(userLex, fileout);
    }
    else if (userLex == "-")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Expression Prime> -> - <Term> <Expression Prime>\n";
        fileout << "<Expression Prime> -> - <Term> <Expression Prime>\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        Term(userLex, fileout);
        ExpressionPrime(userLex, fileout);
    }
    else {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Expression Prime> -> Epsilon\n";
        fileout << "<Expression Prime> -> Epsilon\n";
    }
}


void Term(std::string& userLex, std::ofstream& fileout) {
    if (printSw) {
        std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
        printSw = false;
    }
    std::cout << "<Term> -> <Factor> <Term Prime>\n";
    fileout << "<Term> -> <Factor> <Term Prime>\n";
    Factor(userLex, fileout);
    TermPrime(userLex, fileout);
}



void TermPrime(std::string& userLex, std::ofstream& fileout)
{
    if (userLex == "*")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Term Prime> -> * <Factor> <Term Prime>\n";
        fileout << "<Term Prime> -> * <Factor> <Term Prime>\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        Factor(userLex, fileout);
        TermPrime(userLex, fileout);
    }
    else if (userLex == "/")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Term Prime> -> * <Factor> <Term Prime>\n";
        fileout << "<Term Prime> -> * <Factor> <Term Prime>\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        Factor(userLex, fileout);
        TermPrime(userLex, fileout);
    }
    else
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Term Prime> -> Epsilon\n";
        fileout << "<Term Prime> -> Epsilon\n";
    }
}



void Factor(std::string& userLex, std::ofstream& fileout) {
    if (userLex == "-")
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Factor> -> - <Primary>\n";
        fileout << "<Factor> -> - <Primary>\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        Primary(userLex, fileout);
    }
    else
    {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Factor> -> <Primary>\n";
        fileout << "<Factor> -> <Primary>\n";
        Primary(userLex, fileout);
    }
}


void Primary(std::string& userLex, std::ofstream& fileout) {


    if (token2[recIndex] == "Identifier")
    {
        std::cout << "<Primary> -> <Identifier>\n";
        fileout << "<Primary> -> <Identifier>\n";
        userLex = lexerCall();
    }
    else if (token2[recIndex] == "Integer")
    {
        std::cout << "<Primary> -> <Integer>\n";
        fileout << "<Primary> -> <Integer>\n";
        userLex = lexerCall(); //?
    }
    else if (token2[recIndex] == "Real")
    {
        std::cout << "<Primary> -> <Real>\n";
        fileout << "<Primary> -> <Real>\n";
        userLex = lexerCall(); //?
    }
    else if (userLex == "(")
    {
        std::cout << "<Primary> -> (<Expression>)\n";
        fileout << "<Primary> -> (<Expression>)\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        Expression(userLex, fileout);
        if (userLex == ")")
        {
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
            userLex = lexerCall();
            if (printSw) {
                std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
                printSw = false;
            }
        }
        else {
            std::cout << "Error, expected a )" << "\n" << "Error at line " << lineNum[recIndex] << std::endl;
            fileout << "Error, expected a )" << "\n" << "Error at line " << lineNum[recIndex] << std::endl;
            //system("Pause");
        }
    }
    else if (userLex == "true") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Primary> -> true\n";
        fileout << "<Primary> -> true\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else if (userLex == "false") {
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
        std::cout << "<Primary> -> false\n";
        fileout << "<Primary> -> false\n";
        userLex = lexerCall();
        if (printSw) {
            std::cout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            fileout << "Lexeme: " << parseList[recIndex] << "\t\tToken: " << token2[recIndex] << "\n";
            printSw = false;
        }
    }
    else {
        std::cout << "Error, expected either identifier, integer, real, expression, true or false \n" << "Error at line " << lineNum[recIndex] << std::endl;
        fileout << "Error, expected either identifier, integer, real, expression, true or false \n" << "Error at line " << lineNum[recIndex] << std::endl;

    }
}
