#include<bits/stdc++.h>
#include<cstdlib>
#include<ctime>
using namespace std;

class WinningCombination {
	public:
		int comb[9][9] = {
			{0, 1, 1, 1, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 0, 0, 1, 0},
			{1, 1, 0, 0, 1, 1, 1, 0, 1},
			{1, 0, 0, 0, 1, 1, 1, 0, 0},
			{1, 1, 1, 1, 0, 1, 1, 1, 1},
			{0, 0, 1, 1, 1, 0, 0, 0, 1},
			{1, 0, 1, 1, 1, 0, 0, 1, 1},
			{0, 1, 0, 0, 1, 0, 1, 0, 1},
			{1, 0, 1, 0, 1, 1, 1, 1, 0}
	       	};
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
		int *getnums(int pos) {
			return comb[pos];
		};
		int thirdnum(int first, int second) {
			int k = 0, third;
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 3; j++) {
					if(combinations[i][j] == first || combinations[i][j] == second)
						k++;
					else
						third = combinations[i][j];
				}
				if(k == 2) {
					return third;
				}
				k = 0;
			}
			return -1;
		};
		bool winner(int *a, int num) {
			for(int i = 0; i < 8; i++) {
				if(a[combinations[i][0]] == num && a[combinations[i][1]] == num && a[combinations[i][2]] == num)
				       return true;
			}
			return false;
		};

};

class Sequence {
	public:
		int num;
		Sequence *next;
};

int compare(int *a, int count) {
	int pos, j = -1;
		if(count > 2) {
			WinningCombination com, use;
			for(int x = 0; x < 8; x++) {
				for(int y = x + 1; y < 9; y++) {
					if(a[x] == 1 && a[y] == 1) {
						int third = com.thirdnum(x, y);
						if(third != -1 && a[third] == 0)
							return third;
					}
				}
			}

			for(int x = 0; x < 8; x++) {
				for(int y = x + 1; y < 9; y++) {
					if(a[x] == 2 && a[y] == 2) {
						int third = use.thirdnum(x, y);
						if(third != -1 && a[third] == 0) {
							return third;
						}
					}
				}
			}
		}
		Sequence *start = NULL, *ptr, *ptr2;
		start = new Sequence();
		start->next = NULL;
		ptr = start;
			for(int i = 0; i < 9; i++) {
				if(a[i] == 0) {
					ptr->num = i;
					Sequence *ptr1 = NULL;
					ptr1 = new Sequence();
					ptr2 = ptr;
					ptr1->next = NULL;
					ptr->next = ptr1;
					ptr = ptr->next;
				}
			}
			ptr2->next = start;
			ptr = start;
			srand((unsigned) time(0));
			int rando = (rand() % 9);
			while(rando >= 0) {
				if(rando == 0)
					return ptr->num;
				ptr = ptr->next;
				rando--;
			}
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
	int curr_game_box[9], match = 0;
	for(int i = 0; i < 9; i++) {
		curr_game_box[i] = 0;
	}

	WinningCombination com;

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
	
	printf("\t\t\t  1 | 2  | 3  \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t  4 | 5  | 6  \n"); 
	printf("\t\t\t--------------\n"); 
	printf("\t\t\t  7 | 8  | 9  \n\n"); 
      	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");
	
	cout << "Do you want to go first?(Y/N)? ";
	char des;
	cin >> des;
	int s = 0;
	if (des == 'y' || des == 'Y')
		s = 1;

	int pos, counter = 0;
	while(counter < 9) {
		if((counter + s) % 2 == 1) {
			here:
			cout << "\n\nEnter the position: ";
			cin >> pos;
			pos = pos - 1;
			if(curr_game_box[pos] != 0) {
				goto here;
			}
			int *a = com.getnums(pos);
			curr_game_box[pos] = 2;
			if(com.winner(curr_game_box, 2)) {
			       cout << "\nYou have won :)\n";
			       match++;
		       		break;
		 	}
		}
		else if(counter == 0) {
			cout << "\nComputer took 5\n";
			pos = 4;
			int *a = com.getnums(pos);
			curr_game_box[pos] = 1;
		}
		else {
			pos = compare(curr_game_box, counter);
			cout << "\nComputer took " << pos + 1<< "\n";
			int *a = com.getnums(pos);
			curr_game_box[pos] = 1;
			if(com.winner(curr_game_box, 1)) {
				cout << "\nYou have lost :(\n";
				match++;
				break;
			}
		}
		counter++;
		print(curr_game_box, comp_player, user_player); 
		
	}
	if(match == 0)
		cout << "\nMatch Tied\n";
	else 
		print(curr_game_box, comp_player, user_player);
	cout << "\n";
	cout << "Do you wish to play again? (Y/N)\n";
	char entry;
	cin >> entry;
	if(entry == 'y' || entry == 'Y')
		goto again;
	return 0;
}
