#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

struct tapInOut
{
    int m_cardID;
    string m_tapStation;
    int m_time;
};

class TransitTimes
{
public:
    void tapIn(const std::string &station, int cardId, int tapInTime);

    void tapOut(const std::string &station, int cardId, int tapOutTime);

    int getAverageJourneyTime(const std::string &origin, const std::string &destination);

private:
    //vector<int> m_averageJourneyTime; // n*(n-1) elements

    std::map<std::string, int> m_journeyAvgTimes; // unique start-end station string to avg journey time

    std::map<int, tapInOut> m_tapInContainer; //card id to tapIn struct
};

void TransitTimes::tapIn(const std::string &station, int cardId, int tapInTime)
{
    tapInOut l_tapInOut;
    l_tapInOut.m_cardID = cardId;
    l_tapInOut.m_tapStation = station;
    l_tapInOut.m_time = tapInTime;

    auto keyvalue = m_tapInContainer.find(cardId);
    if (keyvalue != m_tapInContainer.end())
    {

        (*keyvalue).second = l_tapInOut;
    }
    else
    {
        m_tapInContainer.insert(std::pair<>(cardId, l_tapInOut));
    }
}
void TransitTimes::tapOut(const std::string &station, int cardId, int tapOutTime)
{
    auto tapInEvent = m_tapInContainer.find(cardId);
    if (tapInEvent != m_tapInContainer.end())
    {

        const auto timeDiff = tapOutTime - (*tapInEvent).second.m_time;
        string key = (*tapInEvent).second.m_tapStation + station;

        auto journey = m_journeyAvgTimes.find(key);

        if (journey != m_journeyAvgTimes.end())
        {
            // update running avg
            auto &prevAvg = (*journey).second;
            int newAvg = (prevAvg + timeDiff) / cntr; // open

            prevAvg = newAvg;
        }
        else
        {
            m_journeyAvgTimes.insert(pair<>(key, timeDiff)); // open
        }
    }
    else
    {
        m_tapInContainer.insert(std::pair<>(cardId, l_tapInOut)); // open
    }
}

int TransitTimes::getAverageJourneyTime(const std::string &origin, const std::string &destination)
{
    string id = origin + destination;

    // check if map container contains id key
    auto journey = m_journeyAvgTimes.find(id);
    if (journey != m_journeyAvgTimes.end())
    {
        // return running average
        return (*journey).second;
    }
    else
    {
        // return some default value
        return std::numeric_limits<int>::max();
    }
}
