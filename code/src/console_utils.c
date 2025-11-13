#include "../include/console_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    //#define _WIN32_WINNT 0x0600 // Windows Vista+ pour les API modernes
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif

void initConsole(void) {
#ifdef _WIN32
    // --- 1️⃣ Configurer l'encodage UTF-8 ---
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // --- 2️⃣ Activer le mode "Virtual Terminal" (couleurs, emoji, etc.) ---
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }

    // --- 3️⃣ (Optionnel) Changer le titre de la fenêtre ---
    SetConsoleTitleA("🌊 OceanDepths - Combat sous-marin 🐙");

    // --- 4️⃣ (Optionnel) Redimensionner la fenêtre ---
    SMALL_RECT windowSize = {0, 0, 90, 30};
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    //printf("\033[92m[INFO]\033[0m Console configurée pour UTF-8 ✅ (Windows)\n");

#else
    // --- LINUX / MAC ---
    // Rien à faire, mais on peut forcer la locale UTF-8
    setenv("LANG", "en_US.UTF-8", 1);
    const char* lang = getenv("LANG");
    printf("\033[92m[INFO]\033[0m Console UTF-8 détectée ✅ (%s)\n", lang);
#endif
    /*
    // --- 5️⃣ Test visuel ---
    printf("\n\033[36mTest visuel :\033[0m\n");
    printf("Couleurs : \033[31mROUGE\033[0m  \033[32mVERT\033[0m  \033[33mJAUNE\033[0m  \033[36mCYAN\033[0m\n");
    printf("Emoji    : 🤿 🐙 ⚔️ 💎 💧 🌊 ❤️ ☠️ 💫 😴\n");
    printf("Symboles : █ ░ ■ ● ▓ ▀ ▄\n\n");
    */
}
