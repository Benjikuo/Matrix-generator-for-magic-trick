#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

int base_matrix[4][4] = {
    {0, 7, 9, 14},
    {11, 12, 2, 5},
    {6, 1, 15, 9},
    {13, 10, 4, 3}
};

void make(int goal, int user[4][4] = nullptr) {
    int n = (goal - 30) / 4;
    int k = (goal - 30) % 4;
    int ans[4][4];
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            ans[i][j] = base_matrix[i][j] + n;

    ans[0][3] += k;
    ans[1][1] += k;
    ans[2][2] += k;
    ans[3][0] += k;

    if (user == nullptr) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++)
                cout << ans[i][j] << "\t";
            cout << "\n";
        }
        return;
    }

    int wrong = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (user[i][j] != ans[i][j]) {
                cout << ans[i][j] << "*\t";
                wrong++;
            } else cout << ans[i][j] << "\t";
        }
        cout << "\n";
    }

    if (wrong == 0) cout << "\nAll correct!\n";
    else cout << "\nYou got " << wrong << " numbers wrong.\n";
    return;
}

void play() {
    int goal = rand() % (100 - 34 + 1) + 34;
    int user[4][4];
    string str;

    cout << "\nTry to enter a magic square with total sum " << goal << " (new/ans/use/exit/help)\n";
    for (int i = 0; i < 4; i++) {
        cout << "> row" << i + 1 << ": ";
        for (int j = 0; j < 4; j++) {
            while (true) {
                cin >> str;
                try {
                    user[i][j] = stoi(str);
                    break;
                } catch (const exception& e) {
                    if (str == "new") {
                        play();
                        return;
                    } else if (str == "ans") {
                        cout << "\nAns:\n";
                        make(goal);
                        play();
                        return;
                    } else if (str == "use") {
                        while (true) {
                            cout << "\n> Enter a number: ";
                            cin >> goal;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore();
                                cout << "\nIt is not a number.\n";
                            } else break;
                        }
                        cout << "\nTry to enter a magic square with total sum " << goal << " (new/ans/use/exit/help)\n";
                        cout << "> row" << i + 1 << ": ";
                    } else if (str == "exit") {
                        return;
                    } else if (str == "help") {
                        cout << "\nCommands:\n";
                        cout << "- new: Start a new game with a new number.\n";
                        cout << "- ans: The answer of this game.\n";
                        cout << "- use: Set a goal number.\n";
                        cout << "- exit: Change a mode.\n";
                        cout << "\n> row" << i + 1 << ": ";
                    } else {
                        cout << "\nInvalid number. Try again.\n";
                        cout << "> row" << i + 1 << ": ";
                    }
                }
            }
        }
    }
    cout << "\nAns: (* means wrong)\n";
    make(goal, user);
    play();
}

int main() {
    srand(time(NULL));
    string str;
    int goal;

    cout << "\\\\ Welcome to the magic matrix generator //\n";

    while (true) {
        cout << "\nQ: What do you like to do? (make/play/help/exit)\nA: ";
        cin >> str;

        if (str == "make") {
            while (true) {
                cout << "\n> Enter a number: ";
                cin >> goal;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore();
                    cout << "\nIt is not a number.\n";
                } else break;
            }
            cout << "\nGenerated magic matrix (sum: " << goal << ")\n";
            make(goal);
        } else if (str == "play") {
            play();
        } else if (str == "help") {
            cout << "\nCommands:\n"
                 << "- make: Generate a magic matrix with given sum.\n"
                 << "- play: Generate a random target.\n"
                 << "- exit: Quit the program.\n";
        } else if (str == "exit") {
            cout << "\nSee you next time!";
            break;
        } else {
            cout << "\nPlease enter make/play/help/exit\n";
        }
    }
    return 0;
}
