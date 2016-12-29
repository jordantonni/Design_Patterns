#include "stdafx.h"
#pragma once
using namespace std;

struct Document;

struct IMachine
{
    virtual void print(vector<Document*> docs) = 0;
    virtual void scan(vector<Document*> docs) = 0;
    virtual void fax(vector<Document*> docs) = 0;
};

/*
 * Forces recompile of full class on single method change
 * Client may only need single method, but interface forces all to be made
 */
struct MFP : IMachine
{
    void print(vector<Document*> docs) override;
    void scan(vector<Document*> docs) override;
    void fax(vector<Document*> docs) override;
};


// --------------------------------------------------------------------------------------------//

//ISP

/*
 * Break up monolithic interface into smaller Interfaces for each part of the functionality
 */
struct IPrinter
{
    virtual void print(vector<Document*> docs) = 0;
};

struct IScanner
{
    virtual void scan(vector<Document*> docs) = 0;
};

struct Printer : IPrinter
{
    void print(vector<Document*> docs) override;
};

struct Scanner : IScanner
{
    void scan(vector<Document*> docs) override;
};

/*
 * If you need the larger interface that specifices all the fucntionalty,
 * Use multiple inhertiance of each smaller interface to define a new composited interface
 */
struct IMonolithicMachine : IPrinter, IScanner {};

/*
 * Use decorater pattern for the concrete realisation of that monolithic interface
 */
struct MonolithicMachine : IMonolithicMachine
{
    IPrinter& printer;
    IScanner& scanner;

    explicit MonolithicMachine(IPrinter& printer, IScanner& scanner)
        : printer(printer)
        , scanner(scanner) {}

    void print(vector<Document*> docs) override
    {
        printer.print(docs);
    }

    void scan(vector<Document*> docs) override
    {
        scanner.scan(docs);
    }
};

void ISP_TEST() { }
