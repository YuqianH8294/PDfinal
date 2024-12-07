#include <iostream>
#include <string>
#include <chrono>
#include <locale>
#include <codecvt>
#include "TypeWriter.h"


// 檢查是否是UTF-8字節的開始
bool Typewriter::isUTF8Start(unsigned char c) {
    return (c & 0xC0) != 0x80;
}

    // 打印文字
void Typewriter::type(const std::string& text) {
    const char* str = text.c_str();
    size_t len = text.length();
    
    for (size_t i = 0; i < len;) {
        if (isUTF8Start(str[i])) {
            // 計算UTF-8字符的字節數
            int charBytes = 1;
            unsigned char firstByte = str[i];
            if ((firstByte & 0xE0) == 0xC0) charBytes = 2;
            else if ((firstByte & 0xF0) == 0xE0) charBytes = 3;
            else if ((firstByte & 0xF8) == 0xF0) charBytes = 4;

            // 輸出完整的UTF-8字符
            for (int j = 0; j < charBytes && i < len; j++) {
                std::cout << str[i++];
            }
            std::cout << std::flush;

            // 延遲
            auto start = std::chrono::high_resolution_clock::now();
            while (true) {
                auto current = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                    (current - start).count();
                if (duration >= delay_ms) break;
            }
        } else {
            i++;  // 跳過非UTF-8起始字節
        }
    }
    // std::cout << std::endl;
}

// 打印多行文字
void Typewriter::typeLines(const std::string text[], int size) {
    for (int i = 0; i < size; i++) {
        type(text[i]);
    }
}

// 設置打字速度
void Typewriter::setSpeed(int new_delay) {
    delay_ms = new_delay;
}
