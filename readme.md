# Bloomberg Live Coding Challenge

## Given Problem (C++ 14)

Paraphrased from memory...
A subway/metro system has a priori unknown set of unique stations.
An example might look like:
    
    o 55th Penguin Street
    |
    |
    o 57th Penguin Street
    |
    |
    o Central Park
    

Travellers tap in with a card at the respective start station, and tap out at the destination station with a card. Each tap in/out creates an event and calls the given public api functions ```tapIn``` and ```tapOut```.
The function ```getAverageJourneyTime``` shall, based on historical tap in and out events of travellers, return the all-time average journey duration for a unique start/end station combination.

The following class definition of the public api interface is given, it shall be implemented accordingly:

```cpp
class TransitTimes
{
public:
    void tapIn(const std::string &station, int cardId, int tapInTime);

    void tapOut(const std::string &station, int cardId, int tapOutTime);

    int getAverageJourneyTime(const std::string &origin, const std::string 
        &destination);
};
```

## Live Solution and Questions
No compilation, therefore small syntax errors were allowed. 
The prototypical live implementation took about 50 mins, followed by questions regarding time & space complexity of each of the 3 functions and general optimizations.

### Time & Space complexity?
Each ``std::map`` search and insertion in the live solution has a ``log(n)`` time complexity. My guess for space complexity of each ``std::map`` container was ``n``. 

### Possible Optimizations?
 - At tapout event remove the entry with same key from ``m_tapInContainer`` to avoid forever storing user tapIn events.
 - Use ``std::unordered_map`` instead, as the default sorting after keys in ``std::map`` is not necessary and adds to time complexity
 - Make use of ``operator[]`` to access/insert an element in ``std::map``  




    




