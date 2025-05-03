#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void gotoXY(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

class locationInfo {
private:
	int arr[6] = { 77,77,77,77,77,77 };
public:
	void setLocation(int location) {
		arr[5] = location;
	}

	const int* getLocation() const {
		return arr;
	}

	void moveLocation() {
		arr[0] = arr[1];
		arr[1] = arr[2];
		arr[2] = arr[3];
		arr[3] = arr[4];
		arr[4] = arr[5];
	}
};


int main() {

	

	locationInfo info;

	system("mode con: cols=50 lines=30");
	//가로 50 세로 30

	int x = 10;
	int y = 10;
	int key;

	while (1) {
		Sleep(100);
		system("cls");
		//0.1초마다 화면 출력

		gotoXY(x, y);
		//초기 커서 위치 설정

		int tempX = x;
		int tempY = y;
		//뱀 그리기 위한 임시 위치 설정

		if (_kbhit()) {

			key = _getch();

			if ((info.getLocation()[5] == LEFT || info.getLocation()[5] == RIGHT) && (key == UP || key == DOWN)) {
				info.setLocation(key);
			}
			else  if ((info.getLocation()[5] == UP || info.getLocation()[5] == DOWN) && (key == LEFT || key == RIGHT)){
				info.setLocation(key);
			}

			/*if (key == LEFT || key == RIGHT || key == UP || key == DOWN) {
				info.setLocation(key);
			}*/

		}
		//만약 상하좌우 중 하나 누르면
		//위치 정보 맨 끝에 어떤 키 눌렀는지 정보 추가

		for (int i = 0; i < 6; ++i) {
			if (info.getLocation()[i] == RIGHT) {
				++tempX;
			}
			if (info.getLocation()[i] == LEFT) {
				--tempX;
			}
			if (info.getLocation()[i] == UP) {
				--tempY;
			}
			if (info.getLocation()[i] == DOWN) {
				++tempY;
			}

			gotoXY(tempX, tempY);
			cout << "@";
		}
		//위치 정보 맞춰서 뱀 그리기
		//상하좌우 정보 맞춰서 임시 좌표 변경하고 그림

		if (tempX == 0 || tempY == 0 || tempX ==49 || tempY ==30) {
			break;
		}//충돌판정

		if (info.getLocation()[0] == RIGHT) {
			++x;
		}
		if (info.getLocation()[0] == LEFT) {
			--x;
		}
		if (info.getLocation()[0] == UP) {
			--y;
		}
		if (info.getLocation()[0] == DOWN) {
			++y;
		}
		//꼬리부분 위치 맞춰서 커서 좌표 수정
		//꼬리부분이 아직 오른쪽 이동중이면 다음 프레임에서 커서는 오른쪽으로 이동 해야함
		//하키 누르고 꼬리까지 완전히 하로 정보 수정 시 커서는 아래쪽으로 이동

		info.moveLocation();

		
	}
	system("cls");
	gotoXY(0, 0);
	cout << "게임오버";


}