// thanks to shmoo and joeyjurjens for the usefull stuff under this comment.
#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

// #if defined(__aarch64__) //Compile for arm64 lib only
// #include <And64InlineHook/And64InlineHook.hpp>

// #else //Compile for armv7 lib only. Do not worry about greyed out highlighting code, it still works
// #include <Substrate/SubstrateHook.h>
// #include <Substrate/CydiaSubstrate.h>

// #endif
#include <Dobby/dobby.h>

void hook(void *offset, void *ptr, void **orig)
{
    // #if defined(__aarch64__)
    //     A64HookFunction(offset, ptr, orig);
    // #else
    //     MSHookFunction(offset, ptr, orig);
    // #endif
    DobbyHook(offset, ptr, orig);
}

#define HOOK(offset, ptr, orig) hook((void *)Utils::getAbsoluteAddress(g_szTargetLibrary, Utils::string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
#define HOOK_LIB(lib, offset, ptr, orig) hook((void *)Utils::getAbsoluteAddress(OBFUSCATE(lib), Utils::string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)

#define HOOK_NO_ORIG(offset, ptr) hook((void *)Utils::getAbsoluteAddress(g_szTargetLibrary, Utils::string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)
#define HOOK_LIB_NO_ORIG(lib, offset, ptr) hook((void *)Utils::getAbsoluteAddress(OBFUSCATE(lib), Utils::string2Offset(OBFUSCATE(offset))), (void *)ptr, NULL)

#define HOOKSYM(sym, ptr, org) hook(DobbySymbolResolver(g_szTargetLibrary, sym), (void *)ptr, (void **)&org)
#define HOOKSYM_LIB(lib, sym, ptr, org) hook(DobbySymbolResolver(lib,sym), OBFUSCATE(sym)), (void *)ptr, (void **)&org)

#define HOOKSYM_NO_ORIG(sym, ptr) hook(DobbySymbolResolver(g_szTargetLibrary, sym)(void *) ptr, NULL)
#define HOOKSYM_LIB_NO_ORIG(lib, sym, ptr) hook(DobbySymbolResolver(lib, sym), (void *)ptr, NULL)

#define FUNC_SET_TO(_ret, _name, _offset, ...) \
    _name = (_ret(*)(__VA_ARGS__))(Utils::getAbsoluteAddress(g_szTargetLibrary, _offset));

#define FUNC_SET_TO_LIB(_ret, _name, lib,_offset, ...) \
    _name = (_ret(*)(__VA_ARGS__))(Utils::getAbsoluteAddress(lib, _offset));

