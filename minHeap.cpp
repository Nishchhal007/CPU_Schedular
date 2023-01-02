#include <iostream>
#include <vector>

using namespace std;

class MinHeap {
  public:
    MinHeap(int capacity);
    void push(int key);
    void pop();
    int top();
    bool empty();
    int size();

  private:
    vector<int> heap;
    void heapify_up(int index);
    void heapify_down(int index);
};

MinHeap::MinHeap(int capacity) {
  heap.reserve(capacity);
}

void MinHeap::push(int key) {
  heap.push_back(key);
  heapify_up(heap.size() - 1);
}

void MinHeap::pop() {
  swap(heap[0], heap[heap.size() - 1]);
  heap.pop_back();
  heapify_down(0);
}

int MinHeap::top() {
  return heap[0];
}

bool MinHeap::empty() {
  return heap.empty();
}

int MinHeap::size() {
  return heap.size();
}

void min_heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < arr->size() && arr->at(l).arr_time < arr->at(smallest).arr_time)
        {
            smallest = l;
        }
        else
        {
            smallest = i;
        }

        if (r < arr->size() && arr->at(r).arr_time < arr->at(smallest).arr_time)
        {
            smallest = r;
        }

        if (smallest != i)
        {
            swap(arr->at(smallest), arr->at(i));
            min_heapify(smallest);
        }
    }

int main() {
  MinHeap heap(10);
  heap.push(10);
  heap.push(5);
  heap.push(3);
  heap.push(7);
  heap.push(1);
  heap.push(8);

  while (!heap.empty()) {
    cout << heap.top() << " ";
    heap.pop();
  }

  return 0;
}
