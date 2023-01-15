#include <iostream>
#include <memory>   // shared_ptr<T>

template <typename Elem>
class List
{
public:
    void foo(Elem value) {
        auto u = std::make_shared<Node>(value, nullptr);
        std::cout << u->value << std::endl;
        head = u;
    }

    Elem first() const { return head->value; }

private:
    struct Node
    {
        Elem                  value;
        std::shared_ptr<Node> next;
    };

    std::shared_ptr<Node> head;
};