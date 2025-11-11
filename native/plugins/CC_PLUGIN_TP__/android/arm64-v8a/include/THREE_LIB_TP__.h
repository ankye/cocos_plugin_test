#pragma once
#ifndef THREE_LIB_TP___H
#define THREE_LIB_TP___H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class THREE_LIB_TP__
{
private:
    std::string _version = "0.0.1";

public:
    THREE_LIB_TP__();
    ~THREE_LIB_TP__();
    const char *createBuffer(int size);
    void version();
};

#endif