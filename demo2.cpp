#define QUEUE_LEN 20

typedef struct {
    std::vector<LivoxDataFormat> queue[QUEUE_LEN];
    int tail = 0;
} RingQueue;

RingQueue RING_QUEUE;

void ringQueuePush(std::vector<LivoxDataFormat> cloud) {
    int index = RING_QUEUE.tail % QUEUE_LEN;
    RING_QUEUE.queue[index].swap(cloud);
    ++RING_QUEUE.tail;
    if (RING_QUEUE.tail != 0 && RING_QUEUE.tail % QUEUE_LEN == 0) {
        RING_QUEUE.tail = 0;
    }
}

void ringQueuePop(std::vector<LivoxDataFormat> &dst) {
    int index = (RING_QUEUE.tail - camera_delay_lidar_n_frame + QUEUE_LEN) % QUEUE_LEN;
    std::cout << "ringQueuePop index : " << index << ", tail: " << RING_QUEUE.tail << ", size: "<< RING_QUEUE.queue[index].size() << std::endl;
    dst.swap(RING_QUEUE.queue[index]);
    RING_QUEUE.queue[index].clear();
    RING_QUEUE.queue[index].shrink_to_fit();
}
