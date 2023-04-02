#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Player
{
    string name;
    int m_health;
    int m_attack;
    int m_defense;
};

struct Enemy
{
    string name;
    int m_health;
    int m_attack;
    int m_defense;
};

void Attack()
{
    cout << "Player attacks the guard!" << endl;
}

void Defend()
{
    cout << "Player defended!" << endl;
}

class Command
{
public:
    virtual void execute() = 0;
};

class AttackCommand : public Command
{
public:
    void execute()
	{
        Attack();
    }
};

class DefendCommand : public Command
{
public:
    void execute()
	{
        Defend();
    }
};

void savePlayerInfo(Player player, const string& fileName)
{
    ofstream playerFile(fileName, ios::out | ios::binary);
    if (playerFile.is_open()) {
        playerFile.write(reinterpret_cast<char*>(&player), sizeof(player));
        playerFile.close();
        cout << "Player information saved to file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}

Player loadPlayerInfo(const string& fileName)
{
    Player player;
    ifstream playerFile(fileName, ios::out | ios::binary);
    if (playerFile.is_open()) {
        playerFile.read(reinterpret_cast<char*>(&player), sizeof(player));
        playerFile.close();
        cout << "Player information loaded from file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
    return player;
}

void saveEnemyInfo(Enemy enemy, const string& fileName)
{
    ofstream enemyFile(fileName, ios::out | ios::binary);
    if (enemyFile.is_open()) {
        enemyFile.write(reinterpret_cast<char*>(&enemy), sizeof(enemy));
        enemyFile.close();
        cout << "Enemy information saved to file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}

Enemy loadEnemyInfo(const string& fileName)
{
    Enemy enemy;
    ifstream enemyFile(fileName, ios::out | ios::binary);
    if (enemyFile.is_open()) {
        enemyFile.read(reinterpret_cast<char*>(&enemy), sizeof(enemy));
        enemyFile.close();
        cout << "Enemy information loaded from file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
    return enemy;
}


void loadDialog(string fileName)
{
    ifstream dialogFile(fileName);
    if (dialogFile.is_open()) 
    {
        string line;
        while (getline(dialogFile, line)) 
        {
            cout << line << endl;
        }
        dialogFile.close();
    }
    else 
    {
        cout << "Error opening file!" << endl;
    }
}

int main()
{
    map<string, Command*> commands;
    commands["Swing Sword"] = new AttackCommand();
    commands["Raise Shield"] = new DefendCommand();

    Player player = { "Player", 10, 10, 10 };
    savePlayerInfo(player, "player.bin");
    Player loadedPlayer = loadPlayerInfo("player.bin");
    cout << "Player name: " << loadedPlayer.name << endl;
    cout << "Player health: " << loadedPlayer.m_health << endl;
    cout << "Player attack: " << loadedPlayer.m_attack << endl;
    cout << "Player defense: " << loadedPlayer.m_defense << endl;

    Enemy enemy = { "Enemy", 5, 5, 3 };
    saveEnemyInfo(enemy, "enemy.bin");
	Enemy loadedEnemy = loadEnemyInfo("enemy.bin");
    cout << "Enemy name: " << loadedEnemy.name << endl;
    cout << "Enemy health: " << loadedEnemy.m_health << endl;
    cout << "Enemy attack: " << loadedEnemy.m_attack << endl;
    cout << "Enemy defense: " << loadedEnemy.m_defense << endl;


    string input;
    cout << "Enter a command (Swing Sword or Raise Shield): ";
    getline(cin, input);

    if (commands.count(input) > 0) 
    {
        commands[input]->execute();
        loadDialog("dialog.txt");
    }
    else 
    {
        cout << "Invalid command!" << endl;
    }

    return 0;
}