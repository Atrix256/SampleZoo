/*
FILE: datacache.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/24/2019

Description:
Holds re-usable data on disk, such as expensive to create sampling patterns, to help runtime speed, and stability of results for randomized sequences.
*/

#include "datacache.h"

void DataCache::Load()
{
    FILE* file = nullptr;
    fopen_s(&file, "datacache/cache.dat", "rb");
    if (!file)
        return;

    // TODO: read

    fclose(file);
}

void DataCache::Save()
{
    FILE* file = nullptr;
    fopen_s(&file, "datacache/cache.dat", "w+b");
    if (!file)
        return;

    // TODO: write

    fclose(file);
}
