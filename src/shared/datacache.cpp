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
    cache.m_rngSeeds.Load(file);

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

    cache.m_samples__1d.Save(datFile, txtFile, "Samples 1D");
    cache.m_rngSeeds.Save(datFile, txtFile, "RNG Seeds");

    fclose(datFile);
    fclose(txtFile);
}

std::mt19937& DataCacheRNGSeeds::GetRNG(const char* cacheKey)
{
    // make sure we use "the good stuff". yes, it matters if the not good stuff gets in, it's a big difference.
    // https://blog.demofox.org/2017/03/15/neural-network-recipe-recognize-handwritten-digits-with-95-accuracy/
    static std::random_device rd("dev/random");

    DataCacheRNGSeed& seed = m_seedLists[cacheKey];

    // if we haven't made the seed yet, make it
    if (!seed.seeded)
    {
        for (uint32_t& u : seed.seed)
            u = rd();
        seed.seeded = true;
    }

    // seed the rng the first time it's used in a run, else just let it keep going
    if (!seed.usedThisRun)
    {
        seed.usedThisRun = true;
        std::seed_seq fullSeed{ seed.seed[0], seed.seed[1], seed.seed[2], seed.seed[3], seed.seed[4], seed.seed[5], seed.seed[6], seed.seed[7], seed.seed[8] };
        seed.rng = std::mt19937(fullSeed);
    }

    // return the seeded rng
    return seed.rng;
};

bool DataCacheRNGSeeds::Load(FILE* file)
{
    // read how many keys there are
    uint32_t numKeys;
    if (!Read(file, numKeys))
        return false;

    // for each key...
    for (uint32_t keyIndex = 0; keyIndex < numKeys; ++keyIndex)
    {
        // read the key
        std::string key;
        if (!ReadString(file, key))
            return false;

        // read the seed
        DataCacheRNGSeed seed;
        seed.seeded = true;
        seed.usedThisRun = false;
        if (!Read(file, seed.seed))
            return false;

        // insert this key
        m_seedLists[key.c_str()] = seed;
    }

    return true;
}

void DataCacheRNGSeeds::Save(FILE* datFile, FILE* txtFile, const char* label) const
{
    fprintf(txtFile, "---------- %s ----------\r\n\r\n", label);

    // write how many keys there are
    Write(datFile, uint32_t(m_seedLists.size()));

    fprintf(txtFile, "  %zu keys\r\n", m_seedLists.size());

    // for each key...
    for (const auto& pair : m_seedLists)
    {
        // write the key
        WriteString(datFile, pair.first.c_str());

        // write the seed
        Write(datFile, pair.second.seed);

        // write the txtFile data
        fprintf(txtFile, "    %s  - %zu bytes\r\n", pair.first.c_str(), sizeof(pair.second.seed));
    }
}
