//
// Created by QingZhiLiangCheng on 2025/4/26.
//
#include <deque>
#include<list>
#include<cstdio>
#include <iostream>
#include<cmath>
#include <memory>

class PCB {
public:
    int pid_;
    int arrival_time_;
    int run_time_;
    int used_cpu_time_{0};
    int status_{0}; // 0-waiting, 1-running, 2-completed

    PCB(int pid, int arrival_time, int run_time) : pid_(pid), arrival_time_(arrival_time), run_time_(run_time) {}
};

class RR {
public:
    RR(int rr) : rr_(rr) {};

    void AddProcess(int pid, int arrival_time, int run_time) {
        PCB *p_PCB = new PCB(pid, arrival_time, run_time);
        pcbs_.push_back(p_PCB);
    }

    void RunScheduler() {
        pcbs_.sort([](const PCB *a, const PCB *b) {
            return a->arrival_time_ < b->arrival_time_;
        });
        pcb_deque_.push_back(pcbs_.front());
        current_time_ = pcbs_.front()->arrival_time_;
        pcbs_.pop_front();
        while (!pcbs_.empty() || !pcb_deque_.empty()) {
            PCB *current_pcb = pcb_deque_.front();
            pcb_deque_.pop_front();
            current_pcb->used_cpu_time_ += std::min(rr_, current_pcb->run_time_ -
                                                         current_pcb->used_cpu_time_);
            current_time_ += std::min(rr_, current_pcb->run_time_ -
                                           current_pcb->used_cpu_time_);

            while (!pcbs_.empty() && pcbs_.front()->arrival_time_ <= current_time_) {
                pcb_deque_.push_back(pcbs_.front());
                pcbs_.pop_front();
            }


            Display(current_pcb);


            if(current_pcb->used_cpu_time_ < current_pcb->run_time_) {
                pcb_deque_.push_back(current_pcb);
            }
        }
    }


    void Display(PCB* current) {
        std::cout << "当前时间为: " << current_time_ << " 时各进程的信息:\n";

        for (const auto &pcb : pcb_deque_) {
            std::cout << "PID: " << pcb->pid_
                      << ", Used CPU Time: " << pcb->used_cpu_time_
                      << ", Remaining Time: " << pcb->run_time_ - pcb->used_cpu_time_ << "\n";
        }
        std::cout << "---------------------------------------------\n";
    }

private:
    std::list<PCB *> pcbs_;
    std::deque<PCB *> pcb_deque_; // 进程队列
    int current_time_{0};
    int rr_;
};


int main() {
    RR scheduler(2);
    scheduler.AddProcess(1, 0, 8);
    scheduler.AddProcess(2, 1, 4);
    scheduler.AddProcess(3, 2, 9);
    scheduler.AddProcess(4, 3, 5);
    scheduler.RunScheduler();
}
