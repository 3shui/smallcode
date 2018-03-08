#include "iostream"
#include "windows.h"
#include "conio.h" 
using namespace std;
int height;
int width;
int position_x;//飞机坐标 
int position_y;
int bullet_x;//子弹坐标 
int bullet_y;
int enemy_x;//敌机坐标 
int enemy_y;
int score;
int life; 

void hideCursor(){//隐藏光标 
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible=false;
	SetConsoleCursorInfo(handle,&CursorInfo);
}
void gotoXY(int x,int y){//控制光标位置 
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c={x,y};
	SetConsoleCursorPosition(handle,c); 
}
void startup(){//初始化 
	height=20;
	width=20;
	position_x=width/2;
	position_y=height/2;
	score=0;
	life=3;
	bullet_y=-1;
	enemy_x=position_x;
	enemy_y=0;
	hideCursor();
}
void show(){//输出画面 
	gotoXY(0,0);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			if(i==position_y&&j==position_x)cout<<"*";
			else if(i==bullet_y&&j==bullet_x)cout<<"|";
			else if(i==enemy_y&&j==enemy_x)cout<<"@";
			else cout<<" ";
		}
		cout<<endl;
	}
	cout<<"得分:"<<score<<"            "<<"生命: ";
	for(int i=0;i<life;i++){
		cout<<"O";
	}
	for(int i=0;i<3-life;i++){
		cout<<" ";//覆盖之前未扣掉的血 
	}
}
void updateWithInput(){//输入更新 
	char input;
	if(kbhit()){
		input=getch();
		if(input=='w'&&position_y>0)position_y--;
		if(input=='a'&&position_x>0)position_x--;
		if(input=='s'&&position_y<height-1)position_y++;
		if(input=='d'&&position_x<width-1)position_x++;
		if(input==' '){
			bullet_y=position_y-1;
			bullet_x=position_x;
		}
	}
}
void updateWithoutInput(){//无输入更新 
	if(bullet_x==enemy_x&&bullet_y==enemy_y){//检测击中 
		score++;
		enemy_y=0;
		enemy_x=rand()%width;
	}
	bullet_y--;
	//防止bullet_y=enemy_y+1,然后bullet_y-1,enemy_y+1时，会跳过检测 
	if(bullet_x==enemy_x&&bullet_y==enemy_y){
		score++;
		enemy_y=0;
		enemy_x=rand()%width;
	}
	static int speed=0;
	if(speed<30){
		speed++;
	}else{
		speed=0;
		if(enemy_y==height){
			enemy_y=0;
			enemy_x=rand()%width;
			life--; 
		}else{
			enemy_y++;
		}
	}

} 
int main(){
	startup();
	while(true){
		show();
		if(life==0)break;
		updateWithInput();
		updateWithoutInput();
	}
	return 0;
} 
