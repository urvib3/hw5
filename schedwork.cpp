#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstring>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelp(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    const size_t totalWorkers, 
    int* shifts,            // number of shifts each worker is working so far
    int cDay, int cPos      // current position in schedule
);

// Checks if inserting a certain worker into a certain position is isValid
// 1) Worker must be available
// 2) Worker must not already be scheduled for the same day 
// 3) Worker must be under max shifts 
bool isValid(const AvailabilityMatrix& avail,
    const size_t maxShifts,
    int* shifts,            // number of shifts each worker is working so far
    int cDay,     // current position in schedule
    int cWorkerID           // worker to check
);



// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }

    sched.clear();
    // Add your code below

    int k = avail[0].size(); // total # of workers
    int* shifts = new int[k]; 
    for(int i = 0; i < k; i++) shifts[i] = 0; 

    // initialize sched
    sched = std::vector<std::vector<Worker_T>>(avail.size(), std::vector<Worker_T>(dailyNeed, -1));

    bool ans = schedHelp(avail, dailyNeed, maxShifts, sched, k, shifts, 0, 0); 
    
    delete [] shifts; 

    return ans; 

}


bool schedHelp(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    const size_t totalWorkers, 
    int* shifts,            // number of shifts each worker is working so far
    int cDay, int cPos      // current position in schedule
) {

  // std::cout << "cDay: " << cDay << " cPos: " << cPos << std::endl; 
  // std::cout << "printing sched " << sched.size() << std::endl; 
  // for(std::vector<Worker_T> v : sched) { for (Worker_T w : v) std:: cout << w << " "; std::cout << std::endl; }

  // BASE CASE: cDay and cPos out of bounds of schedule array
  if(cDay >= sched.size()) return true; 

  // Try every possible worker for current day and current position in schedule
  // To avoid repeat combinations, all workers for a day will be tried in ascending order
  for(int cWorkerID = (cPos > 0) ? sched[cDay][cPos - 1] + 1 : 0; cWorkerID < totalWorkers; cWorkerID++) {
    
    // only update data and recurse if current worker is a possibility
    if(isValid(avail, maxShifts, shifts, cDay, cWorkerID)) {

      // update shifts array and schedule
      shifts[cWorkerID]++; 
      sched[cDay][cPos] = cWorkerID; 

      // recurse and return true if recursion leads to a solution
      if(schedHelp(avail, dailyNeed, maxShifts, sched, totalWorkers, shifts, 
      (cPos + 1 == dailyNeed) ? cDay + 1 : cDay, 
      (cPos + 1 == dailyNeed) ? 0 : cPos + 1)) return true; 

      // backtrack 
      shifts[cWorkerID]--; 
      sched[cDay][cPos] = -1; // optional reset
    }
  }

  return false; 
}


bool isValid(const AvailabilityMatrix& avail,
    const size_t maxShifts, 
    int* shifts,            // number of shifts each worker is working so far
    int cDay,               // current position in schedule
    int cWorkerID           // worker to check
) {

  // 1) Worker must be available
  // 2) Worker must be under max shifts 

  if(!avail[cDay][cWorkerID] || 
      shifts[cWorkerID] == maxShifts) return false; 

  return true; 

}







