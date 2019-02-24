/*
FILE: datacache.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/24/2019

Description:
Holds re-usable data on disk, such as expensive to create sampling patterns, to help runtime speed, and stability of results for randomized sequences.
*/

#pragma once

#include <unordered_map>

class DataCache
{
private:
    DataCache();

public:
    static void Load();
    static void Save();

    static DataCache& Instance() {
        static DataCache cache;
        return cache;
    }
};