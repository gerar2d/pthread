#include <ctime>
#include <iostream>

using namespace std;

int pcr1, pcr2, pcr3, pcw1, pcw2, rCounter, wCounter, critInfo = 0;
bool key = false;

void r1 (int pcr1);
void r2 (int pcr2);
void r3 (int pcr3);
void w1 (int pcw1);
void w2 (int pcw2);
bool cAs (bool a);

int main (){
    for (int i = 0; i <= 1000; i++){
        int coin = rand() % 5;
        switch (coin)
        {
        case 0:
           r1(pcr1);
            break;
        case 1:
           r2(pcr2);
            break;
        case 2:
           r3(pcr3);
            break;
        case 3:
           w1(pcw1);
            break;
        case 4:
           w2(pcr2);
            break; 

        }
    }

}

void r1 (int a){
    switch (a)
    {
    case 0:
    //critical information.
        while (cAs(key) == true)cout<<"waiting************"<<endl;
        pcr1++;
        rCounter++;
        key = true;
        if (wCounter == 1 || rCounter == 2)cout<<"waiting*************"<<endl;
        for (int i = 0; i < 100000; i++){
            if (i == 1 || i == 99999){
                cout<<"crit: "<<critInfo<<" rCounter: "<<rCounter<<" wCounter: "<<wCounter<<endl;
            }
        }
        rCounter--;
        key = false;
        break;
    case 1:
        pcr1++;
        break;
    case 2:
        pcr1 = 0;
    cout<<"***pcr1***: "<<pcr1<<endl;
    }
}

void r2 (int a){
    switch (a)
    {

    case 0:
    //critical information.
        while (cAs(key) == true)cout<<"waiting************"<<endl;
        pcr2++;
        rCounter++;
        key = true;
        if (wCounter == 1 || rCounter == 2)cout<<"waiting*************"<<endl;
        for (int i = 0; i < 100000; i++){
            if (i == 1 || i == 99999){
                cout<<"crit: "<<critInfo<<" rCounter: "<<rCounter<<" wCounter: "<<wCounter<<endl;
            }
        }
        rCounter--;
        key = false;
        break;
    case 1:
        pcr2++;
        break;
    case 2:
        pcr2 = 0;
    cout<<"***pcr2***: "<<pcr2<<endl;
    }
}

void r3 (int a){
    switch (a)
    {

    case 0:
    //critical information.
        while (cAs(key) == true)cout<<"waiting************"<<endl;
        pcr3++;
        rCounter++;
        key = true;
        if (wCounter == 1 || rCounter == 2)cout<<"waiting*************"<<endl;
        for (int i = 0; i < 100000; i++){
            if (i == 1 || i == 99999){
                cout<<"crit: "<<critInfo<<" rCounter: "<<rCounter<<" wCounter: "<<wCounter<<endl;
            }
        }
        rCounter--;
        key = false;
        break;
    case 1:
        pcr3++;
        break;
    case 2:
        pcr3 = 0;
    cout<<"***pcr3***: "<<pcr3<<endl;
    }
}

void w1 (int a){
    switch (a)
    {

    case 0:
    //critical information.
        while (cAs(key) == true)cout<<"waiting************"<<endl;
        pcw1++;
        wCounter++;
        key = true;
        if (wCounter == 1 || rCounter == 2)cout<<"waiting***********"<<endl;
        for (int i = 0; i < 100000; i++){
            if (i == 1 || i == 99999){
                cout<<"crit: "<<critInfo<<" rCounter: "<<rCounter<<" wCounter: "<<wCounter<<endl;
            }
        }
        critInfo++;
        wCounter--;
        key = false;
        break;
    case 1:
        pcw1++;
        break;
    case 2:
        pcw1 = 0;
        cout<<"***pcw1***: "<<pcw1<<endl;
    }
}

void w2 (int a){
    switch (a)
    {
 
    case 0:
        while (cAs(key) == true)cout<<"waiting************"<<endl;
        pcw2++;
        wCounter++;
        key = true;
        if (wCounter == 1 || rCounter == 2)cout<<"waiting***********"<<endl;
        for (int i = 0; i < 100000; i++){
            if (i == 1 || i == 99999){
                cout<<"crit: "<<critInfo<<" rCounter: "<<rCounter<<" wCounter: "<<wCounter<<endl;
            }
        }
        critInfo++;
        wCounter--;
        key = false;
        break;
    case 1:
        pcw2++;
        break;
    case 2:
        pcw2 = 0;
        cout<<"***pcw2***: "<<pcw2<<endl;
    }
}

bool cAs (bool a) {
	bool rv = a;
	a = true;
	return rv;
}
