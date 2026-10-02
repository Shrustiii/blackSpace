#include "MissionLog.h"

MissionLog::MissionLog() {
    head = nullptr;
    count = 0;
}

MissionLog::~MissionLog() {
    clear();
}

void MissionLog::addMessage(const std::string& message) {
    MissionNode* newNode = new MissionNode(message);

    if (head == nullptr) {
        head = newNode;
    } else {
        MissionNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    count++;

    if (count > 6) {
        MissionNode* oldHead = head;
        head = head->next;
        delete oldHead;
        count--;
    }
}

void MissionLog::clear() {
    while (head != nullptr) {
        MissionNode* temp = head;
        head = head->next;
        delete temp;
    }

    count = 0;
}

void MissionLog::draw(int startX, int startY) const {
    DrawText("MISSION LOG", startX, startY, 18, SKYBLUE);

    MissionNode* temp = head;
    int line = 0;

    // Keep the latest three messages inside the HUD panel.
    for (int i = 0; i < count - 3; ++i) {
        temp = temp->next;
    }

    while (temp != nullptr) {
        DrawText(temp->message.c_str(), startX, startY + 24 + (line * 18), 15, LIGHTGRAY);
        temp = temp->next;
        line++;
    }
}
