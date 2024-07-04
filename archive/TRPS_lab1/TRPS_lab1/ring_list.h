#pragma once
#include <string>

struct Node {
	std::string text;
	Node* next = nullptr;

	Node(std::string str): text(str) {}
};

class Ring_list {
	Node* list = nullptr;
	Node* head = nullptr;
public:
	void add(std::string str) {
		if (!head) {
			Node* node = new Node(str);
			head = list = node;
			list->next = node;
		}
		else {
			Node* node = new Node(str);
			list->next = node;
			node->next = head;
			list = list->next;
		}
	}

	bool find(std::string str) {
		Node* temp = head;
		do {
			if (temp->text == str)
				return true;
			temp = temp->next;
		} while (temp != head);
		return false;
	}

	void erase(std::string str) {
		Node* curr = head, * prev = head;
		if (curr->text == str) {
			list->next = head = curr->next;
			delete curr;
			std::cout << "����������� ������� �������" << std::endl << std::endl;
			return;
		}
		curr = curr->next;
		while (curr != head) {
			if (curr->text == str) {
				prev->next = curr->next;
				delete curr;
				std::cout << "����������� ������� �������" << std::endl << std::endl;
				return;
			}
			curr = curr->next;
			prev = prev->next;
		}
		std::cout << "����������� �� �������" << std::endl << std::endl;
	}

	void sort() {
		if (head == nullptr || head->next == head) {
			return;
		}

		Node* sorted = nullptr; // ������ ���������������� ������

		Node* current = head;
		do {
			Node* nextNode = current->next;
			if (sorted == nullptr || sorted->text >= current->text) {
				// ��������� � ������ ���������������� ������
				current->next = sorted == nullptr ? current : sorted;
				sorted = current;
			}
			else {
				// ���� ���������� ������� � ��������������� ������
				Node* search = sorted;
				while (search->next != sorted && search->next->text < current->text) {
					search = search->next;
				}
				current->next = search->next;
				search->next = current;
			}

			current = nextNode;
		} while (current != head);

		head = sorted;
	}

	void print() {
		Node* temp = head;
		std::cout << std::endl;
		do {
			std::cout << temp->text<<std::endl;
			temp = temp->next;
		} while (temp!=head);
	}
};
