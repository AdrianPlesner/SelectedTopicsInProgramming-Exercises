#include <iostream>
#include <chrono>
#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <cstdint>
using namespace std;
using namespace std::chrono;


void swap_ends(int arr[], int size) {
    for (int i = size/2 - 1, j = size - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}


void swap_ends(vector<int>& arr) { // overloading the same fn-name
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_buff(int arr[], int size){
    int buffer_size {size/2};
    int position {buffer_size};
    if (size % 2 == 1){
        position += 1;
    }
    int buff[buffer_size];
    memcpy(buff, arr, buffer_size * sizeof(int));
    memcpy(arr, arr+position, buffer_size * sizeof(int));
    memcpy(arr+position, buff, buffer_size * sizeof(int));
}

void swap_dynamic(int arr[], int size) {
    int buffer_size {size/2};
    int position {buffer_size};
    if (size % 2 == 1){
        position += 1;
    }
    int* buff = new int[buffer_size];
    memcpy(buff, arr, buffer_size * sizeof(int));
    memcpy(arr, arr+position, buffer_size * sizeof(int));
    memcpy(arr+position, buff, buffer_size * sizeof(int));
}

constexpr int arr_size = 10'000'000;

// This is fine
vector<int> vec(arr_size);
int c_arr[arr_size];
void do_work(bool has_vec){
    swap_ends(c_arr, sizeof(c_arr)/sizeof(int));
    if(has_vec)
        swap_ends(vec);
}


//This is also fine
void do_more_work(bool has_vec){
    if(has_vec){
        vector<int> vec(arr_size);
        swap_ends(vec);
    }
    swap_ends(c_arr, sizeof(c_arr)/sizeof(int));
}


//However, this is stack overflow

void too_much_work(bool has_vec){
    if(has_vec){
        vector<int> vec(arr_size);
        swap_ends(vec);
    }
    int c_arr[arr_size];
    swap_ends(c_arr, sizeof(c_arr)/sizeof(int));

}

void do_buffer_work(){
    swap_buff(c_arr, sizeof(c_arr)/sizeof(int));
}

void do_dynamic_buffer_work(){
    swap_dynamic(c_arr, sizeof(c_arr)/sizeof(int));
}


void exercise1_2(){
    // do some warm up work here
    auto t0 = high_resolution_clock::now();

    auto t1 = high_resolution_clock::now();

    t0 = high_resolution_clock::now();
    //do_work(false);
    t1 = high_resolution_clock::now();
    cout << duration<double, milli>(t1-t0).count() << "ms\n";

    t0 = high_resolution_clock::now();
    //do_more_work(false);
    t1 = high_resolution_clock::now();
    cout << duration<double, milli>(t1-t0).count() << "ms\n";

    /*t0 = high_resolution_clock::now();
    do_buffer_work();
    t1 = high_resolution_clock::now();
    cout << duration<double, milli>(t1-t0).count() << "ms\n";*/

    t0 = high_resolution_clock::now();
    do_dynamic_buffer_work();
    t1 = high_resolution_clock::now();
    cout << duration<double, milli>(t1-t0).count() << "ms\n";

    /*t0 = high_resolution_clock::now();
    too_much_work();
    t1 = high_resolution_clock::now();
    cout << duration<double, milli>(t1-t0).count() << "ms\n";*/
}


int* cpy_srt(int arr[], int size){
    int* result = new int[size];
    memcpy(result, arr, size * sizeof(int));
    sort(result, result+size);
    return result;
}

int* cpy_srt(vector<int> vec){
    int* result = new int[vec.size()];
    auto data = vec.data();
    memcpy(result, data, vec.size() * sizeof(int));
    sort(result, result+vec.size());
    return result;
}

void exercise1_3(){
    int arr[] {6,3,5,89,8,5,3,4};
    int size {sizeof(arr) / sizeof(arr[0])};

    auto sorted = cpy_srt(arr, size);

    for(auto i = 0; i < size; i++ ){
        cout << sorted[i] << " ";
    }
    cout << endl;

    vector vec {8,4,56,7,4,3,5,7,9,3};
    auto sorted_vec = cpy_srt(vec);
    for(auto i = 0; i < vec.size(); i++ ){
        cout << sorted_vec[i] << " ";
    }
    cout << endl;
}

int main(){
    exercise1_3();

    return 0;
}

