#include "Card.hpp"
#include <iostream>

// unused file
// this was my implementation of a linked list for a players hand (before finding out about vectors)
// decided to use vectors instead
class CardList {

  class ListNode {
    public:
      Card item;
      ListNode* next;

      ListNode(Card card) {
        this->item = card;
      }
  };

  public:
    ListNode *head = nullptr;
    ListNode *tail = nullptr;

    void add(Card* card) {
      ListNode *newCard = new ListNode(*card);
      newCard->next = head;
      head = newCard;
    }

    void remove(int value) {
      ListNode* traverse = head;
      ListNode* prev = nullptr;

      // deleting at head case
      if ((head->item).value == value && head != nullptr) {
        ListNode*temp = head;
        head = head->next;
        // destroy temp
        delete temp;
      } 
      
      else {
        bool flag = true;
        while (traverse != nullptr && flag) {
          if ((traverse->item).value == value) {
            prev->next = traverse->next;
            ListNode * temp = traverse;
            delete temp;
            flag = false;
          } else {
            prev = traverse;
            traverse = traverse->next;
          }
        }
      }
    }

    void printList() {
      ListNode* traverse = head;
      while (traverse != nullptr) {
        cout << (traverse->item).value << endl;
        traverse = traverse->next;
      }
    }
};