/*
FILE: datacache.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/24/2019

Description:
Holds re-usable data on disk, such as expensive to create sampling patterns, to help runtime speed, and stability of results for randomized sequences.
*/

#pragma once

#include <unordered_map>
#include <vector>

template <typename T>
struct DataList
{
    size_t m_uniqueIndex = 1;

    typedef std::vector<T> TData;
    std::vector<TData> m_dataLists;
};

template <typename T>
struct DataCacheFamily
{
    std::unordered_map<std::string, DataList<T>> m_dataLists;

    template <typename SAMPLE_FN>
    void GetSamples_Progressive(const char* key, const SAMPLE_FN& SampleFn, std::vector<T>& values, size_t numValues, bool wantUnique, bool useCache)
    {
        if (!useCache)
        {
            SampleFn(values, numValues);
            return;
        }

        DataList<T>& dataList = m_dataLists[key];

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
            SampleFn(samples, numValues);

        values.resize(numValues);
        memcpy(values.data(), samples.data(), sizeof(T) * numValues);
    }

    template <typename SAMPLE_FN>
    void GetSamples_NonProgressive(const char* key, const SAMPLE_FN& SampleFn, std::vector<T>& values, size_t numValues, bool wantUnique, bool useCache)
    {
        if (!useCache)
        {
            SampleFn(values, numValues);
            return;
        }

        char keyBuffer[256];
        sprintf(keyBuffer, "%s_%zu", key, numValues);

        DataList<T>& dataList = m_dataLists[keyBuffer];

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
            SampleFn(samples, numValues);

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

                std::vector<float>& dataList = dataLists.m_dataLists[dataListIndex];
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

    void Save(FILE* file) const
    {
        // write how many keys there are
        Write(file, uint32_t(m_dataLists.size()));

        // for each key...
        for (const auto& pair : m_dataLists)
        {
            // write the key
            WriteString(file, pair.first.c_str());

            // write how many data lists there are
            Write(file, uint32_t(pair.second.m_dataLists.size()));

            // for each data list...
            for (const auto& dataList : pair.second.m_dataLists)
            {
                // write how many items there is in this data list
                Write(file, uint32_t(dataList.size()));

                // write the data items
                for (const auto& data : dataList)
                    Write(file, data);
            }
        }
    }
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

    DataCacheFamily<float> m_samples__1d;
};