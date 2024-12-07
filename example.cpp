#include <string>
#include <vector>
#include <map>
#include <random>
#include <functional>
#include <fstream>
#include <iostream>
#include "TypeWriter.h"
#ifdef _WIN32
    #include <windows.h> // Windows 平台專屬
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h> // Mac 專屬
    #define SLEEP(ms) usleep(ms * 1000)
#endif
// #include "TypewriterEffect.h" //這是打字效果處理器 用TypewriterEffect printer; 建立一個物件再用 printer.printText()印東西
using namespace std;

void showTXT(const string& filename){
        Typewriter tp;
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            tp.setSpeed(10);
            while (getline(file, line)) {
                tp.type(line);
                tp.type("\n");
            }
            file.close();
        }
    }
// 狀態效果
struct Status {
    string name;
    int duration;
    function<void(class Player&)> effect;
};

// 主角類別
class Player {
private:
    string playerName;
    int academic;      // 學科能力
    int popularity;    // 人緣
    int charm;        // 魅力
    int stamina;       // 體能
    int fatigue;      // 疲勞值
    int lucky;      // 幸運值
    int move;       // 行動點數上限
    vector<Status> statuses;  // 狀態效果
    map<string, bool> flags;  // 劇情標記

public:
    
    Player() : academic(0), popularity(0), charm(50), stamina(0),fatigue(0), lucky(5), move(30){}
    Player(const string& playerName, const int& type){
        this->playerName = playerName;
        if(type == 1){
            cout << "你大概是一個 NERD\n";
        }
        else if (type == 2){
            cout << "你是一個 Social Queen\n";
        }
        else if (type == 3){
            cout << "你是一個 陽光少女\n";
        }
        else if (type == 4){
            cout << "你是一個 Genius\n";
        }
        else if (type == 5){
            cout << "你是一個 Indian chill guy\n";
        }
    }

    void setPlayer(int& type){
        if(type == 1){
            
        }
        else if (type == 2)
        {
            /* code */
        }
        else if (type == 3)
        {
            /* code */
        }
        else if (type == 4)
        {
            /* code */
        }
        else if (type == 5)
        {
            /* code */
        }
    }


    // Getters and setters
    void modifyStats(int aca, int pop, int chr, int fat, int sta) {
        academic += aca;
        popularity += pop;
        charm += chr;
        fatigue += fat;
        stamina += sta;
    }
    int getAcademic() const{return academic;};
    int getPopularity()const{return popularity;};    // 人緣
    int getCharm()const{return charm;};        // 魅力
    int getFatigue()const{return fatigue;};      // 疲勞值
    string getName() const{return playerName;};
    int getMove()const{return move;};
};

// NPC角色類別
class Character {
private:
    string name;
    int affection;     // 好感度
    vector<pair<int, string>> dialogues;  // 好感度門檻與對應對話
    map<int, function<void(Player&)>> specialEvents;  // 特殊事件

public:
    Character(string n) : name(n), affection(0) {}
    
    void addDialogue(int threshold, string text) {
        dialogues.push_back({threshold, text});
    }
    
    void addSpecialEvent(int threshold, function<void(Player&)> event) {
        specialEvents[threshold] = event;
    }
    
    string getCurrentDialogue() const {
        string current;
        for(const auto& d : dialogues) {
            if(affection >= d.first) {
                current = d.second;
            }
        }
        return current;
    }
    int getAffection(){return affection;};
    void setAffection(int affection){this->affection = affection;};
};

// 地點類別
class Location {
    string name;
    vector<string> availableCharacters;
    vector<pair<string, function<void(Player&)>>> actions;
};

// 事件系統
class EventSystem {
private:
    vector<pair<function<bool(const Player&)>, function<void(Player&)>>> randomEvents;
    
public:
    void addRandomEvent(function<bool(const Player&)> condition,
                        function<void(Player&)> event) {
        randomEvents.push_back({condition, event});
    }
    
    void tryTriggerEvent(Player& player) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
        
        for(const auto& event : randomEvents) {
            if(dis(gen) < 0.1 && event.first(player)) {  // 10% 觸發機率
                event.second(player);
                break;
            }
        }
    }
};

