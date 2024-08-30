#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

template <typename T>
class MyCircularQueue {
private:
    int front;
    int rear;
    int capacity;
    std::vector<T> elements;
    std::mutex mtx;
    std::condition_variable cv;

public:
    MyCircularQueue(int k) : front(0), rear(0), capacity(k+1), elements(k+1) {}

    bool push_back(const T& value) {
        std::unique_lock<std::mutex> lock(mtx);
        if (isFull()) {
            return false;
        }
        elements[rear] = value;
        rear = (rear + 1) % capacity;
        cv.notify_all();
        return true;
    }

    bool deQueue() {
        std::unique_lock<std::mutex> lock(mtx);
        if (isEmpty()) {
            return false;
        }
        front = (front + 1) % capacity;
        cv.notify_all();
        return true;
    }

    T Front() {
        std::unique_lock<std::mutex> lock(mtx);
        if (isEmpty()) {
            return T();
        }
        return elements[front];
    }

    T Rear() {
        std::unique_lock<std::mutex> lock(mtx);
        if (isEmpty()) {
            return T();
        }
        return elements[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {
        std::unique_lock<std::mutex> lock(mtx);
        return rear == front;
    }

    bool isFull() {
        std::unique_lock<std::mutex> lock(mtx);
        return ((rear + 1) % capacity) == front;
    }
};

void videoCaptureThread(int cameraIndex, MyCircularQueue<cv::Mat>& queue) {
    cv::VideoCapture cap(cameraIndex);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera " << cameraIndex << std::endl;
        return;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;  // Capture a frame
        if (frame.empty()) break;

        if (!queue.push_back(frame)) {
            std::cerr << "Warning: Queue is full. Dropping frame." << std::endl;
        }
    }
}

#endif // MULTITHREADING_H