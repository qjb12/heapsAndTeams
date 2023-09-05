#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
PriorityQueue::PriorityQueue(std::size_t max_size) :
    nodes_(max_size + 1, KeyValuePair()),
    max_size_(max_size),
    size_(0) {
}
void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}
void PriorityQueue::insert(KeyValuePair kv) {
// TODO: complete this function
    ++this->size_;
    int last = this->size_;
    this->nodes_[last] = kv;
    this->heapifyUp(last);
}
KeyValuePair PriorityQueue::min() {
// TODO: complete this function
    return this->nodes_[1];
}
KeyValuePair PriorityQueue::removeMin() {
// TODO: complete this function
    int size = this->size_;
    KeyValuePair last = this->nodes_[size];
    KeyValuePair min = this->nodes_[1];
    this->nodes_[1] = last;
    this->nodes_[size] = min;
    --this->size_;
    this->heapifyDown(1);
    return min;
}
bool PriorityQueue::isEmpty() const {
// TODO: complete this function
    if(this->size_ != 0){   
        return false;
    } else {
        return true;
    }
}
size_t PriorityQueue::size() const {
// TODO: complete this function
    return this->size_;
}
nlohmann::json PriorityQueue::JSON() const {
nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
      nlohmann::json node;
      KeyValuePair kv = nodes_[i];
      node["key"] = kv.first;
      node["value"] = kv.second;
      if (i != ROOT) {
          node["parent"] = std::to_string(i / 2);
      }
      if (2 * i <= size_) {
          node["leftChild"] = std::to_string(2 * i);
      }
      if (2 * i + 1 <= size_) {
          node["rightChild"] = std::to_string(2 * i + 1);
      }
      result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
    result["metadata"]["maxHeapSize"] = max_size_; 
  result["metadata"]["size"] = size_;
return result;
}
void PriorityQueue::heapifyUp(size_t i) {
// TODO: complete this function
    int val = i;
    while(val/2 > 0){
        double curr = this->nodes_[val].first;            
        double parent = this->nodes_[val/2].first;
        if(parent > curr){
            KeyValuePair temp = this->nodes_[val];
            this->nodes_[val] = this->nodes_[val/2];
            this->nodes_[val/2] = temp;
            val = val/2;
        } else {
            val = 0;
        }
    }
}
void PriorityQueue::heapifyDown(size_t i) {
// TODO: complete this function
    int val = i;
    int size = this->size_;
    while((val * 2) <= size){
            double curr = this->nodes_[val].first;
            double right = this->nodes_[(val*2) + 1].first;
            double left = this->nodes_[val*2].first;
            if(curr > right && curr > left && (val*2) + 1 <= size){
                if(right < left){
                    //replace to right
                    KeyValuePair temp = this->nodes_[val];
                    this->nodes_[val] = this->nodes_[(val*2) + 1];
                    this->nodes_[(val*2) + 1] = temp;
                    val = (val*2) + 1;
                } else {
                    KeyValuePair temp = this->nodes_[val];
                    this->nodes_[val] = this->nodes_[(val*2)];
                    this->nodes_[(val*2)] = temp;
                    val = (val*2);
                }
            } else if(curr > right && (val*2) + 1 <= size){
                KeyValuePair temp = this->nodes_[val];
                this->nodes_[val] = this->nodes_[(val*2) + 1];
                this->nodes_[(val*2) + 1] = temp;
                val = (val*2) + 1;
            } else if(curr > left){
                KeyValuePair temp = this->nodes_[val];
                this->nodes_[val] = this->nodes_[(val*2)];
                this->nodes_[(val*2)] = temp;
                val = (val*2);
            } else {
                val = size + 1;
            }
        }
}
void PriorityQueue::removeNode(size_t i) {
// TODO: complete this function
    int size = this->size_;
    KeyValuePair last = this->nodes_[size];
    this->nodes_[i] = last;
    this->heapifyDown(i);
    --this->size_;
}
Key PriorityQueue::getKey(size_t i) {
// TODO: complete this function
    return this->nodes_[i].first;
}