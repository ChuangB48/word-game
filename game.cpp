#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
vector <pair<char,pair<int,int>>> p;
int score=0,health=5000;
bool last[256]={false},f=false;
void press(){
    while(!f){
        for(int a=0;a<256;a++){
            auto state=GetAsyncKeyState(a);
            if((state&0x8000)&&!last[a]){
                auto button=MapVirtualKey(a,MAPVK_VK_TO_CHAR);
                int psize=p.size();
                bool z=false;
                for(int b=psize-1;b>=0;b--){
                    if(p[b].second.second>=33&&p[b].second.second<=35&&p[b].first==char(button)){
                        p.erase(p.begin()+b);
                        z=true;
                        break;
                    }
                }
                if(z){
                    score+=10;
                    health+=10;
                }
                else{
                    score--;
                    health-=100;
                }
                last[a]=true;
            }
            else if(!(state&0x8000)){
                last[a]=false;
            }
        }
    }
}
void screen(){
    int psize=p.size();
    string output="";
    for(int a=0;a<38;a++){
        if(a==34){
            bool z=false;
            for(int b=0;b<psize;b++){
                if(p[b].second.second==a){
                    z=true;
                    for(int c=0;c<p[b].second.first;c++){
                        output+='-';
                    }
                    output+=p[b].first;
                    for(int c=p[b].second.first+1;c<145;c++){
                        output+="-";
                    }
                }
            }
            if(!z){
                for(int b=0;b<145;b++){
                    output+="-";
                }
            }
        }
        else{
            for(int b=0;b<psize;b++){
                if(p[b].second.second==a){
                    for(int c=0;c<p[b].second.first;c++){
                        output+=' ';
                    }
                    output+=p[b].first;
                }
            }
        }
        output+='\n';
    }
    if(score<0){
        score=0;
    }
    cout << "\033[2J\033[H" << "health:" << health << '\n' << "score:" << score << '\n' << output;
    Sleep(150);
    health--;
}
void play(){
    srand(time(NULL));
    thread button(press);
    button.detach();
    while(true){
        int psize=p.size();
        for(int a=0;a<psize;a++){
            if(p[a].second.second>=38){
                p.erase(p.begin()+a);
                a--;
                score--;
                health-=10;
            }
            else{
                p[a].second.second++;
            }
        }
        if(rand()%3==0){
            p.push_back(make_pair(char(rand()%26+65),make_pair(rand()%145,0)));
        }
        if(health<=0){
            system("cls");
            if(score<0){
                score=0;
            }
            f=true;
            break;
        }
        screen();
    }
}
void start(){
    cout << "\n\n\n\n\n\n\n";
    cout << "                                  _____       _____       _____      __         __\n";
    cout << "                                 |     \\     |     \\     |         /          /\n";
    cout << "                                 |     |     |     |     |         |          |\n";
    cout << "                                 |     /     |     /     |         \\          \\\n";
    cout << "                                 |----/      |----/      |-----      --         --\n";
    cout << "                                 |           |\\          |              \\          \\\n";
    cout << "                                 |           | \\         |              |          |\n";
    cout << "                                 |           |  \\        |              /          /\n";
    cout << "                                 |           |   \\       |-----      --         --\n";
    cout << "\n\n\n";
    cout << "                                                  _____                    ___________    _____     _____\n";
    cout << "                                                 |         |\\       |          |         |         |     \\\n";
    cout << "                                                 |         | \\      |          |         |         |     |\n";
    cout << "                                                 |         |  \\     |          |         |         |     /\n";
    cout << "                                                 |-----    |   \\    |          |         |-----    |----/\n";
    cout << "                                                 |         |    \\   |          |         |         |\\\n";
    cout << "                                                 |         |     \\  |          |         |         | \\\n";
    cout << "                                                 |         |      \\ |          |         |         |  \\\n";
    cout << "                                                 |-----    |       \\|          |         |-----    |   \\\n";
    cout << "\n\n\n\n";
    while (true){
        if(GetAsyncKeyState(0x0D)&0x8000){
            cout << "\033[2J\033[H";
            play();
            break;
        }
    }
}
int main() {
    start();
    cout << "GameOver!\nScore:" << score << "\n";
    system("pause");
    return 0;
}