// 遊戲主體
class DatingGame {
private:
    Player player;
    vector<Character> characters;
    int currentDay;
    string currentLocation;
    EventSystem eventSystem;
    map<string, int> endings;  // 結局條件

public:
    Typewriter tp;
    DatingGame() : currentDay(1) {
        // 初始化角色
        characters.push_back(Character("角色1"));
        characters.push_back(Character("角色2"));
        characters.push_back(Character("角色3"));

        // 設定隨機事件
        setupRandomEvents();
    }
    void setGame(){ // 遊戲前導
        string playerName;
        int type;
        cout << ">>遊戲簡介：一名學測剩30週的高中美少女，要在短短的30週內出奇蹟";
        pause();
        cout <<">>期間會遇到許多出其不意的事情，合理的運用時間才能獲得理想的目標！考上台大吧！\\(^w^)/ " << "\n";
        showTXT("C:/Users/Jolie/Jolie's doc/C++/final/rule.txt");

        while (true) {
            cout << "請輸入你的名字: ";
            getline(cin, playerName);
            
            // 移除字串前後的空白
            playerName.erase(0, playerName.find_first_not_of(" \t\n\r\f\v"));
            playerName.erase(playerName.find_last_not_of(" \t\n\r\f\v") + 1);
            
            if (playerName.empty()) {
                cout << "名字不能為空！請重新輸入。\n";
            } else {
                cout << ">>你叫" << playerName << "嗎?  酷喔，聽起來就是電神的名字 \n";
                pause();
                break;
            }
        }

        cout << "你可以選擇成為這幾種類型的女主人翁：\n=====類型一：斯文書生=====\n       初始能力：\n學科值：100\n體能：20\n"
            <<"人緣：50\n魅力:10\n幸運:5";
        cout <<"\n=====類型二：社交花花=====\n       初始能力：\n學科值：20\n體能：50\n"
            <<"人緣：100\n魅力:20\n幸運:5";
        cout <<"\n=====類型三：排球少女=====\n       初始能力：\n學科值：50\n體能：100\n"
            <<"人緣：20\n魅力:15\n幸運:5\n";
        cout <<"(輸入想要類型的數字)：";

        while (true){
            cin >> type;
            if (type == 1 || type == 2 || type == 3 || type == 4 || type == 5) {
                cout << "你選擇了類型：" << type << "\n";
                break; // 輸入正確，跳出循環"
            } else {
                cout << "請重新輸入一次。不要玩我" << endl;
            }
        }
        cout << "學測";
        for (int i = 0; i < 6; ++i) {
            cout << "." << flush; // 輸出點並立即刷新緩衝區
           SLEEP (500); // 延遲 500 毫秒; // 延遲 0.5 秒
        } cout << "啟動";
        for (int i = 0; i < 3; ++i) {
            cout << "!" << flush; // 輸出點並立即刷新緩衝區
            SLEEP(250); // 延遲 500 毫秒; // 延遲 0.5 秒
        }
        Player player;
        player = Player(playerName, type);
    }
    
    void displayEndings() {
        // 設定各種角色結局條件
    }
    
