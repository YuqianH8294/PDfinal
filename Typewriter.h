#include <iostream>
#include <string>
#include <chrono>
#include <locale>
#include <codecvt>
class Typewriter {
private:
    int delay_ms;  // 每個字元之間的延遲時間(毫秒)

    // 檢查是否是UTF-8字節的開始
    bool isUTF8Start(unsigned char c);

public:
    Typewriter(int delay = 100) : delay_ms(delay) { }

    // 打印文字
    void type(const std::string& text);

    // 打印多行文字
    void typeLines(const std::string text[], int size);

    // 設置打字速度
    void setSpeed(int new_delay);
};