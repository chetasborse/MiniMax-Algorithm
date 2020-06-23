#include<bits/stdc++.h>
#include<cstdlib>
#include<ctime>
#include<limits>
using namespace std;

class Positions {
    public:
        int a[9];
};

class WinningCombination {
    public:
        int combinations[8][3] = {
			{0, 1, 2},
			{0, 3, 6},
			{0, 4, 8},
			{1, 4, 7},
			{2, 4, 6},
			{2, 5, 8},
			{3, 4, 5},
			{6, 7, 8}
		};
};

class Numb {
    public:
    int number;
    Numb *next;
};

int check1(Positions position) {
    WinningCombination wc;
    int zero = 0;
    for(int i = 0; i < 8; i++) {
        if(position.a[i] == 0)
            zero++;
        if(position.a[wc.combinations[i][0]] == 1 && position.a[wc.combinations[i][1]] == 1 && position.a[wc.combinations[i][2]] == 1)
            return 1;
        else if(position.a[wc.combinations[i][0]] == 2 && position.a[wc.combinations[i][1]] == 2 && position.a[wc.combinations[i][2]] == 2)
            return 2;
    }
    if(zero == 0)
        return 3;
    else
        return 4;
    
}

int getpoints(Positions position, int fill, int depth) {
    int number = 0;
    if(depth % 2 == 0)
        position.a[fill] = 1;
    else
        position.a[fill] = 2;
    int status = check1(position);
    if(status == 3)
        return 0;
    else if(status == 1)
        return (10 - depth);
    else if(status == 2)
        return (-10 - depth);
    else {
        Numb *numb = NULL, *ptr;
        numb = new Numb();
        ptr = numb;
        ptr->next = NULL;
        for(int i = 0; i < 9; i++)
            if(position.a[i] == 0) {
                int points = getpoints(position , i, depth + 1);
                ptr->number = points;
                Numb *ptr1 = NULL;
                ptr1 = new Numb();
                ptr->next = ptr1;
                ptr1->next = NULL;
                ptr = ptr->next;
            }
        ptr = numb;
        if(depth % 2 == 0) {
            int max = INT_MAX;
            while(ptr->next) {
                if(max > ptr->number)
                    max = ptr->number;
                ptr = ptr->next;
            }
            return max;
        }
        else {
            int min = INT_MIN;
            while(ptr->next) {
                if(min < ptr->number)
                    min = ptr->number;
                ptr = ptr->next;
            }
            return min;
        }
    }
    return number;
}

int getpos(Positions position) {
    int max = -100, pos;
    for(int i = 0; i < 9; i++) {
        if(position.a[i] == 0) {
            int points = getpoints(position, i, 0);
            if(max < points) {
                max = points;
                pos = i;
            }
        }
    }
    return pos;
}

void print(int *curr_game_box, char comp_player, char user_player) {
	cout << "\t\t\t\n";
		for(int i = 0; i < 9; i++) {
			if(i == 0 || i == 3 || i == 6)
				cout << "\t\t\t";
			switch(curr_game_box[i]) {
				case 0:
					cout << "    ";
					break;
				case 1:
					cout << "  "  << comp_player << " ";
					break;
				case 2:
					cout << "  "  <<user_player << " ";
			}
			if(i != 2 && i != 5 && i != 8)		
				cout << "|";
			if(i == 2 || i == 5 ) {
				printf("\n\t\t\t--------------\n");
			}
		}
}

int main() {
again:
    system("clear");
    int counter = 0, pos;
    Positions position;

    int X, O;
	char user_player, comp_player;
	cout << "Choose between 'X' and 'O' : ";
	cin >> user_player;
	if(user_player == 'x' || user_player == 'X') {
		X = 2;
		O = 1;
		user_player = 'X';
		comp_player = 'O';
	}
	else {
		X = 1;
		O = 2;
		user_player = 'O';
		comp_player = 'X';
	}

    cout << "\t\t\t  1 | 2  | 3  \n"; 
	cout << "\t\t\t--------------\n"; 
	cout << "\t\t\t  4 | 5  | 6  \n"; 
	cout << "\t\t\t--------------\n"; 
	cout << "\t\t\t  7 | 8  | 9  \n\n"; 
    cout << "-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n";

    cout << "Do you want to go first?(Y/N)? ";
	char des;
	cin >> des;
	int s = 0;
	if (des == 'y' || des == 'Y')
		s = 1;

    for(int i = 0; i < 9; i++)
        position.a[i] = 0;

    while(counter < 9) {
        if((counter + s) % 2 == 1) {
            back:
            cout << "Enter the position: ";
            cin >> pos;
            if(position.a[pos - 1] != 0)  {
                cout << "The place is already taken\n";
                goto back;
            }
            position.a[pos - 1] = 2;
        }
        else if(counter == 0) {
            srand((unsigned) time(0));
			int pos = (rand() % 9);
            cout << "Computer took " << pos + 1 << "\n";
            position.a[pos] = 1;
        } 
        else {
            pos = getpos(position);
            cout << "Computer took " << pos + 1 << "\n";
            position.a[pos] = 1;
        }
        counter++;
        print(position.a, comp_player, user_player); 
        int k = check1(position);
        if(k == 1) {
            cout << "\n\n\t\t\tYou lost the game :(\n";
            break;
        }
        else if(k == 2) {
            cout << "\n\n\t\t\tYou won the game :)\n";
            break;
        }
        else if(k == 3) {
            cout << "\n\t\t\tGame Tied!!!";
        }
        cout << "\n\n";         
    }
    cout << "Do you wish to play again? (Y/N)\n";
	char entry;
	cin >> entry;
	if(entry == 'y' || entry == 'Y')
		goto again;
    return 0;
}
