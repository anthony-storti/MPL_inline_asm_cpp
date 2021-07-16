/*
Main includes two bubble sort functions one written in pure C++ and one in x86 assembly and an additional function that returns time since epoch
to help time the algorithms, the program times the speed of asm and C++ bubble sorting after filling arrays of size 1000,5000,10000,and 30000
with random ints read from a file. One arrays are sorted in prompts for user input, validates input as an int and searches for input in the largest array
processor: x86
*/
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void bubblesort_cpp(int a[], int len);
void bubblesort_asm(int* input, int num);
void fillArray(int arr[], int s);


int main(void)
{
    // initialize and fill array with 1000 ints from file
    int input = 1000;
    int  arr_asm_one[1000];
    fillArray(arr_asm_one, 1000);
    int  arr_cpp_one[1000];
    fillArray(arr_cpp_one, 1000);
    // call both sorting algorithms and time them. Output times to console 
    auto start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_asm(arr_asm_one, input - 1);
    auto end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "Assembly sorting 1,000 integers takes " << end_time - start_time << "ms" << endl;
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_cpp(arr_cpp_one, input);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "C++ sorting 1,000 integers takes " << end_time - start_time << "ms" << endl;;
    // initialize and fill array with 5000 ints from file
    input = 5000;
    int  arr_asm_five[5000];
    fillArray(arr_asm_five, 5000);
    int  arr_cpp_five[5000];
    fillArray(arr_cpp_five, 5000);
    // call both sorting algorithms and time them. Output times to console 
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_asm(arr_asm_five, input - 1);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "Assembly sorting 5,000 integers takes " << end_time - start_time << "ms" << endl;
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_cpp(arr_cpp_five, input);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "C++ sorting 5,000 integers takes " << end_time - start_time << "ms" << endl;;
    // initialize and fill array with 10000 ints from file
    input = 10000;
    int  arr_asm_ten[10000];
    fillArray(arr_asm_ten, 10000);
    int  arr_cpp_ten[10000];
    fillArray(arr_cpp_ten, 10000);
    // call both sorting algorithms and time them. Output times to console 
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_asm(arr_asm_ten, input - 1);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "Assembly sorting 10,000 integers takes " << end_time - start_time << "ms" << endl;
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_cpp(arr_cpp_ten, input);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "C++ sorting 10,000 integers takes " << end_time - start_time << "ms" << endl;
    // initialize and fill array with 30000 ints from file
    input = 30000;
    int  arr_asm_thirty[30000];
    fillArray(arr_asm_thirty, 30000);
    int  arr_cpp_thirty[30000];
    fillArray(arr_cpp_thirty, 30000);
    // call both sorting algorithms and time them. Output times to console 
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_asm(arr_asm_thirty, input - 1);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "Assembly sorting 30,000 integers takes " << end_time - start_time << "ms" << endl;
    start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    bubblesort_cpp(arr_cpp_thirty, input);
    end_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "C++ sorting 30,000 integers takes " << end_time - start_time << "ms" << endl;
    //prompt user for input and validate input as integer type
    cout << "enter an Integer to Search for" << endl;
    int choice = 0;
    string junk;
    while (!(cin >> choice)) {
        cout << "enter a valid Integer:";
        cin.clear();
        getline(cin, junk);
    }
    //initialize variables to escape bool and index count
    bool cont = true;
    int x = 0;
    //continue searching for user input value until either the returned index value is greater than user input value or you have reached the end of the 
    //array or the user input value is found in the array. In the last case output to console user input has been found and what index it was found at.
    while (cont) {
        if (x >= input || arr_asm_one[x] > choice) {
            cont = false;
            cout << "Number not Found" << endl;
        }
        if (arr_asm_one[x] == choice) {
            cout << "List contains " << choice << " at index " << x - 1 << endl;
            cont = false;
        }
        ++x;
    }
    return 0;
}
/*
bubblesort_asm
requires: requires a pointer to an array of integers and the size of array elements passed as an integer
modifies: the passed array of integers with starting memory location
actions: sorts the passed array of integers in ascending order in place using inline assembly for x86 processors
*/

void bubblesort_asm(int* input, int num) {
    __asm {

        push 0                                      // push 0 to stack
        mov ecx, 0                                  // put zero in ecx register 
        mov esi, input                              // put memory address of input[0] in esi register
        jmp l2                                      // jump to inner loop
        l1 :                                        // outer loop call
        push ecx                                    // push ecx to stack
            mov ecx, 0                              // set loop counter to 0
            l2 :                                    // inner loop call
            mov edx, dword ptr[esi + 4 * ecx]       // put first comparator of array in edx register
            mov eax, dword ptr[esi + 4 + 4 * ecx]   // put second comparator of array in eax register
            cmp eax, edx                            // compare eax register to edx register
            jg l4                                   // if eax is greater than edx jump to l4 ie. if elements are already in order
            push edx                                // otherwise push second element to stack
            pop dword ptr[esi + 4 + 4 * ecx]        // pop second element to memory location of first element            
            push eax                                // push first element to stack
            pop dword ptr[esi + 4 * ecx]            // pop first element to second elements location in memory
            l4 :                                    // l4 jumped to if elements are already in order 
        inc ecx                                 // increment counter 
            cmp ecx, num                            // compare inner loop counter to size of array
            jne l2                                  // if not equal jump back to do another inner loop
            pop ecx                                 // pop outer loop counter
            inc ecx                                 // increment outter loop counter
            cmp ecx, num                            // compare outter loop counter to size of array
            jne l1                                  // if not equal jump to l1 and execute outer loop
            jmp done                                // if equal jump to done to exit asm code this could probably be eliminated
            done :                                  // exit asm code this could probably be eliminated with the last steps but it makes it clear
                                                    // where the end of the code is
    }
}
/*
bubblesort_cpp
requires: array of intergers and the length of the array as an integer
modifies: the passed array of integers
actions: sorts the passed array of integers in ascending order in place
*/
void bubblesort_cpp(int a[], int len) {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            if (a[j] < a[i]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
/*
fillArray
requires: array of intergers and the length of the array as an integer
modifies: the passed array of integers
actions: fills the array with values from random_numbers.txt file starting at first line and ending at passed array size line of file
*/
void fillArray(int arr[], int s) {
    int line;
    int cnt = 0;
    ifstream inFile("random_numbers.txt");
    while (cnt < s && inFile >> line) {
        arr[cnt] = line;
        cnt++;
    }

}

