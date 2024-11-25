#ifndef UTILS
#define UTILS

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <dlfcn.h>
#include <unistd.h>
#include <dirent.h>
#include <Logger.h>

bool isUnity = false;
bool libLoaded = false;
uintptr_t libBase;

namespace Utils
{
    uintptr_t getAbsoluteAddress(const char *libraryName, uintptr_t relativeAddr)
    {
        libBase = GlossGetLibBias(libraryName);
        if (libBase == 0)
            return 0;
        return (reinterpret_cast<uintptr_t>(libBase + relativeAddr));
    }

    bool isLibraryLoaded(const char *libraryName)
    {
        // libLoaded = true;
        libBase = GlossGetLibBias(libraryName);
        if(libBase == 0) {
            return false; 
        }
        return true;
    }

    uintptr_t getRealOffset(const char *libraryName, uintptr_t address)
    {
        if (libBase == 0)
        {
            uintptr_t libBase = GlossGetLibBias(libraryName);
        }
        return (libBase + address);
    }

    uintptr_t getLibOffset(const char *libraryName, uintptr_t address)
    {
        if (libBase == 0)
        {
            libBase = GlossGetLibBias(libraryName);
        }
        return (libBase - address);
    }

    bool isUnityGame()
    {
        return isLibraryLoaded("libil2cpp.so");
    }

    uintptr_t string2Offset(const char *c)
    {
        int base = 16;
        // See if this function catches all possibilities.
        // If it doesn't, the function would have to be amended
        // whenever you add a combination of architecture and
        // compiler that is not yet addressed.
        static_assert(sizeof(uintptr_t) == sizeof(unsigned long) || sizeof(uintptr_t) == sizeof(unsigned long long),
                      "Please add string to handle conversion for this architecture.");

        // Now choose the correct function ...
        if (sizeof(uintptr_t) == sizeof(unsigned long))
        {
            return strtoul(c, nullptr, base);
        }
        // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
        return strtoull(c, nullptr, base);
    }

    char *readFileContent(const char *filename)
    {
        FILE *file = fopen(filename, "r");
        if (file == nullptr)
        {
            perror("Error opening file");
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        char *buffer = (char *)malloc(file_size + 1);
        if (buffer == nullptr)
        {
            perror("Error allocating memory");
            fclose(file);
            return nullptr;
        }

        size_t result = fread(buffer, 1, file_size, file);
        if (result != file_size)
        {
            perror("Error reading file");
            free(buffer);
            fclose(file);
            return nullptr;
        }

        buffer[file_size] = '\0';

        fclose(file);
        return buffer;
    }
}

#endif
