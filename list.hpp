#ifndef LIST_H
#define LIST_H
#include    <stdint.h>
#include    <utility>
#include    <ostream>
#include    <istream>
#include    <string>
#include    <sstream>
#include    <initializer_list>

template <class T>
class Iterator;

template <class T>
class List;

template <class T>
class Node
{
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;

public:
    Node             (Node* const& next = nullptr,
                      const_reference value = 0);

    Node             (const Node& other);

    Node             (Node&& other);

    ~Node            ();
    Node & operator= (const Node& other);
    Node & operator= (Node&& other);
    void copy        (const Node& other);
    void copy        (Node&& other);
    void move        (Node&& other);
    void setValue    (const_reference value);
    void setNext     (Node* const& next);
    value_type getValue () const;
    Node * getNext   () const;
    void swap        (Node& other);
private:
    friend class Iterator<T>;
    friend class List<T>;
    mutable Node * next;
    value_type value;
};


template <class T>
class Iterator
{
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using node            = Node<T>;

public:
    Iterator                    (node* const& current = nullptr);

    Iterator                    (const Iterator& other);

    Iterator                    (Iterator&& other);

    Iterator & operator=        (const Iterator& other);

    Iterator & operator=        (Iterator&& other);

    const Iterator & operator=  (const Iterator& other) const;

    const Iterator & operator=  (Iterator&& other) const;

    void copy                   (const Iterator& other) const;

    void copy                   (Iterator&& other) const;

    void move                   (Iterator&& other) const;

    Iterator & operator++       ();
    const Iterator & operator++ () const;
    reference operator*         ();
    const_reference operator*   () const;

    void swap                   (Iterator & other);

    bool operator==             (const Iterator & other) const;

    bool operator!=             (const Iterator & other) const;
private:
    friend class List<T>;
    template <class U>
    friend uint32_t distance    (const Iterator<U> a, const Iterator<U> b);
    mutable node* current;
};

template <class T>
class List
{
public:
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using node            = Node<T>;
    using iterator        = Iterator<T>;
    using const_iterator  = const Iterator<T>;

    enum Exception                   { LIST_IS_EMPY };

    List                             ();

    List                             (const List& other);

    List                             (List&& other);

    List                             (std::initializer_list<T> _l);

    ~List                            ();

    List & operator=                 (const List& other);

    List & operator=                 (List&& other);

    List & operator=                 (std::initializer_list<int32_t> _l);

    void copy                        (const List& other);

    void copy                        (List&& other);

    void move                        (List&& other);

    void push_begin                  (const_reference value);

    void push_end                    (const_reference value);

    value_type pop_begin             ();

    value_type front                 () const;

    value_type back                  () const;

    iterator begin                   ();

    const_iterator cbegin            () const;

    iterator end                     ();

    const_iterator cend              () const;

    iterator before_begin            ();

    const_iterator cbefore_begin     () const;

    iterator insert_after            (const_iterator position,
                                      const_reference value);

    iterator insert_after            (const_iterator position,
                                      pointer const& begin,
                                      pointer const& end);

    void erase_after                 (const_iterator begin,
                                      const_iterator end);

    void erase_after                 (const_iterator begin);

    bool remove                      (const_reference value);

    template                         <class UnaryPredicat>
    bool remove_if                   (UnaryPredicat p);

    template                         <class UnaryPredicat>
    iterator find                    (UnaryPredicat p);

    template                         <class UnaryPredicat>
    const_iterator find              (UnaryPredicat p) const;

    template                         <class UnaryPredicat>
    iterator find_after              (UnaryPredicat p, const_iterator begin);

    template                         <class UnaryPredicat>
    const_iterator find_after        (UnaryPredicat p,
                                      const_iterator begin) const;

    void sort                        ();

    template                         <class BinaryPredicat>
    void sort                        (BinaryPredicat p);

    void merge                       (List& other);

    template                         <class BinaryPredicat>
    void merge                       (List& other, BinaryPredicat p);

    void swap                        (List& other);

    void clear                       ();

    uint32_t getSize                 () const;

    bool empty                       () const;

    void reverse                     ();

    void splice_after                (const_iterator position, List& other);

    void splice_after                (const_iterator position, List&& other);

    void splice_after                (const_iterator position,
                                      List& other,
                                      const_iterator start,
                                      const_iterator finish);

private:
    template                         <class BinaryPredicat>
    void __sort__                    (BinaryPredicat p, List<T>& lst,
                                      const uint32_t& size);

    uint32_t getMinRun               (uint32_t N);

    template <class U>
    friend std::ostream & operator<< (std::ostream& out, const List<U>& lst);

    template <class U>
    friend std::istream & operator>> (std::istream& in,  List<U>& lst);

    template <class U>
    friend void swap                 (List<U>& a, List<U>& b);


    struct __NULL_NODE__ {
               node* head;
               node* tail;
    };

    __NULL_NODE__ nullnode;
};


#include    "list.inl"

#endif // LIST_H
