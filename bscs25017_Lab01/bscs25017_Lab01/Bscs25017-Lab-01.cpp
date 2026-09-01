#include <iostream>
#include<algorithm>
#include<vector>
#include<numeric>
using namespace std;





template <typename T>
class PerVector {
private:
    T* arr;        // dynamically allocated storage
    int cap;       // current capacity
    int len;       // number of elements currently stored

    void reallocate(int newCap)   // grow the underlying array
    {
		T* temp = new T[newCap];
		for (int i = 0; i < len; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		cap = newCap;
    }

public:
    PerVector() {
		arr = new T[1];
		cap = 1;
		len = 0;
    }
    PerVector(const PerVector<T>& other):cap(other.cap), len(other.len)  // deep copy
    {
		this->arr = new T[other.cap];
		for (int i = 0; i < other.len; i++) {
			this->arr[i] = other.arr[i];
		}
    }
    ~PerVector() {
		delete[] arr;
    }

    void push_back(const T& val) {
		if (len == cap) {
			reallocate(cap * 2);
		}
		arr[len] = val;
		len++;
    }
    void pop_back() {
		if (len - 1 > 0) {
			len--;
		}
    }
    T& operator[](int index) {
		return arr[index];
    }
    int size() const {
		return len;
    }
    int capacity() const {
		return cap;
    }
    bool empty() const {
		return len == 0;
    }

    // ---- Iterator support ----
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p = nullptr) {
            ptr = p;
        }

        T& operator*() const {
            return *ptr;
        }

        Iterator& operator++()      // prefix ++it
        {
            this->ptr++;
            return *this;
        }

        Iterator operator++(int)     // postfix it++
        {
            Iterator temp = *this;
            this->ptr++;
            return temp;
        }

        Iterator& operator--()       // prefix --it
        {
            this->ptr--;
            return *this;
        }

        Iterator operator+(int n) const {
            return Iterator(ptr + n);
        }
        Iterator operator-(int n) const {
            return Iterator(ptr - n);
        }
        int operator-(const Iterator& other) const   // distance between two iterators
        {
            int temp = this->ptr - other.ptr;
            if (temp < 0) {
                -temp;
            }
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return this->ptr == other.ptr;
        }
        bool operator!=(const Iterator& other) const {
            return  this->ptr != other.ptr;
        }
        bool operator<(const Iterator& other) const {
            int temp = this->ptr - other.ptr;
            if (temp < 0) {
                return false;
            }
            return true;
        }
    };
    Iterator begin() {
        return Iterator(arr);
    }
    Iterator end() {
        return Iterator(arr+len);
    }
};

int main2() {
    PerVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    cout << "Forward Traversal using Iterator: ";
    for (PerVector<int>::Iterator it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Testing pointer arithmetic operators
    PerVector<int>::Iterator imt = vec.begin();
    PerVector<int>::Iterator offsetIt = imt + 2;
    cout << "Element at index 2 (via iterator addition): " << *offsetIt << endl;
    cout << "Distance (end - begin): " << (vec.end() - vec.begin()) << endl;

    return 0;
}

int main() {
    vector<int> vec = { 10,10,20,30,30,30,20 };
    cout << "Given Vector: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    int num = 0;
    //Task 1
    cout << "\n\nTask 1\n";
    cout << "Enter Element To Check In Given Array: ";
    cin >> num;
    auto it = find(vec.begin(), vec.end(), num);
    if (it == vec.end()) {
        cout << "Element does not exist\n";
    }
    else {
        cout << "Element exists\n"; 
    }
    //Task 2
    cout << "\n\nTask 2\n";
    sort(vec.begin(), vec.end());
    cout << "Sorted Vector: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }

    //Task 3
    cout << "\n\nTask 3\n";
    auto min = min_element(vec.begin(), vec.end());
    cout << "Minimum value: " << *min << endl;
    auto max = max_element(vec.begin(), vec.end());
    cout << "Maximum value: " << *max << endl;


    // Task 4
    cout << "\n\nTask 4\n";
    int sum = accumulate(vec.begin(), vec.end(),0);
    cout << "Sum: " << sum << endl;
    float avg = sum / vec.size();
    cout << "Average: " << avg << endl;

    // Task 5
    cout << "\n\nTask 5\n";
    cout << "Enter Element To Count In Given Array: ";
    cin >> num;
    int ct = count(vec.begin(), vec.end(), num);
    cout << "Count of " << num << " : " << ct << endl;

    //Task 6
    cout << "\n\nTask 6\n";
    reverse(vec.begin(), vec.end());
    cout << "Reversed Vector: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }

    // Task 7
    cout << "\n\nTask 7\n";
    sort(vec.begin(), vec.end());
    cout << "Enter Element To Check In Given Array Using Binary Search: ";
    cin >> num;
    bool imt = binary_search(vec.begin(), vec.end(), num);
    if (!imt) {
        cout << "Element does not exist\n";
    }
    else {
        cout << "Element exists at position "<<*it<<endl;
    }



}

