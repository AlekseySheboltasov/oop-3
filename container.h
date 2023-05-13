#pragma once
#include <iostream>


template <typename T>
class Container {
private:
    struct Node {
        Node* next;
        Node* prev;
        T data;

    public:
        Node(Node* n = nullptr, Node* p = nullptr) : next(n), prev(p) {}

        Node(T const &d, Node* n = nullptr, Node* p = nullptr) :data(d), next(n), prev(p) {}
    };

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* _current) : current(_current) {}

        bool operator!=(Iterator other) {
            return current != other.current;
        }

        Iterator operator++() {
            current = current->next;
            return *this;
        }

        Iterator operator--() {
            current = current->prev;
            return *this;
        }

        T value() {
            return current->data;
        }
    };

    Node* tech;
    unsigned int len;

public:
    Container() : len(0) {}

    int size() {
        return len;
    }

    bool is_empty() {
        return len == 0;
    }

    void push_front(T const &data) {
        if (len == 0) {
            tech = new Node();
            tech->next = tech;
            tech->prev = tech;
        }
        Node* tmp = new Node(data, tech->next, tech);
        tech->next = tmp;
        tech->next = tmp;
        len++;
    }

    void push_back(T const &data) {
        if (len == 0) {
            tech = new Node();
            tech->next = tech;
            tech->prev = tech;
        }
        Node* tmp = new Node(data, tech, tech->prev);
        tech->prev->next = tmp;
        tech->prev = tmp;
        len++;
    }

    void pop_front() {
        if (!is_empty()) {
            Node* tmp = tech->next->next;
            delete tech->next;
            tech->next = tmp;
            tmp->prev = tech;
            len--;
            if (len == 0) {
                delete tech;
            }
        }
    }

    void pop_back() {
        if (!is_empty()) {
            Node* tmp = tech->prev->prev;
            delete tech->prev;
            tech->prev = tmp;
            tmp->next = tech;
            len--;
            if (len == 0) {
                delete tech;
            }
        }
    }

    void clear() {
        while (len > 0) {
            pop_front();
        }
    }

    void swap_containers(Container<T> &second) {
        std::swap(this->tech, second->tech);
        std::swap(this->len, second->len);
    }

    Iterator begin() {
        return Iterator(tech->next);
    }

    Iterator end() {

        return tech;
    }

    void reverse() {
        Node* i = tech->get_next();
        Node* j = tech->get_prev();
        T tmp;
        while (i != j && i != j->get_prev()) {
            tmp = i->get();
            i->set(j->get());
            j->set(tmp);
            i = i->get_next();
            j = j->get_prev();
        }
    }

    ~Container() {
        clear();
    }
};