#define DECL_HOOK(_ret, _name, ...)    \
    _ret (*orig_##_name)(__VA_ARGS__); \
    _ret hook_##_name(__VA_ARGS__)

#define DECL_HOOKv(_name, ...)         \
    void (*orig_##_name)(__VA_ARGS__); \
    void hook_##_name(__VA_ARGS__)

/**
 * Now for memory patch you need to use GlossHook
 * but, you can still use this if need to use KittyMemory!
 */
// std::vector<MemoryPatch> memoryPatches;
// std::vector<uint64_t> offsetVector;

// // Patching a offset without switch.
// void patchOffset(const char *fileName, uint64_t offset, std::string hexBytes, bool isOn)
// {

//     MemoryPatch patch = MemoryPatch::createWithHex(fileName, offset, hexBytes);

//     // Check if offset exists in the offsetVector
//     if (std::find(offsetVector.begin(), offsetVector.end(), offset) != offsetVector.end())
//     {
//         // LOGE("Already exists");
//         std::vector<uint64_t>::iterator itr = std::find(offsetVector.begin(), offsetVector.end(), offset);
//         patch = memoryPatches[std::distance(offsetVector.begin(), itr)]; // Get index of memoryPatches vector
//     }
//     else
//     {
//         memoryPatches.push_back(patch);
//         offsetVector.push_back(offset);
//         // LOGI("Added");
//     }

//     if (!patch.isValid())
//     {
//         LOGE("Failing offset: 0x%llu, please re-check the hex", offset);
//         return;
//     }
//     if (isOn)
//     {
//         if (!patch.Modify())
//         {
//             LOGE("Something went wrong while patching this offset: 0x%llu", offset);
//         }
//     }
//     else
//     {
//         if (!patch.Restore())
//         {
//             LOGE("Something went wrong while restoring this offset: 0x%llu", offset);
//         }
//     }
// }

// void patchOffsetSym(uintptr_t absolute_address, std::string hexBytes, bool isOn)
// {

//     MemoryPatch patch = MemoryPatch::createWithHex(absolute_address, hexBytes);

//     // Check if offset exists in the offsetVector
//     if (std::find(offsetVector.begin(), offsetVector.end(), absolute_address) != offsetVector.end())
//     {
//         // LOGE("Already exists");
//         std::vector<uint64_t>::iterator itr = std::find(offsetVector.begin(), offsetVector.end(), absolute_address);
//         patch = memoryPatches[std::distance(offsetVector.begin(), itr)]; // Get index of memoryPatches vector
//     }
//     else
//     {
//         memoryPatches.push_back(patch);
//         offsetVector.push_back(absolute_address);
//         // LOGI("Added");
//     }

//     if (!patch.isValid())
//     {
//         LOGE("Failing offset: 0x%llu, please re-check the hex", absolute_address);
//         return;
//     }
//     if (isOn)
//     {
//         if (!patch.Modify())
//         {
//             LOGE("Something went wrong while patching this offset: 0x%llu", absolute_address);
//         }
//     }
//     else
//     {
//         if (!patch.Restore())
//         {
//             LOGE("Something went wrong while restoring this offset: 0x%llu", absolute_address);
//         }
//     }
// }

// #define PATCH(offset, hex) patchOffset(g_szTargetLibrary, Utils::string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), true)
// #define PATCH_LIB(lib, offset, hex) patchOffset(OBFUSCATE(lib), Utils::string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), true)

// #define PATCH_SYM(sym, hex) patchOffset(dlsym(dlopen(g_szTargetLibrary, 4), OBFUSCATE(sym)), OBFUSCATE(hex), true)
// #define PATCH_LIB_SYM(lib, sym, hex) patchOffset(dlsym(dlopen(lib, 4), OBFUSCATE(sym)), OBFUSCATE(hex), true)

// #define PATCH_SWITCH(offset, hex, boolean) patchOffset(g_szTargetLibrary, Utils::string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), boolean)
// #define PATCH_LIB_SWITCH(lib, offset, hex, boolean) patchOffset(OBFUSCATE(lib), Utils::string2Offset(OBFUSCATE(offset)), OBFUSCATE(hex), boolean)

// #define PATCH_SYM_SWITCH(sym, hex, boolean) patchOffsetSym((uintptr_t)dlsym(dlopen(g_szTargetLibrary, 4), OBFUSCATE(sym)), OBFUSCATE(hex), boolean)
// #define PATCH_LIB_SYM_SWITCH(lib, sym, hex, boolean) patchOffsetSym((uintptr_t)dlsym(dlopen(lib, 4), OBFUSCATE(sym)), OBFUSCATE(hex), boolean)

// #define RESTORE(offset) patchOffset(g_szTargetLibrary, Utils::string2Offset(OBFUSCATE(offset)), "", false)
// #define RESTORE_LIB(lib, offset) patchOffset(OBFUSCATE(lib), Utils::string2Offset(OBFUSCATE(offset)), "", false)

// #define RESTORE_SYM(sym) patchOffsetSym((uintptr_t)dlsym(dlopen(g_szTargetLibrary, 4), OBFUSCATE(sym)), "", false)
// #define RESTORE_LIB_SYM(lib, sym) patchOffsetSym((uintptr_t)dlsym(dlopen(lib, 4), OBFUSCATE(sym)), "", false)
#endif // ANDROID_MOD_MENU_MACROS_H