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

class Command
{
public:
    Command(int num, string key, bool proc = false, bool act = false, bool allow = false)
    {
        number = num; proceed = proc; type = key; action = act; allowed = allow;
    }
    void Execute()
    {
        if (action)
        {
	        loadDialog(1, "dialog.txt");
        	item = false;
        }
        else
        {
            loadDialog(number, "dialog.txt");

            if (GetType() == "White Marble")
                item = true;
        	action = true;
        }
        if (proceed)
            proceed = false;
        else
            proceed = true;
    }
    bool GetProceed() { return proceed; }
    bool GetAction() { return action; }
    bool GetAllowed() { return allowed; }
    bool GetItem() { return item; }
    void SetAllowed(bool allow) { allowed = allow; }
    string GetType() { return type; }
    int number;
    bool proceed, action, allowed, item = false;
    string type;
};

int main()
{
    map<string, Command*> commands;

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

    cout << "Warning: commands only take lower cases.\n";
	cout << "\n\n";
    loadDialog(2, "dialog.txt");
    loadDialog(3, "dialog.txt");

    bool isRunning = true;
    string input;
    int marbleCnt = 0;

	commands["check door"] = new Command(4, "none");
    commands["open door"] = new Command(5, "none");
    commands["check table"] = new Command(6, "none");
    commands["check vase"] = new Command(7, "none");
    commands["break vase"] = new Command(8, "none");
    commands["take marble"] = new Command(9, "White Marble");
    commands["turn around"] = new Command(10, "none");
    commands["go down"] = new Command(12, "Main Hall");

    commands["go back"] = new Command(11, "Main Room");

    do
    {
        bool isMainRoom = true;

        while (isMainRoom)
        {
            commands["check door"]->SetAllowed(true);
            commands["open door"]->SetAllowed(true);
            commands["check table"]->SetAllowed(true);
            commands["check vase"]->SetAllowed(true);
            commands["break vase"]->SetAllowed(true);
            commands["take marble"]->SetAllowed(true);
            commands["turn around"]->SetAllowed(true);
            commands["go down"]->SetAllowed(true);

            bool isMainHall = false;
	        cout << "\n\n";
        	getline(cin, input);

        	if(commands.count(input) > 0)
        	{
        		commands[input]->Execute();
                if (commands[input]->GetProceed() == true)
                {
                    if (commands[input]->GetType() == "Main Hall")
                        isMainHall = true;
                }
                else
                    isMainHall = false;

                if (commands[input]->GetType() == "White Marble" && commands[input]->GetItem() == true)
                {
	                marbleCnt++;
                	cout << marbleCnt << endl;
                }
        	}
        	else
        	{
        		cout << "That's not something you can do.";
        	}

            while (isMainHall)
            {
                commands["go back"]->SetAllowed(true);

                cout << "\n\n";
                getline(cin, input);

                if (commands.count(input) > 0)
                {
                    commands[input]->Execute();
                    if (commands[input]->GetProceed() == true)
                    {
	                    if (commands[input]->GetType() == "Main Room")
	                    	isMainHall = false;
                    }
                    else
                        isMainHall = true;
                }
                else
                {
                    cout << "That's not something you can do.";
                }
            }
        }
    }
    while (isRunning);
    

    return 0;
}