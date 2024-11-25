#include <main.h>

#include <Dobby/dobby.h>
#include <GlossHook/Gloss.h>
#include <Logger.h>
#include <Utils.h>
#include <Macros.h>

void *main_thread(void *)
{
    try {
        do {
            LOGI("Patcher now is loaded!");
            sleep(1);
            if (Utils::isUnityGame())
                LOGI("Target library detected as Unity Library");
        } while (!Utils::isLibraryLoaded(g_szTargetLibrary));
        LOGI("Patcher is now on patch state, trying loaded every patch block...");
        // Your patch code here...
    }
    catch(const std::exception& e)
    {
        LOGE("Whoopsie error detected at Patch code, Error: %s", e.what());
    }
    pthread_exit(nullptr);
    return nullptr;
}

void *looper_thread(void *) {
    while(Utils::isLibraryLoaded(g_szTargetLibrary)) {
        // Your loop code here...
    }
    pthread_exit(nullptr);
    return nullptr;
}

__attribute__((constructor)) void lib_main()
{
    pthread_t mains;
    pthread_create(&mains, nullptr, main_thread, nullptr);

    pthread_t loopers;
    pthread_create(&loopers, nullptr, looper_thread, nullptr);
}