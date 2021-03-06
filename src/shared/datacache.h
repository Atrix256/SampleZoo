/*
FILE: datacache.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/24/2019

Description:
Holds re-usable data on disk, such as expensive to create sampling patterns, to help runtime speed, and stability of results for randomized sequences.
*/

#pragma once

#include <map>
#include <vector>
#include <random>

#include "vector.h"

template <typename T>
struct DataList
{
    bool saveKey = false;   // everything uses cached samples in memory.  If this is true, it will save to disk to be loaded next time.
    size_t m_uniqueIndex = 1;

    typedef std::vector<T> TData;
    std::vector<TData> m_dataLists;
};

template <typename T>
struct DataCacheFamily
{
    // a map, not an unordered_map because order matters. If the order changes, then cache.dat is different and means a huge file upload.
    std::map<std::string, DataList<T>> m_dataLists;

    template <typename SAMPLE_FN>
    void GetSamples_Progressive(const char* cacheKey, const SAMPLE_FN& SampleFn, std::vector<T>& values, size_t numValues, bool wantUnique, bool randomized)
    {
        static std::mt19937 dummy;
        std::mt19937& rng = randomized ? DataCache::Instance().m_rngSeeds.GetRNG(cacheKey) : dummy;

        DataList<T>& dataList = m_dataLists[cacheKey];

        size_t dataListIndex = 0;
        if (wantUnique)
        {
            dataListIndex = dataList.m_uniqueIndex;
            dataList.m_uniqueIndex++;
        }

        if (dataList.m_dataLists.size() <= dataListIndex)
            dataList.m_dataLists.resize(dataListIndex + 1);

        DataList<T>::TData& samples = dataList.m_dataLists[dataListIndex];
        if (samples.size() < numValues)
            SampleFn(samples, numValues, rng);

        values.resize(numValues);
        memcpy(values.data(), samples.data(), sizeof(T) * numValues);
    }

    template <typename SAMPLE_FN>
    void GetSamples_NonProgressive(const char* cacheKey_, const SAMPLE_FN& SampleFn, std::vector<T>& values, size_t numValues, bool wantUnique, bool randomized)
    {
        static std::mt19937 dummy;
        std::mt19937& rng = randomized ? DataCache::Instance().m_rngSeeds.GetRNG(cacheKey_) : dummy;

        char cacheKey[256];
        sprintf(cacheKey, "%s_%zu", cacheKey_, numValues);

        DataList<T>& dataList = m_dataLists[cacheKey];

        size_t dataListIndex = 0;
        if (wantUnique)
        {
            dataListIndex = dataList.m_uniqueIndex;
            dataList.m_uniqueIndex++;
        }

        if (dataList.m_dataLists.size() <= dataListIndex)
            dataList.m_dataLists.resize(dataListIndex + 1);

        DataList<T>::TData& samples = dataList.m_dataLists[dataListIndex];
        if (samples.size() != numValues)
            SampleFn(samples, numValues, rng);

        values.resize(numValues);
        memcpy(values.data(), samples.data(), sizeof(T) * numValues);
    }

    bool Load(FILE* file)
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

            // read how many data lists there are
            uint32_t numDataLists;
            if (!Read(file, numDataLists))
                return false;

            // for each data list...
            DataList<T> dataLists;
            dataLists.m_dataLists.resize(numDataLists);
            for (uint32_t dataListIndex = 0; dataListIndex < numDataLists; ++dataListIndex)
            {
                // write how many items there is in this data list
                uint32_t numDataItems;
                if (!Read(file, numDataItems))
                    return false;

                std::vector<T>& dataList = dataLists.m_dataLists[dataListIndex];
                dataList.resize(numDataItems);
                for (uint32_t dataItemIndex = 0; dataItemIndex < numDataItems; ++dataItemIndex)
                {
                    if (!Read(file, dataList[dataItemIndex]))
                        return false;
                }
            }

            // insert this key
            m_dataLists[key.c_str()] = dataLists;
        }

        return true;
    }

    void Save(FILE* datFile, FILE* txtFile, const char* label) const
    {
        fprintf(txtFile, "---------- %s ----------\r\n\r\n", label);

        // write how many keys there are
        size_t dataListCount = 0;
        for (const auto& pair : m_dataLists)
        {
            if (pair.second.saveKey)
                dataListCount++;
        }
        Write(datFile, uint32_t(dataListCount));

        fprintf(txtFile, "  %zu keys\r\n", dataListCount);

        // for each key...
        for (const auto& pair : m_dataLists)
        {
            if (!pair.second.saveKey)
                continue;

            // write the key
            WriteString(datFile, pair.first.c_str());

            // write how many data lists there are
            Write(datFile, uint32_t(pair.second.m_dataLists.size()));

            // for each data list...
            size_t totalMemory = 0;
            for (const auto& dataList : pair.second.m_dataLists)
            {
                totalMemory += dataList.size() * sizeof(dataList[0]);

                // write how many items there is in this data list
                Write(datFile, uint32_t(dataList.size()));

                // write the data items
                for (const auto& data : dataList)
                    Write(datFile, data);
            }

            // write the txtFile data
            fprintf(txtFile, "    %s  - %zu entries, %zu bytes\r\n", pair.first.c_str(), pair.second.m_dataLists.size(), totalMemory);
        }
        fprintf(txtFile, "\r\n");
    }

    void SaveKey(const char* key, bool progressive)
    {
        if (progressive)
        {
            m_dataLists[key].saveKey = true;
            return;
        }

        std::string prefix = key;
        prefix.append("_");

        for (auto& pair : m_dataLists)
        {
            if (pair.first.compare(0, prefix.length(), prefix) == 0)
                pair.second.saveKey = true;
        }
    }

    void PostTest()
    {
        for (auto& pair : m_dataLists)
            pair.second.m_uniqueIndex = 1;
    }
};

struct DataCacheRNGSeed
{
    uint32_t seed[8];
    std::mt19937 rng;
    bool seeded = false;
    bool usedThisRun = false;
};

class DataCacheRNGSeeds
{
public:
    std::mt19937& GetRNG(const char* key);

    bool Load(FILE* file);
    void Save(FILE* datFile, FILE* txtFile, const char* label) const;

    void PostTest();

private:
    // a map, not an unordered_map because order matters. If the order changes, then cache.dat is different and means a huge file upload.
    std::map<std::string, DataCacheRNGSeed> m_seedLists;
};

class DataCache
{
private:
    DataCache() {}

public:
    static void Load();
    static void Save();

    static DataCache& Instance() {
        static DataCache cache;
        return cache;
    }

    void PostTest()
    {
        m_samples__1d.PostTest();
        m_samples__2d.PostTest();
        m_rngSeeds.PostTest();
    }

    DataCacheFamily<float> m_samples__1d;
    DataCacheFamily<Vec2> m_samples__2d;
    DataCacheRNGSeeds m_rngSeeds;
};