#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<vector>


#define NUM_REF 100
#define FRAME_START 0
#define FRAME_END 4

using namespace std;

int Ref[NUM_REF]{ 2,2,7,1,2,1,3,4,2,5,2,7,8,9,1,2,7,2,1,3,1,7,2,3,2,1,2,4,5,4,5,6,7,8,9,6,3,1,2,3,
                 1,2,3,6,7,5,6,3,4,3,4,3,4,3,4,3,4,3,4,7,7,7,2,2,1,7,6,7,8,7,8,9,7,8,2,7,8,3,5,3,
                 5,7,1,3,1,3,1,3,2,3,4,5,4,6,4,7,3,8,3,9 };

int pf_record[1][4];
int ram_frames[FRAME_END];

void FIFO();
void LRU();
void Print();
void Reset();


int main() {


    cout << endl;
    cout << "*** Virtual Memory Simulation Program" << endl;
    cout << "*** From Number changes: 3,4,5,6,7" << endl;
    cout << "*** Number of Reference are: " << NUM_REF << endl;

    FIFO();
    LRU();
    Print();

    cout << "\n\n ** End of Virtual Memory Simulation \n" << endl;




    return 0;
}

void FIFO() {

    bool f;
    int i, j, k;
    int page_fault = 0;
    int next_victim = FRAME_START;
    int found = 0;



    for (i = 3; i <= 7; ++i) {
        Reset();
        page_fault = 0;
        next_victim = 0;
        found = 0;
        for (j = 0; j < 100; ++j) {
            f = false;
            for (k = 0; k < i; ++k) {
                if (ram_frames[k] == Ref[j]) {
                    f = true;
                    ++found;
                }
            }
            if (f == false) {
                ram_frames[next_victim] = Ref[j];
                ++page_fault;
                ++next_victim;
                if (next_victim > i) {
                    next_victim = 0;
                }
            }
        }

        pf_record[0][i - 3] = page_fault;

    }
    cout << "***FIFO Results" << endl;
    for (int i = 3; i <= 7; ++i) {
        cout << "pf_record[FIFO][" << i << "](Frames)  : " << pf_record[0][i - 3] << endl;

    }




}

void LRU() {
    int pageFault = 0;
    int victim = 0;
    int count = 0;
    bool f;
    int k, j, i;
    Reset();
    vector<int> temp;
    cout << "*** LRU Results" << endl;
    for (int q = 3; q <= 7; ++q) {
        Reset();
        temp.clear();
        for (int f = 0; f < q; ++f) {
            ram_frames[f] = Ref[f];
            temp.push_back(Ref[f]);
        }
        pageFault = 0;
        for (i = 0; i < 100; ++i) {
            f = false;
            for (k = 0; k < q; ++k) {
                if (ram_frames[k] == Ref[i]) {
                    f = true;
                    break;
                }
            }
            if (!f) {
                temp.push_back(Ref[i]);
                victim = temp.at(temp.size() - q);
                count = 0;
                ++pageFault;
                for (j = 0; j < q; ++j) {
                    if (ram_frames[j] == victim && count == 0) {
                        ram_frames[j] = Ref[i];
                        ++count;
                    }
                }
            }

        }
        pf_record[1][q - 3] = pageFault;
        cout << "pf_record[LRU][" << q << "](Frames)  : " << pf_record[1][q - 3] << endl;
    }



}

void Print() {
    int min = pf_record[0][0];


    for (int i = 0; i < 5; ++i) {
        if (pf_record[0][i] < min) {
            min = pf_record[0][i];
        }
    }

    for (int i = 0; i < 5; ++i) {
        if (pf_record[1][i] < min) {
            min = pf_record[1][i];
        }
    }

    cout << "Minimum Page Fault : Algorithm FIFO with " << min << " and frame number 7 " << endl;

}
void Reset() {
    for (int i = 0; i < FRAME_END; ++i) {
        ram_frames[i] = 0;

    }



    return;
}