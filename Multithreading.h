#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <Multithreading.h>
#include <HK_camera.h>
#include <thread>

class MyCircularQueue {
private:
    int front{};
    int rear{};
    int capacity{};
    cv::Mat elements[20];

public:
    MyCircularQueue(int k) {
        this->capacity=k+1;
        this->front=this->rear=0;
    }
    bool push_back(int value) {
        if(isFull){
            return false;
        }
        elements[rear]=value;
        rear=(rear+1)%capacity;
        return ture;
    }
    bool deQueue() {
        if(isEmpty){
            return false;
        }
        front=(front+1)%capacity;
        return ture;
    }

     cv::Mat Front() {
        if(isEmpty){
            return elements[front].empty();
        }
        return elements[front];
    }

    int Rear() {
        if(isEmpty){
            return -1;
        }
        return elements[rear];
    }

    bool isEmpty() {
        return rear==front;
    }

    bool isFull() {
        return ((rear+1)%capacity)==front;
        //这么理解当rear=4，（rear+1）%capacity=front
    }
};

// void Creat_LoopQueue(int k){
//     vector<class MyCircularQueue> queue(k);
//
// }


void videoCaptureThread(int cameraIndex, CircularQueue<cv::Mat>& queue) {
    cv::VideoCapture cap(cameraIndex);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera " << cameraIndex << std::endl;
        return;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame; // Capture a frame
        if (frame.empty()) break;

        queue.push(frame); // Push the frame into the circular queue
    }
}





#endif //MULTITHREADING_H
