#include <iostream>
using namespace std;

void Init(int* array, int length);
bool Check(int* array, int length);

//54 - 1、ジジを抜いた枚数
const int CARD_MAX = 53;

const int PLAYER_0 = 0;
const int PLAYER_1 = 1;
const int UNDISTRIBUTION = 2;
const int NUM_OF_TYPES = 4;

int main() {
	srand(time(NULL));
	int average = 0;
	const int NUM_OF_EXECUTINS = 100;
	int checker[CARD_MAX];

	for (int n = 0; n < NUM_OF_EXECUTINS; n++) {

		int count = 0;

		do {
			Init(checker, sizeof(checker) / sizeof(checker[0]));
			count++;
			bool oddTurn = true;

			for (int i = 0; i < CARD_MAX; i++) {
				while (1) {
					int r = rand() % CARD_MAX;
					if (checker[r] == UNDISTRIBUTION) {
						//if(r == 52) cout << r << ", " << (oddTurn ? "PLAYER_0" : "PLAYER_1") << ", \n";
						checker[r] = (oddTurn ? PLAYER_0 : PLAYER_1);
						oddTurn = !oddTurn;
						break;
					}
				}
			}
		} while (!Check(checker, sizeof(checker) / sizeof(checker[0])));

		cout << "試行" << n << "回目終了\n";
		for (int i = 0; i < CARD_MAX; i++) {
			cout << "内訳" << i << " : " << checker[i] << ", ";
			if (i != 0 && (i + 1) % NUM_OF_TYPES == 0) cout << "\n";
		}
		cout << "\n";
		average += count;
	}

	int result = average / NUM_OF_EXECUTINS;
	cout << "トランプ配布時に試合を終了させるには平均" << result << "回の試行が必要です。(" << NUM_OF_EXECUTINS << "回の試行結果)\n";
	cout << "確率は" << (1.0 / (double)result) << "\n";
}

void Init(int* array, int length) {
	for (int i = 0; i < length; i++) {
		array[i] = UNDISTRIBUTION;
	}
}

bool Check(int* array, int length) {
	int count_0 = 0;
	int count_1 = 0;

	for (int i = 0; i < length; i++) {
		if (array[i] == PLAYER_0) count_0++;
		else if (array[i] == PLAYER_1) count_1++;
		else return false;

		if (count_0 + count_1 == NUM_OF_TYPES) {
			int cond = NUM_OF_TYPES / 2;
			if (count_0 == cond && count_1 == cond) {
				count_0 = 0;
				count_1 = 0;
				continue;
			}
			else return false;
		}
	}
	if (array[52] == PLAYER_1) cout << "BABA";
	return true;
}