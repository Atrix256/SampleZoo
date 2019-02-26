/*
FILE: fnv1a.h
AUTHOR: Alan Wolfe (alan.wolfe@gmail.com)
DATE: 2/26/2019
*/

#pragma once

// default values recommended by http://isthe.com/chongo/tech/comp/fnv/
static const uint32_t Prime = 0x01000193; //   16777619
static const uint32_t Seed = 0x811C9DC5; // 2166136261
/// hash a single byte
static inline uint32_t fnv1a(unsigned char oneByte, uint32_t hash = Seed)
{
    return (oneByte ^ hash) * Prime;
}

/// hash a block of memory
static inline uint32_t fnv1a(const void* data, size_t numBytes, uint32_t hash = Seed)
{
    const unsigned char* ptr = (const unsigned char*)data;
    while (numBytes--)
        hash = fnv1a(*ptr++, hash);
    return hash;
}