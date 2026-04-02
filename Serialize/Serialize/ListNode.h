#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

// Структура по условию задачи
struct ListNode 
{
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* rand = nullptr;
    std::string data;
};

ListNode* loadFromText(const std::string& filename); // Построение списка из текстового описания (inlet.in)
void serialize(ListNode* head, const std::string& filename); // Сериализация в бинарный файл (outlet.out)
ListNode* deserialize(const std::string& filename); // Десериализация из бинарного файла
void printList(ListNode* head); // Вспомогательная функция для вывода списка