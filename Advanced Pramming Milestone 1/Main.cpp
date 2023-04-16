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

    void SetName(string name) { this->name = name;  }
    void SetHealth(int health) { m_health = health; }
    void SetAttack(int attack) { m_attack = attack; }
    void SetDefense(int defense) { m_defense = defense; }
};

struct Enemy
{
    string name;
    int m_health;
    int m_attack;
    int m_defense;

    void SetName(string name) { this->name = name; }
    void SetHealth(int health) { m_health = health; }
    void SetAttack(int attack) { m_attack = attack; }
    void SetDefense(int defense) { m_defense = defense; }
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
    virtual bool GetProceed() = 0;
};

class AttackCommand : public Command
{
public:
    void execute()
	{
        Attack();
    }
    bool GetProceed() { return proceed; }
    bool proceed;
};

class DefendCommand : public Command
{
public:
    void execute()
	{
        Defend();
    }
    bool GetProceed() { return proceed; }
    bool proceed;
};

void savePlayerInfo(Player player, const string& fileName)
{
    fstream file;
	file.open(fileName);

    if (!file) {
        ofstream playerFile(fileName);
        playerFile << player.name << endl;
        playerFile << player.m_health << endl;
        playerFile << player.m_attack << endl;
        playerFile << player.m_defense << endl;
        playerFile.close();
        cout << "Player information saved to file." << endl;
    }
    else if (file)
    {
        file.clear();
        file << player.name << endl;
        file << player.m_health << endl;
        file << player.m_attack << endl;
        file << player.m_defense << endl;
        file.close();
        cout << "Player information saved to file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}

Player loadPlayerInfo(Player player, const string& fileName)
{
    fstream playerFile(fileName);
    if (playerFile) {
        string name;
        int hp, atk, def;
        playerFile >> name >> hp >> atk >> def;
        player.SetName(name);
        player.SetHealth(hp);
        player.SetAttack(atk);
        player.SetDefense(def);
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
    fstream file;
    file.open(fileName);

    if (!file) {
        ofstream enemyFile(fileName);
        enemyFile << enemy.name << endl;
        enemyFile << enemy.m_health << endl;
        enemyFile << enemy.m_attack << endl;
        enemyFile << enemy.m_defense << endl;
        enemyFile.close();
        cout << "Player information saved to file." << endl;
    }
    else if (file)
    {
        file.clear();
        file << enemy.name << endl;
        file << enemy.m_health << endl;
        file << enemy.m_attack << endl;
        file << enemy.m_defense << endl;
        file.close();
        cout << "Enemy information saved to file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
}

Enemy loadEnemyInfo(Enemy enemy, const string& fileName)
{
    fstream enemyFile(fileName);
    if (enemyFile) {
        string name;
        int hp, atk, def;
        enemyFile >> name >> hp >> atk >> def;
        enemy.SetName(name);
        enemy.SetHealth(hp);
        enemy.SetAttack(atk);
        enemy.SetDefense(def);
        enemyFile.close();
        cout << "Enemy information loaded from file." << endl;
    }
    else {
        cout << "Error opening file." << endl;
    }
    return enemy;
}


void loadDialog(int num, string fileName)
{
    ifstream dialogFile(fileName);
	string line;
    int currLine = 0;

    if(!dialogFile.fail())
    {
	    while(!dialogFile.eof())
	    {
	    	currLine++;
	    	getline(dialogFile, line);
	    	if (currLine == num) break;
	    }
        cout << line << endl;
    	dialogFile.close();
    }
    else 
    {
        cout << "Error opening file!" << endl;
    }
}

class ActionCommand : public Command
{
public:
    ActionCommand(int num, bool proc = false) { number = num; proceed = proc; }
    void execute()
    {
        loadDialog(number, "dialog.txt");
    }
    bool GetProceed() { return proceed; }
    int number;
    bool proceed;
};

class ProceedCommand :public Command
{
public:
    ProceedCommand(int num, bool proc = false) { number = num; proceed = proc; }
    void execute()
    {
        loadDialog(number, "dialog.txt");
        if (proceed == false)
            proceed = true;
        else
            proceed = false;
    }
    bool GetProceed() { return proceed; }
    int number;
    bool proceed;
};

int main()
{
    map<string, Command*> commands;
    commands["Swing Sword"] = new AttackCommand();
    commands["swing sword"] = new AttackCommand();

    commands["Raise Shield"] = new DefendCommand();
    commands["raise shield"] = new DefendCommand();

    Player tempPlayer = { "Player", 10, 10, 10 };
    savePlayerInfo(tempPlayer, "player.txt");
    Player player = loadPlayerInfo(tempPlayer, "player.txt");
    //cout << "\nPlayer name: " << player.name << endl;
    //cout << "Player health: " << player.m_health << endl;
    //cout << "Player attack: " << player.m_attack << endl;
    //cout << "Player defense: " << player.m_defense << "\n\n";
    //
    //Enemy tempEnemy = { "Enemy", 5, 5, 3 };
    //saveEnemyInfo(tempEnemy, "enemy.txt");
	//Enemy enemy = loadEnemyInfo(tempEnemy, "enemy.txt");
    //cout << "\nEnemy name: " << enemy.name << endl;
    //cout << "Enemy health: " << enemy.m_health << endl;
    //cout << "Enemy attack: " << enemy.m_attack << endl;
    //cout << "Enemy defense: " << enemy.m_defense << "\n\n";
    //
    //
    //string input;
    //cout << "Enter a command (Swing Sword or Raise Shield): ";
    //getline(cin, input);
    //
    //if (commands.count(input) > 0) 
    //{
    //    commands[input]->execute();
    //    loadDialog(1, "dialog.txt");
    //}
    //else 
    //{
    //    cout << "Invalid command!" << endl;
    //}

	cout << "\n\n";
    loadDialog(1, "dialog.txt");
    loadDialog(2, "dialog.txt");

    bool isRunning = true;
    string input;

    do
    {
        commands["Go Through"] = new ProceedCommand(9);
        bool isMainRoom = false;

        cout << "\n\n";
        getline(cin, input);

        if (commands.count(input) > 0)
        {
            commands[input]->execute();
            if (commands[input]->GetProceed() == true)
                isMainRoom = true;
            else
                isMainRoom = false;
        }
        else
        {
            cout << "That's not something you can do.";
        }

        while (isMainRoom)
        {
            commands["Inspect Door"] = new ActionCommand(3);
            commands["Inspect door"] = new ActionCommand(3);
            commands["inspect door"] = new ActionCommand(3);
            commands["Check Door"] = new ActionCommand(3);
            commands["Check door"] = new ActionCommand(3);
            commands["check door"] = new ActionCommand(3);

	        cout << "\n\n";
        	getline(cin, input);

        	if(commands.count(input) > 0)
        	{
        		commands[input]->execute();
        	}
        	else
        	{
        		cout << "That's not something you can do.";
        	}
        }
    }
    while (isRunning);
    

    return 0;
}