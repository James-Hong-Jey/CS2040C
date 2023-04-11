#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 1; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? processing_time < c.processing_time : arrival_time < c.arrival_time; 
	// a customer is "greater" if his time is shorter
	// i.e. faster
};


void customerQueueTest(int n_cust) {
	int current_time = 0;
	int totalWaitingTime = 0;
	int i;
	int WT; // waiting time for each customer

	Heap<Customer> queue;

	Customer* custList = new Customer[n_cust];
	cout << endl << endl << "Setup" << endl;
	cout << "List of customers and their arrival and processing times" << endl;
	for (i = 0; i<n_cust; i++)
	{
		custList[i].setAT(i);
		custList[i].setPT((n_cust - i) % (n_cust / 2) + 1 + (i % 2)*(n_cust / 2));
		cout << "Customer " << i << " will arrive at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
	}
	cout << endl;

	for (int round = 0; round<2; round++) {
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = round;
		current_time = 0; 
		totalWaitingTime = 0;
		WT = 0;
		i = 0;
		Customer c; // AT & PT == 0

		while (i < n_cust || !queue.empty()) {
			if(c.PT() != 0 && c.PT() == WT) { // when he FINISHES being processed
				WT = 0;
				if(queue.empty()) {
					c.setAT(0);
					c.setPT(0);
				} else {
					c = queue.extractMax();
				}
			}

			if(i < n_cust){ // if there are still guys at home, move them into the queue
				queue.insert(custList[i]);
				cout << "Customer arrives at time " << current_time << " with PT=" << custList[i].PT() << endl;
			}

			if(c.PT() == 0) { // no one being processed rn
				cout << "Customer arrives when no one is waiting" << endl;
				c = queue.extractMax();
				cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() 
				<< " after waiting for " << current_time - c.AT() << " min." << endl; // this means he STARTS being processed
				totalWaitingTime += current_time - c.AT(); 
			} else if (WT == 0) {
				cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() 
				<< " after waiting for " << current_time - c.AT() << " min." << endl; // this means he STARTS being processed
				totalWaitingTime += current_time - c.AT(); 
			}
			
			i++;
			WT++;
			current_time++;
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;
	}
	delete[] custList;
}
