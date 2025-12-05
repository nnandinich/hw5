#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t slot,
    vector<size_t>& workerCurrShift
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
    sched.resize(avail.size());
    for(size_t i=0; i<avail.size(); i++){
      sched[i].resize(dailyNeed, INVALID_ID);
    }
    vector<size_t> workerCurrShift(avail[0].size(), 0);
    bool result= scheduleHelper(avail, dailyNeed, maxShifts, sched, 0, 0, workerCurrShift);
    return result;
}

bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day,
    size_t slot,
    vector<size_t>& workerCurrShift
    )
 {   
  //number of days
  size_t n=avail.size();
  size_t totalWorkers=avail[0].size();
  //if all days scheduled
  if(day==n){
    return true;
  }
  //if day slots are filled, go to next day
  if(slot==dailyNeed){
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, day+1, 0, workerCurrShift);
  }
  //find workers for slot
  for(size_t i=0; i<totalWorkers; i++ ){
    //need to make sure worker isnt scheduled on this day
    if(find(sched[day].begin(), sched[day].end(), i)==sched[day].end()){
      //current worker is avaiable on this day and see if over max shifts
      if(avail[day][i] && workerCurrShift[i]<maxShifts){
        //assign worker to shift
        sched[day][slot]=i;
        workerCurrShift[i]++;
        //move to next spot
        if(scheduleHelper(avail, dailyNeed, maxShifts, sched, day, slot+1, workerCurrShift)){
          return true;
        } 
        //if it doesnt work, go back
        sched[day][slot]=INVALID_ID;
        workerCurrShift[i]-=1;
        }
      }
    }
    //no worker can work for this slot
      return false;
 }
