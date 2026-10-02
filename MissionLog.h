#ifndef MISSIONLOG_H
#define MISSIONLOG_H

#include "StandardIncludes.h"
#include <string>

struct MissionNode {
    std::string message;
    MissionNode* next;

    MissionNode(const std::string& newMessage) {
        message = newMessage;
        next = nullptr;
    }
};

class MissionLog {
private:
    MissionNode* head;
    int count;

public:
    MissionLog();
    ~MissionLog();

    // Each log owns its nodes; copying would share and double-delete them.
    MissionLog(const MissionLog&) = delete;
    MissionLog& operator=(const MissionLog&) = delete;

    void addMessage(const std::string& message);
    void clear();
    void draw(int startX, int startY) const;
};

#endif
