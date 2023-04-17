#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "Cpp_List.h"

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
    Command(int num, string key, bool proc = false, bool act = false)
    {
        number = num; proceed = proc; type = key; action = act;
    }
    void Execute()
    {
        if (action)
        {
            loadDialog(1, "dialog.txt");
            item = false;
        }
        else if (GetType() == "Main Hall" || GetType() == "Main Room" || GetType() == "Music Room"
			|| GetType() == "Reception Room" || GetType() == "Dining Room" || GetType() == "Kitchen" 
            || GetType() == "Storage Room" || GetType() == "Cabinets")
        {
            loadDialog(number, "dialog.txt");
        }
        else if(GetType() == "Zero" || GetType() == "One" || GetType() == "Two" || GetType() == "Three" ||
            GetType() == "Four" || GetType() == "Five" || GetType() == "Six" || GetType() == "Seven" || 
            GetType() == "Eight" || GetType() == "Nine")
        {
            loadDialog(number, "dialog.txt");
        }
        else
        {
            loadDialog(number, "dialog.txt");

            if (GetType() == "White Marble" || GetType() == "Green Marble" || GetType() == "Purple Marble" ||
                GetType() == "Blue Marble" || GetType() == "Pen" || GetType() == "Candle")
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
    bool GetItem() { return item; }
    string GetType() { return type; }
    int number;
    bool proceed, action, item = false;
    string type;
};

int main()
{
    map<string, Command*> commands;
    List<string> inventory;

    cout << "Warning: commands only take lower cases.\n"
        "         and there are no boundaries between rooms. Proceed with caution.";
    cout << "\n\n\n";
    loadDialog(3, "dialog.txt");

    bool isRunning = true;
    bool pen = false, candle = false;
    string input;

    commands["check door"] = new Command(4, "none");
    commands["open door"] = new Command(5, "none");
    commands["check vase"] = new Command(6, "none");
    commands["break vase"] = new Command(7, "none");
    commands["take wmarble"] = new Command(8, "White Marble");
    commands["turn around"] = new Command(9, "none");
    commands["go down"] = new Command(12, "Main Hall");

    commands["go back"] = new Command(10, "Main Room");
    commands["go left"] = new Command(15, "Music Room");
    commands["go right"] = new Command(20, "Reception Room");
    commands["go across"] = new Command(40, "Dining Room");

    commands["go hall"] = new Command(13, "Main Hall");
    commands["check piano"] = new Command(16, "none");
    commands["use pen"] = new Command(17, "Use Pen");
    commands["take gmarble"] = new Command(18, "Green Marble");

    commands["check bookshelf"] = new Command(21, "none");
    commands["check curtains"] = new Command(22, "none");
    commands["check desk"] = new Command(23, "none");
    commands["take pen"] = new Command(24, "Pen");
    commands["check cabinets"] = new Command(25, "Cabinets");
    commands["input zero"] = new Command(26, "Zero");
    commands["input one"] = new Command(27, "One");
    commands["input two"] = new Command(28, "Two");
    commands["input three"] = new Command(29, "Three");
    commands["input four"] = new Command(30, "Four");
    commands["input five"] = new Command(31, "Five");
    commands["input six"] = new Command(32, "Six");
    commands["input seven"] = new Command(33, "Seven");
    commands["input eight"] = new Command(34, "Eight");
    commands["input nine"] = new Command(35, "Nine");
    commands["take pmarble"] = new Command(38, "Purple Marble");

    commands["check table"] = new Command(41, "none");
    commands["take plate"] = new Command(42, "none");
    commands["take fork"] = new Command(42, "none");
    commands["take butterknife"] = new Command(42, "none");
    commands["take candle"] = new Command(43, "Candle");
    commands["light candles"] = new Command(44, "Use Candle");
    commands["take bmarble"] = new Command(45, "Blue Marble");

    commands["white marble"] = new Command(48, "none");
    commands["green marble"] = new Command(49, "none");
    commands["purple marble"] = new Command(50, "none");
    commands["blue marble"] = new Command(51, "none");

    do
    {
        bool isMainRoom = true;

        while (isMainRoom)
        {
            bool isMainHall = false;

            if (commands["take wmarble"]->GetItem() && commands["take bmarble"]->GetItem() &&
                commands["take pmarble"]->GetItem() && commands["take gmarble"]->GetItem())
            {
                loadDialog(47, "dialog.txt");
                cout << "\n\n";
                getline(cin, input);

                if (commands.count(input) > 0)
                    commands[input]->Execute();
                else
                    cout << "That's not something you can do.";

                if (commands[input] == commands["white marble"])
                {
                    cout << "\n\n";
                    getline(cin, input);

                    if (commands.count(input) > 0)
                        commands[input]->Execute();
                    else
                        cout << "That's not something you can do.";

                    if (commands[input] == commands["blue marble"])
                    {
                        cout << "\n\n";
                        getline(cin, input);

                        if (commands.count(input) > 0)
                            commands[input]->Execute();
                        else
                            cout << "That's not something you can do.";
                        if (commands[input] == commands["green marble"])
                        {
                            cout << "\n\n";
                            getline(cin, input);

                            if (commands.count(input) > 0)
                                commands[input]->Execute();
                            else
                                cout << "That's not something you can do.";
                            if (commands[input] == commands["purple marble"])
                            {
                                loadDialog(53, "dialog.txt");
                                isRunning = false;
                            }
                            else
                            {
                                loadDialog(52, "dialog.txt");
                                isRunning = false;
                            }
                        }
                        else
                        {
                            cout << "\n\n";
                            getline(cin, input);

                            if (commands.count(input) > 0)
                                commands[input]->Execute();
                            else
                                cout << "That's not something you can do.";

                            loadDialog(52, "dialog.txt");
                            isRunning = false;
                        }
                    }
                    else
                    {
                        for (unsigned i = 0; i < 2; i++)
                        {
                            cout << "\n\n";
                            getline(cin, input);

                            if (commands.count(input) > 0)
                                commands[input]->Execute();
                            else
                                cout << "That's not something you can do.";
                        }

                        loadDialog(52, "dialog.txt");
                        isRunning = false;
                    }
                }
                else
                {
                    for (unsigned i = 0; i < 3; i++)
                    {
                        cout << "\n\n";
                        getline(cin, input);

                        if (commands.count(input) > 0)
                            commands[input]->Execute();
                        else
                            cout << "That's not something you can do.";
                    }

                    loadDialog(52, "dialog.txt");
                    isRunning = false;
                }
            }
            cout << "\n\n";
            getline(cin, input);

            if (commands.count(input) > 0)
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
                    inventory.Add(commands[input]->GetType());
                }
            }
            else
            {
                cout << "That's not something you can do.";
            }

            while (isMainHall)
            {
                bool isMusicRoom = false;
                bool isReceptionRoom = false;
                bool isDiningRoom = false;

                cout << "\n\n";
                getline(cin, input);

                if (commands.count(input) > 0)
                {
                    commands[input]->Execute();
                    if (commands[input]->GetProceed() == true)
                    {
                        if (commands[input]->GetType() == "Main Room")
                            isMainHall = false;
                        else if (commands[input]->GetType() == "Music Room")
                            isMusicRoom = true;
                        else if (commands[input]->GetType() == "Reception Room")
                            isReceptionRoom = true;
                        else if (commands[input]->GetType() == "Dining Room")
                            isDiningRoom = true;
                    }
                    else
                        isMainHall = true;
                }
                else
                {
                    cout << "That's not something you can do.";
                }

                while (isMusicRoom)
                {
                    cout << "\n\n";
                    getline(cin, input);

                    if (commands.count(input) > 0)
                    {
                        commands[input]->Execute();
                        if (commands[input]->GetProceed() == true)
                        {
                            if (commands[input]->GetType() == "Main Hall")
                                isMusicRoom = false;
                        }
                        else
                            isMusicRoom = true;

                        if (commands[input]->GetType() == "Use Pen" && pen)
                        {
                            inventory.Remove(commands[input]->GetType());
                        }
                        else if (commands[input]->GetType() == "Green Marble" && commands[input]->GetItem() == true)
                        {
                            inventory.Add(commands[input]->GetType());
                        }
                    }
                    else
                    {
                        cout << "That's not something you can do.";
                    }
                }

                while (isReceptionRoom)
                {
                    cout << "\n\n";
                    getline(cin, input);

                    if (commands.count(input) > 0)
                    {
                        commands[input]->Execute();
                        if (commands[input]->GetProceed() == true)
                        {
                            if (commands[input]->GetType() == "Main Hall")
                                isReceptionRoom = false;
                        }
                        else
                            isReceptionRoom = true;

                        if (commands[input]->GetType() == "Purple Marble" && commands[input]->GetItem() == true)
                        {
                            inventory.Add(commands[input]->GetType());
                        }
                        else if (commands[input]->GetType() == "Pen" && commands[input]->GetItem() == true)
                        {
                            inventory.Add(commands[input]->GetType());
                            pen = true;
                        }

                        if (commands[input]->GetType() == "Cabinets")
                        {
                            bool isAttempting = true;
                            while (isAttempting)
                            {
	                            cout << "\n\n";
                            	getline(cin, input);

                            	if (commands.count(input) > 0)
                            		commands[input]->Execute();
                            	else
                            		cout << "That's not something you can do.";

                            	if (commands[input] == commands["input six"])
                            	{
                            		cout << "\n\n";
                            		getline(cin, input);

                            		if (commands.count(input) > 0)
                            			commands[input]->Execute();
                            		else
                            			cout << "That's not something you can do.";

                            		if (commands[input] == commands["input nine"])
                            		{
                            			cout << "\n\n";
                            			getline(cin, input);

                            			if (commands.count(input) > 0)
                            				commands[input]->Execute();
                            			else
                            				cout << "That's not something you can do.";
                            			if (commands[input] == commands["input four"])
                            			{
                            				cout << "\n\n";
                            				getline(cin, input);

                            				if (commands.count(input) > 0)
                            					commands[input]->Execute();
                            				else
                            					cout << "That's not something you can do.";
                            				if (commands[input] == commands["input one"])
                            				{
                            					loadDialog(37, "dialog.txt");
                                                isAttempting = false;
                            				}
                            				else
                            				{
                            					loadDialog(36, "dialog.txt");
                                                isAttempting = false;
                            				}
                            			}
                            			else
                            			{
                            				cout << "\n\n";
                            				getline(cin, input);

                            				if (commands.count(input) > 0)
                            					commands[input]->Execute();
                            				else
                            					cout << "That's not something you can do.";

                            				loadDialog(36, "dialog.txt");
                                            isAttempting = false;
                            			}
                            		}
                            		else
                            		{
                            			for (unsigned i = 0; i < 2; i++)
                            			{
                            				cout << "\n\n";
                            				getline(cin, input);

                            				if (commands.count(input) > 0)
                            					commands[input]->Execute();
                            				else
                            					cout << "That's not something you can do.";
                            			}

                            			loadDialog(36, "dialog.txt");
                                        isAttempting = false;
                            		}
                            	}
                            	else
                            	{
                            		for (unsigned i = 0; i < 3; i++)
                            		{
                            			cout << "\n\n";
                            			getline(cin, input);

                            			if (commands.count(input) > 0)
                            				commands[input]->Execute();
                            			else
                            				cout << "That's not something you can do.";
                            		}

                            		loadDialog(36, "dialog.txt");
                            		isAttempting = false;
                            	}
                            }
                        }
                        else
                        {
                            cout << "That's not something you can do.";
                        }
                    }

                    while (isDiningRoom)
                    {
                        cout << "\n\n";
                        getline(cin, input);

                        if (commands.count(input) > 0)
                        {
                            commands[input]->Execute();
                            if (commands[input]->GetProceed() == true)
                            {
                                if (commands[input]->GetType() == "Main Hall")
                                    isDiningRoom = false;
                            }
                            else
                                isDiningRoom = true;

                            if (commands[input]->GetType() == "Blue Marble" && commands[input]->GetItem() == true)
                            {
                                inventory.Add(commands[input]->GetType());
                            }
                            else if (commands[input]->GetType() == "Candle" && commands[input]->GetItem() == true)
                            {
                                inventory.Add(commands[input]->GetType());
                                candle = true;
                            }

                            if (commands[input]->GetType() == "Use Candle" && candle)
                            {
                                inventory.Remove(commands[input]->GetType());
                            }
                        }
                        else
                        {
                            cout << "That's not something you can do.";
                        }
                    }
                }
            }
        }
    } while (isRunning);

	return 0;
}