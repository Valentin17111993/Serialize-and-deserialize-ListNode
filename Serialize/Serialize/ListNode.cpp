#include "ListNode.h"

ListNode* loadFromText(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) return nullptr;

    std::string line;
    std::vector<ListNode*> nodes;
    std::vector<int> randIndices;

    while (std::getline(file, line)) 
    {
        if (line.empty()) continue;

        size_t sep = line.find_last_of(';');
        if (sep == std::string::npos) continue;

        std::string data = line.substr(0, sep);
        int randIdx = std::stoi(line.substr(sep + 1));

        ListNode* node = new ListNode();
        node->data = data;

        if (!nodes.empty()) 
        {
            node->prev = nodes.back();
            nodes.back()->next = node;
        }
        nodes.push_back(node);
        randIndices.push_back(randIdx);
    }

    for (size_t i = 0; i < nodes.size(); ++i) 
    {
        if (randIndices[i] >= 0 && (size_t)randIndices[i] < nodes.size()) 
        {
            nodes[i]->rand = nodes[randIndices[i]];
        }
    }

    return nodes.empty() ? nullptr : nodes[0];
}

void serialize(ListNode* head, const std::string& filename) 
{
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return;

    std::unordered_map<ListNode*, int> nodeToIndex;
    ListNode* curr = head;
    int count = 0;

    while (curr) 
    {
        nodeToIndex[curr] = count++;
        curr = curr->next;
    }

    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

    curr = head;
    while (curr) 
    {
        size_t dataSize = curr->data.size();
        file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
        file.write(curr->data.data(), dataSize);

        int randIdx = (curr->rand) ? nodeToIndex[curr->rand] : -1;
        file.write(reinterpret_cast<const char*>(&randIdx), sizeof(randIdx));

        curr = curr->next;
    }
    file.close();
}

ListNode* deserialize(const std::string& filename) 
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) return nullptr;

    int count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (count <= 0) return nullptr;

    std::vector<ListNode*> nodes(count);
    std::vector<int> randIndices(count);

    for (int i = 0; i < count; ++i) 
    {
        nodes[i] = new ListNode();

        size_t dataSize;
        file.read(reinterpret_cast<char*>(&dataSize), sizeof(dataSize));
        nodes[i]->data.resize(dataSize);
        file.read(&nodes[i]->data[0], dataSize);

        file.read(reinterpret_cast<char*>(&randIndices[i]), sizeof(int));

        if (i > 0) 
        {
            nodes[i]->prev = nodes[i - 1];
            nodes[i - 1]->next = nodes[i];
        }
    }

    for (int i = 0; i < count; ++i) 
    {
        if (randIndices[i] != -1) 
        {
            nodes[i]->rand = nodes[randIndices[i]];
        }
    }
    return nodes[0];
}

void printList(ListNode* head) 
{
    ListNode* curr = head;
    int i = 0;
    while (curr) 
    {
        std::cout << "[" << i++ << "] Data: " << curr->data
            << " | Rand points to: " << (curr->rand ? curr->rand->data : "nullptr") << "\n";
        curr = curr->next;
    }
}