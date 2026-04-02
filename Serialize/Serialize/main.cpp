#include "ListNode.h"

int main() 
{
    // Ñמחהאול עוסעמגûי פאיכ inlet.in
    std::ofstream out("inlet.in");
    out << "apple;2\nbanana;-1\ncarrot;1";
    out.close();

    std::cout << "--- Loading from inlet.in ---\n";
    ListNode* head = loadFromText("inlet.in");
    printList(head);

    std::cout << "\n--- Serializing to outlet.out ---\n";
    serialize(head, "outlet.out");

    std::cout << "--- Deserializing from outlet.out ---\n";
    ListNode* restoredHead = deserialize("outlet.out");
    printList(restoredHead);

    return 0;
}