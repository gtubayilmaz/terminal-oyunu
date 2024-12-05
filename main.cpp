#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Character Sınıfı
class Character {
protected:
    string name;
    int health;
    int attackPower;

public:
    Character(string characterName) {
        name = characterName;
        health = 100;  // Başlangıç sağlığı
        attackPower = rand() % 20 + 10;  // Saldırı gücü 10 ile 30 arasında
    }

    void attack(Character &opponent) {
        int damage = rand() % attackPower + 1;  // Saldırı gücüne göre rastgele hasar
        cout << name << " saldırdı! " << opponent.name << " " << damage << " hasar aldı." << endl;
        opponent.takeDamage(damage);  // Rakibe zarar ver
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    void printStatus() {
        cout << name << " Sağlık: " << health << endl;
    }

    bool isAlive() {
        return health > 0;
    }

    string getName() {
        return name;
    }
};

// Player Sınıfı
class Player : public Character {
private:
    int score;

public:
    Player(string playerName) : Character(playerName) {
        score = 0;
    }

    void printStatus() {
        cout << name << " Sağlık: " << health << ", Skor: " << score << endl;
    }

    void attack(Character &opponent) {
        Character::attack(opponent);
        score += 10;  // Her saldırı sonrası oyuncuya puan eklenir
    }
};

// Enemy Sınıfı
class Enemy : public Character {
private:
    string type;

public:
    Enemy(string enemyType) : Character(enemyType) {
        type = enemyType;
    }

    void attack(Character &opponent) {
        int damage = rand() % attackPower + 1;
        cout << type << " saldırdı! " << opponent.getName() << " " << damage << " hasar aldı." << endl;
        opponent.takeDamage(damage);
    }
};

// Weapon Sınıfı
class Weapon {
private:
    string name;
    int damage;

public:
    Weapon(string weaponName, int weaponDamage) : name(weaponName), damage(weaponDamage) {}

    void use(Character &target) {
        cout << name << " kullanıldı!" << endl;
        target.takeDamage(damage);
    }
};

// Game Sınıfı
class Game {
private:
    Player player;
    Enemy enemy;

public:
    Game(string playerName, string enemyType) : player(playerName), enemy(enemyType) {}

    void start() {
        cout << "Oyun başladı!" << endl;

        while (player.isAlive() && enemy.isAlive()) {
            player.printStatus();
            enemy.printStatus();

            // Oyuncu sırası
            cout << "\n" << player.getName() << "'in sırası!" << endl;
            player.attack(enemy);

            if (enemy.isAlive()) {
                // Düşman sırası
                cout << "\n" << enemy.getName() << "'in sırası!" << endl;
                enemy.attack(player);
            }

            cout << endl;
            system("pause");
            system("cls");  // Ekranı temizle (Windows için)
        }

        if (player.isAlive()) {
            cout << player.getName() << " Kazandı!" << endl;
        } else {
            cout << enemy.getName() << " Kazandı!" << endl;
        }
    }
};

int main() {
    srand(time(0));  // Rastgele sayılar için zaman bazlı tohum

    string playerName, enemyType;
    cout << "Oyuncu adını girin: ";
    cin >> playerName;
    cout << "Düşman türünü girin (örneğin: Ork, Ejderha): ";
    cin >> enemyType;

    Game game(playerName, enemyType);
    game.start();

    return 0;
}

/*

+----------------+        +-------------------+       +---------------+
|   Character    |<-------|      Player       |       |    Enemy      |
+----------------+        +-------------------+       +---------------+
| - name: string |        | - score: int      |       | - type: string |
| - health: int  |        |                   |       |               |
| - attack: int  |        | + attack()        |       | + attack()    |
+----------------+        | + takeDamage()    |       | + takeDamage()|
| + attack()      |        | + printStatus()   |       | + printStatus()|
| + takeDamage()  |        +-------------------+       +---------------+
| + printStatus() |
+----------------+           ^
        |                    |
        |                    |
        v                    |
+-------------------+      +---------------+
|     Weapon        |      |      Game     |
+-------------------+      +---------------+
| - name: string    |      | - player: Player|
| - damage: int     |      | - enemy: Enemy  |
+-------------------+      | + start()       |
| + use()           |      | + end()         |
+-------------------+      +---------------+

*/