    void setupRandomEvents() {
        // 添加隨機事件
        eventSystem.addRandomEvent(
            [](const Player& p) { return true; },  // 條件
            [](Player& p) {
                cout << "觸發隨機事件！\n";
                p.modifyStats(0, 0, 0, 0, 0);
            }
        );
    }
    void checkLoveEnding(int score){ // 確認有沒有在一起
        // 取最高好感度的進入結局 第二者當朋友
        // 若兩者滿100
        // 三者都滿100
        // 都未達標
    }
    void checkEnding() {
        // 檢查是否達到結局條件
        // 先考試
        int score;
        if(player.getAcademic() >= 600)
            score = collegeTest("easy");
        else if (player.getAcademic() < 600 && player.getAcademic() >= 450)
            score = collegeTest("moderate");
        else score = collegeTest("hard");
        tp.setSpeed(100);
        tp.type("學測中你一共獲得了");
        cout << score << "分\n";
        if(score == 75){
            tp.type("你考上了夢寐以求的台大，家人邀請你左鄰右舍一起來放鞭炮慶祝\n");
        }
        else if (score == 50){
            tp.type("你考上了一所中字輩大學，家人很為你高興，認為你的投入有換來回報\n");
        }
        else{
            tp.type("你最終去了小葉大學......在那邊當店神\n");
        }
        checkLoveEnding(score);
    }
    int collegeTest(string level){
        tp.type("今天是大考的日子......\n");
        pause();
        int score = 0;
        int answer[3] = {};
        int solution[3]={0}; // 未完成
        if(level == "easy"){
            tp.type("第一題： \n (自然題)");
            showTXT("final/easy_test1.txt");
            tp.type("請作答：");
            cin >> answer[0];
            tp.type("第二題： \n (國文題)");
            showTXT("final/easy_test2.txt");
            tp.type("請作答：");
            cin >> answer[1];
            tp.type("第三題： \n (英文題)");
            showTXT("final/easy_test3.txt");
            tp.type("請作答：");
            cin >> answer[2];

        }
        else if(level == "hard"){
            tp.type("第一題： \n (自然題)");
            showTXT("final/hard_test1.txt");
            tp.type("請作答：");
            cin >> answer[0];
            tp.type("第二題： \n (數學題)");
            showTXT("final/hard_test2.txt");
            tp.type("請作答：");
            cin >> answer[1];
            tp.type("第三題： \n (社會題)");
            showTXT("final/hard_test3.txt");
            tp.type("請作答：");
            cin >> answer[2];
        }
        else{
            tp.type("第一題： \n (國文題)");
            showTXT("final/test1.txt");
            tp.type("請作答：");
            cin >> answer[0];
            tp.type("第二題： \n (數學題)");
            showTXT("final/test2.txt");
            tp.type("請作答：");
            cin >> answer[1];
            tp.type("第三題： \n (自然題)");
            showTXT("final/test3.txt");
            tp.type("請作答：");
            cin >> answer[2];
        }
        for(int i; i < 3; i++){ // 對答案
            if(i == solution[i]){
                score += 25;
            }
        }
        return score;
    }
    void run() {
        while(true) {
            string command; // 玩家指令
            displayStatus(); // 展示能操作的選項
            int currentMove = player.getMove(); //現在剩餘行動點等於這個玩家最高行動點上限
            while(currentMove > 0){
                getline(cin, command);
                if(command == "1"){ // study
                    if(currentMove < 6){
                        tp.type("你的行動值不夠！");
                    }
                    else{
                        currentMove -= 6;
                        //觸發學習事件//
                    }
                }
                else if(command == "2"){ // exercise
                    if(currentMove < 6){
                        tp.type("你的行動值不夠！");
                    }
                    else{
                        currentMove -= 6;
                        //觸發運動事件//
                    }
                }
                else if(command == "3"){ // social
                    if(currentMove < 6){
                        tp.type("你的行動值不夠！");
                    }
                    else{
                        currentMove -= 6;
                        //觸發社交事件//
                    }
                }
                else if(command == "4"){ // eat
                    if(currentMove < 4){
                        tp.type("你的行動值不夠！");
                    }
                    else{
                        currentMove -= 4;
                        //觸發吃飯事件//
                    }
                }
                else if(command == "5"){ // sleep
                    //觸發睡覺事件//
                    currentMove = 0;
                }
                else if(command == "Q"){
                    goto exit_loop; // 切到雙層迴圈外 結束遊戲
                }
                else{
                    tp.type("看清楚選項！請輸入一個數字後直接按下Enter");
                }
                processCommand(command);
                command.clear();

                }
                currentDay ++;
                if(currentDay == 3){
                    checkEnding();
                    break;
            }
        }
        exit_loop:;
    }

    void displayStatus() {
        // TypewriterEffect printer;
        cout << "=== Day " << currentDay << " ===\n";
        
        // 顯示其他狀態
        tp.type("倒數");
        cout << 30 - currentDay;
        tp.type("週了...... 今天做點甚麼好呢？\n");
        
        if(player.getFatigue() > 50)
            tp.type("好累喔......不想念書了，這破書愛讀誰讀\n");
        else if (player.getFatigue() > 100){
            tp.type("破防了");
        }
        // 現在能力 可以選的選項 1. 
        tp.setSpeed(30);
        tp.type("           <目前狀態>          \n");
        tp.type("依據現在的能力值 你可以選擇：");
        tp.type("1.study(消耗6點行動值), 2.exercise(消耗6點行動值), 3.social(消耗6點行動值), 4.eat(消耗4點行動值，減少一點點疲勞), 5.sleep(清空所有行動值，減少疲勞值)\n");
        
    }

    void processCommand(const string& cmd) {
        // 處理玩家輸入
    }
    void pause() { // press Enter to continue
    string dummy;
    getline(cin, dummy);  // 不管輸入什麼，只要按 Enter 就會繼續
    }
};

int main() {
    // SetConsoleOutputCP(65001)
    DatingGame game;
    Character* characters[] = {new Character("陳愛芬"), new Character("黃梓祺"), new Character("王語崴")}; // 初始化角色列表
    characters[0]->setAffection(50); // 閨密福利
    characters[1]->setAffection(20); // 青梅竹馬
    characters[2]->setAffection(0); // 最難追的
    game.setGame();
    game.run();
    return 0;
}