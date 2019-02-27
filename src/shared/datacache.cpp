/*
FILE: datacache.cpp
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/24/2019

Description:
Holds re-usable data on disk, such as expensive to create sampling patterns, to help runtime speed, and stability of results for randomized sequences.
*/

#include "datacache.h"
#include <stdint.h>


template <typename T>
static bool Write(FILE* file, const T& data)
{
    return fwrite(&data, sizeof(T), 1, file) == 1;
}

static bool WriteString(FILE* file, const char* string)
{
    return
        Write(file, uint32_t(strlen(string)+1)) &&
        fwrite(string, strlen(string) + 1, 1, file) == 1;
}

template <typename T>
static bool Read(FILE* file, T& data)
{
    return fread(&data, sizeof(data), 1, file) == 1;
}

static bool ReadString(FILE* file, std::string& string)
{
    uint32_t stringLength;
    if (!Read(file, stringLength))
        return false;

    string.resize(stringLength, 0);
    return fread((void*)string.data(), stringLength, 1, file) == 1;
}

void DataCache::Load()
{
    FILE* file = nullptr;
    fopen_s(&file, "datacache/cache.dat", "rb");
    if (!file)
        return;

    DataCache& cache = Instance();
    cache.m_samples__1d.Load(file);

    fclose(file);
}

void DataCache::Save()
{
    FILE* datFile = nullptr;
    FILE* txtFile = nullptr;
    fopen_s(&datFile, "datacache/cache.dat", "w+b");
    fopen_s(&txtFile, "datacache/cache.txt", "w+b");
    if (!datFile || !txtFile)
        return;

    const DataCache& cache = Instance();

    fprintf(txtFile, "---------- Samples 1D ----------\r\n\r\n");
    cache.m_samples__1d.Save(datFile, txtFile);

    fclose(datFile);
    fclose(txtFile);
}
