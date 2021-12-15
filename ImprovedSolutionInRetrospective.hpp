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

struct tapInOutData
{
    int m_cardID;
    std::string m_tapStation;
    int m_time;

    tapInOutData(int cardID, string tapStation, int time) : m_cardID(cardID), m_tapStation(tapStation), m_time(time) {}
};

struct avgJourneyTimeData
{
    int m_avgTime;
    int m_cntr;

    avgJourneyTimeData(int avgTime, int cntr) : m_avgTime(avgTime), m_cntr(cntr) {}
};

class TransitTimes
{
public:
    void tapIn(const std::string &station, int cardId, int tapInTime);

    void tapOut(const std::string &station, int cardId, int tapOutTime);

    int getAverageJourneyTime(const std::string &origin, const std::string &destination);

private:
    std::unordered_map<std::string, avgJourneyTimeData> m_avgJourneyTimeContainer; // unique start-end station string to avg journey time

    std::unordered_map<int, tapInOutData> m_tapInContainer; //card id to tapIn data struct
};

void TransitTimes::tapIn(const std::string &station, int cardId, int tapInTime)
{
    tapInOutData tapInData(cardId, station, tapInTime);

    // add or update value
    m_tapInContainer[cardId] = tapInData;
}

void TransitTimes::tapOut(const std::string &station, int cardId, int tapOutTime)
{
    auto tapInData = m_tapInContainer.find(cardId);
    if (tapInData != m_tapInContainer.end())
    {
        const int timeDiff = tapOutTime - tapInData->second.m_time;
        string key = tapInData->second.m_tapStation + station;

        auto journey = m_avgJourneyTimeContainer.find(key);
        if (journey != m_avgJourneyTimeContainer.end())
        {
            // update running avg
            auto &prevAvg = journey->second.m_avgTime;
            int newAvg = (prevAvg + timeDiff) / (++journey->second.m_cntr);
            prevAvg = newAvg;
        }
        else
        {
            avgJourneyTimeData avgTimeData(timeDiff, 1);
            m_avgJourneyTimeContainer.insert(std::make_pair(key, avgTimeData));
        }
    }
    else
    {
        // do nothing
    }
}

int TransitTimes::getAverageJourneyTime(const std::string &origin, const std::string &destination)
{
    string key = origin + destination;

    // check if map container contains id key
    auto journey = m_avgJourneyTimeContainer.find(key);
    if (journey != m_avgJourneyTimeContainer.end())
    {
        // return running average
        return journey->second.m_avgTime;
    }
    else
    {
        // return default value
        return std::numeric_limits<int>::min();
    }
}
