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

void MinHeap::heapify_up(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (heap[parent] > heap[index]) {
      swap(heap[parent], heap[index]);
      index = parent;
    } else {
      break;
    }
  }
}

void MinHeap::heapify_down(int index) {
  int child = index * 2 + 1;
  while (child < heap.size()) {
    int min_child = child;
    int right_child = child + 1;
    if (right_child < heap.size() && heap[right_child] < heap[min_child]) {
      min_child = right_child;
    }
    if (heap[index] > heap[min_child]) {
      swap(heap[index], heap[min_child]);
      index = min_child;
      child = index * 2 + 1;
    } else {
      break;
    }
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
