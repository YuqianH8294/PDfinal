#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <functional>
#include <windows.h> // Windows 平台專屬
#include <fstream>
using namespace std;

void showTXT(const string& filename){
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                cout << line << endl;
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
    int move;       // 行動點數
    vector<Status> statuses;  // 狀態效果
    map<string, bool> flags;  // 劇情標記

public:
    
    Player() : academic(0), popularity(0), charm(50), stamina(0),fatigue(0){}
    Player(const string& playerName, const int& type){
        this->playerName = playerName;
        if(type == 1){
            cout << "你是一個 NERD";
        }
    }

    void setPlayer(string playerName, int type){
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
        
        
    }

    void updateStatus() {
        for(auto it = statuses.begin(); it != statuses.end();) {
            it->effect(*this);
            if(--(it->duration) <= 0) {
                it = statuses.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Getters and setters
    void modifyStats(int aca, int pop, int chr, int fat) {
        academic += aca;
        popularity += pop;
        charm += chr;
        fatigue += fat;
    }
    int getAcademic(){return academic;};
    int getPopularity(){return popularity;};    // 人緣
    int getCharm(){return charm;};        // 魅力
    int getFatigue(){return fatigue;};      // 疲勞值
    string getName(){return playerName;};
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
    DatingGame() : currentDay(1) {
        // 初始化角色
        characters.push_back(Character("角色1"));
        characters.push_back(Character("角色2"));
        characters.push_back(Character("角色3"));
        
        // 設定結局條件
        setupEndings();
        
        // 設定隨機事件
        setupRandomEvents();
    }
    void setGame(){ // 遊戲前導
        string playerName;
        int type;
        cout << ">>遊戲簡介：一名學測剩30週的高中美少女，要在短短的30週內出奇蹟";
        pause();
        cout <<">>期間會遇到許多出其不意的事情，合理的運用時間才能獲得理想的目標！考上台大吧！\\(^w^)/ " << "\n";
        showTXT("final\\rule.txt");

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
            Sleep(500); // 延遲 500 毫秒; // 延遲 0.5 秒
        } cout << "啟動";
        for (int i = 0; i < 3; ++i) {
            cout << "!" << flush; // 輸出點並立即刷新緩衝區
            Sleep(250); // 延遲 500 毫秒; // 延遲 0.5 秒
        }
        Player player;
        player = Player(playerName, type);
    }
    void advanceDay() {
        currentDay++;
        player.updateStatus();
        eventSystem.tryTriggerEvent(player);
        checkEnding();
    }
    
    void setupEndings() {
        // 設定各種結局條件
    }
    
    void setupRandomEvents() {
        // 添加隨機事件
        eventSystem.addRandomEvent(
            [](const Player& p) { return true; },  // 條件
            [](Player& p) {
                cout << "觸發隨機事件！\n";
                p.modifyStats(5, 0, 0, 10);
            }
        );
    }
    
    void checkEnding() {
        // 檢查是否達到結局條件
        int score;
        if(player.getAcademic() >= 600)
            score = collegeTest("easy");
        else if (player.getAcademic() < 600 && player.getAcademic() >= 450)
            score = collegeTest("moderate");
        else score = collegeTest("hard");
        
    }
    int collegeTest(string level){
        cout << "今天是大考的日子......"<< "\n";
        pause();
        if(level == "easy"){
            cout << "第一題： \n (生物題)";
            return 0;
        }
        return 0;
    }
    void run() {
        string command;
        while(true) {
            displayStatus();
            getline(cin, command);
            // 去掉所有空格
            int index = 0;
            for(char c: command){
                if(c != ' '){
                    command[index++] = c;
                }
            }
            if(command == "Q") break;
            processCommand(command);
            command.clear();
            if(currentDay == 30){
                checkEnding();
                break;
            }
        }
    }

    void displayStatus() {
        cout << "=== Day " << currentDay << " ===\n";
        
        // 顯示其他狀態
        cout << "倒數" << 30 - currentDay << "週了...... 今天做點甚麼好呢？\n";
        if(player.getFatigue() > 50)
            cout << "好累喔......不想念書了，這破書愛讀誰讀\n";
        else if (player.getFatigue() > 100){
            cout << "破防了";
        }
        
        pause();
        
        currentDay ++;
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
    system("chcp 65001");
    DatingGame game;
    game.setGame();
    game.run();
    return 0;
}