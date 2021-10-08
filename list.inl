

template <class T>
Node<T>::Node (Node<T>* const& next, const_reference value)
{
    this->next  = next;
    this->value = value;
}

template <class T>
Node<T>::Node (const Node<T>& other)
{ copy (other); }

template <class T>
Node<T>::Node (Node<T>&& other)
{ move (std::move(other)); }

template <class T>
Node<T>::~Node ()
{

}

template <class T>
Node<T>& Node<T>::operator= (const Node<T>& other)
{
    copy   (other);
    return *this;
}

template <class T>
Node<T>& Node<T>::operator= (Node<T>&& other)
{
    move   (std::move (other));
    return *this;
}

template <class T>
void Node<T>::copy (const Node<T>& other)
{
    this->next  = other.next;
    this->value = other.value;
}

template <class T>
void Node<T>::copy (Node<T>&& other)
{ move (std::move (other)); }

template <class T>
void Node<T>::move (Node<T>&& other)
{
    this->next  = std::move (other.next);
    this->value = std::move (other.value);
}

template <class T>
void Node<T>::setValue (const_reference value)
{ this->value = value; }

template <class T>
void Node<T>::setNext (Node<T>* const& next)
{ this->next = next; }

template <class T>
T Node<T>::getValue () const
{ return value; }

template <class T>
Node<T>* Node<T>::getNext () const
{ return next; }

template <class T>
void Node<T>::swap (Node<T>& other)
{
    Node<T>* tmpnext    = std::move(other.next);
    value_type tmpvalue = std::move(other.value);
    other.next          = std::move(this->next);
    other.value         = std::move(this->value);
    this->next          = std::move(tmpnext);
    this->value         = std::move(tmpvalue);
}

template <class T>
void swap (Node<T>& a, Node<T>& b)
{ a.swap(b); }

template <class T>
Iterator<T>::Iterator (node* const& current)
{ this->current = current; }

template <class T>
Iterator<T>::Iterator (const Iterator<T>& other)
{ copy(other); }

template <class T>
Iterator<T>::Iterator (Iterator<T>&& other)
{ move (std::move (other)); }

template <class T>
Iterator<T>& Iterator<T>::operator= (const Iterator<T>& other)
{
    copy   (other);
    return *this;
}

template <class T>
Iterator<T>& Iterator<T>::operator= (Iterator<T>&& other)
{
    move   (std::move (other));
    return *this;
}

template <class T>
const Iterator<T>& Iterator<T>::operator= (const Iterator<T>& other) const
{
    copy   (other);
    return *this;
}

template <class T>
const Iterator<T>& Iterator<T>::operator= (Iterator<T>&& other) const
{
    move   (std::move(other));
    return *this;
}

template <class T>
void Iterator<T>::copy (const Iterator<T>& other) const
{ this->current = other.current; }

template <class T>
void Iterator<T>::copy (Iterator<T>&& other) const
{ move (std::move (other)); }

template <class T>
void Iterator<T>::move (Iterator<T>&& other) const
{ this->current = std::move (other.current); }

template <class T>
Iterator<T>& Iterator<T>::operator++ ()
{
    this->current = this->current->getNext();
    return *this;
}

template <class T>
const Iterator<T>& Iterator<T>::operator++ () const
{
    this->current = this->current->getNext();
    return *this;
}

template <class T>
T& Iterator<T>::operator* ()
{ return this->current->value; }

template <class T>
const T& Iterator<T>::operator* () const
{ return this->current->value; }

template <class T>
void Iterator<T>::swap (Iterator<T>& other)
{
    node* tmp     = std::move(other.current);
    other.current = std::move(this->current);
    this->current = std::move(tmp);
}

template <class T>
bool Iterator<T>::operator== (const Iterator<T>& other) const
{ return (this->current == other.current); }

template <class T>
bool Iterator<T>::operator!= (const Iterator<T> & other) const
{ return (this->current != other.current); }

template <class U>
uint32_t distance (const Iterator<U> a, const Iterator<U> b)
{
    uint32_t res = 0;
    for (auto it = a; it != b; ++res, ++it)
        ;
    return res;
}

template <class T>
List<T>::List ()
{   nullnode.head = nullnode.tail = (node*)(void*)&nullnode; }

template <class T>
List<T>::List (const List<T>& other) : List ()
{ copy (other); }

template <class T>
List<T>::List (List<T>&& other) : List ()
{ move (std::move (other)); }

template <class T>
List<T>::List(std::initializer_list<value_type> _l): List ()
{
    for (auto it = _l.begin (); it != _l.end (); ++it) {
        push_end (*it);
    }
}

template <class T>
List<T>::~List ()
{ clear(); }

template <class T>
List<T>& List<T>::operator= (const List<T>& other)
{
    clear  ();
    copy   (other);
    return *this;
}

template <class T>
List<T>& List<T>::operator= (List<T>&& other)
{
    clear  ();
    move   (std::move (other));
    return *this;
}

template <class T>
List<T>& List<T>::operator= (std::initializer_list<int32_t> _l)
{
    clear ();
    for (auto it = _l.begin (); it != _l.end (); ++it) {
        push_end (*it);
    }
    return *this;
}

template <class T>
void List<T>::copy (const List<T>& other)
{
    clear ();
    auto tmp = this->cend ();
    for (auto i = other.nullnode.head; i != (node*)(void*)&other.nullnode.head;
              i = i->next) {

         tmp = this->insert_after (tmp, i->value);
    }
}

template <class T>
void List<T>::copy (List<T>&& other)
{ move (std::move (other)); }

template <class T>
void List<T>::move (List&& other)
{
    this->nullnode.head = other.nullnode.head;
    this->nullnode.tail = other.nullnode.tail;
    other.nullnode.head = other.nullnode.tail = (node*)(void*)&nullnode;
}

template <class T>
void List<T>::push_begin (const_reference value)
{
    nullnode.head = new node (nullnode.head, value);
    if (nullnode.head->next == (node*)(void*)&nullnode) {
        nullnode.tail = nullnode.head;
    }
}

template <class T>
void List<T>::push_end (const_reference value)
{
    nullnode.tail->next = new node ((node*)(void*)&nullnode, value);
    nullnode.tail       = nullnode.tail->next;

    if (nullnode.head == (node*)(void*)&nullnode) {
        nullnode.head = nullnode.tail;
    }
}

template <class T>
T List<T>::pop_begin ()
{
    value_type res;
    if (empty ()) throw Exception::LIST_IS_EMPY;

    node* tmp     = nullnode.head;
    res           = tmp->value;
    nullnode.head = tmp->next;

    if (nullnode.tail == tmp) {
        nullnode.tail = nullnode.head;
    }

    delete tmp;
    return res;
}

template <class T>
T List<T>::front () const
{
    if (empty ()) throw Exception::LIST_IS_EMPY;
    return nullnode.head->value;
}

template <class T>
T List<T>::back () const
{
    if (empty()) throw Exception::LIST_IS_EMPY;
    return nullnode.tail->value;
}

template <class T>
Iterator<T> List<T>::begin ()
{ return iterator (nullnode.head); }

template <class T>
const Iterator<T> List<T>::cbegin () const
{ return const_iterator (nullnode.head); }

template <class T>
Iterator<T> List<T>::end ()
{ return iterator ((node*)(void*)&nullnode); }

template <class T>
const Iterator<T> List<T>::cend () const
{ return const_iterator ((node*)(void*)&nullnode); }

template<class T>
Iterator<T> List<T>::before_begin ()
{ return iterator ((node*)(void*)&nullnode); }

template <class T>
const Iterator<T> List<T>::cbefore_begin () const
{ return const_iterator ((node*)(void*)&nullnode); }

template <class T>
Iterator<T> List<T>::insert_after (const_iterator position,
                                   const_reference value)
{
    position.current->next = new node (position.current->next, value);
    if (position.current == nullnode.tail)
        nullnode.tail = position.current->next;

    return iterator(position.current->next);
}

template <class T>
Iterator<T> List<T>::insert_after (const_iterator position,
                                   pointer const & begin,
                                   pointer const & end)
{
    iterator tmp = position;
    for (auto i = begin; i <= end; ++i) {
        tmp = insert_after(tmp, *i);
    }
    return tmp;
}

template <class T>
void List<T>::erase_after (const_iterator begin, const_iterator end)
{
    if (end.current == nullnode.tail) {
        nullnode.tail = begin.current;
    }
    auto tmp = iterator (begin.current->next);
    begin.current->next = end.current->next;
    for (auto it = tmp; it != iterator (end.current->next);){
        tmp = it;
        ++it;
        delete tmp.current;
    }
}

template <class T>
void List<T>::erase_after (const_iterator begin)
{
    auto tmp = begin.current->next;
    if (tmp == nullnode.tail) {
        nullnode.tail = begin.current;
    }
    begin.current->next = tmp->next;
    delete tmp;
}

template <class T>
bool List<T>::remove (const_reference value)
{ return remove_if ([value](const_reference lst) { return value == lst; }); }

template <class T>
void List<T>::swap (List<T>& other)
{
    node* tmp_tail      = std::move (other.nullnode.tail);
    node* tmp_head      = std::move (other.nullnode.head);
    other.nullnode.tail = std::move (this->nullnode.tail);
    other.nullnode.head = std::move (this->nullnode.head);
    this->nullnode.tail = std::move (tmp_tail);
    this->nullnode.head = std::move (tmp_head);
}

template <class T>
void List<T>::clear ()
{
    for (node* i = nullnode.head; i != (node*)(void*)&nullnode;) {
        node* tmp = i;
        i         = i->next;
        delete tmp;
    }
    nullnode.head = nullnode.tail = (node*)(void*)&nullnode;
}

template <class T>
uint32_t List<T>::getSize () const
{ return distance(cbegin (), cend ()); }

template <class T>
bool List<T>::empty () const
{ return (nullnode.head == (node*)(void*)&nullnode); }

template <class T>
void List<T>::merge(List<T>& other)
{
    merge (other, [](const_reference a, const_reference b) { return a < b; } );
}

template <class T>
uint32_t List<T>::getMinRun(uint32_t n)
{
    uint32_t r = false;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <class U>
std::ostream& operator<< (std::ostream& out, const List<U>& lst)
{
    bool stream_state = out.sync_with_stdio(false);
    out << '[' << ' ';
    for (auto it = lst.cbegin(); it != lst.cend(); ++it){
        out << *it << ' ';
    }
    out << ']';
    out.sync_with_stdio(stream_state);
    return out;
}

template <class U>
std::istream& operator>> (std::istream& in, List<U>& lst)
{
    std::string line;
    std::getline           (in, line);
    std::istringstream iss (line);
    U x;
    while ((iss >> x))
        lst.push_end(x);
    return in;
}

template <class T>
void List<T>::reverse ()
{
    auto current                    = const_iterator (nullnode.head->next);

    while (current.current->next != (node*)(void*)&nullnode) {
        auto tmp                    = current.current->next->next;
        current.current->next->next = nullnode.head->next;
        nullnode.head               = current.current->next;
        current.current->next       = tmp;
    }
    nullnode.tail                   = current.current;
}

template <class T>
void List<T>::splice_after (const_iterator position, List<T>& other)
{ splice_after(position, other,
               other.cbefore_begin(), (const_iterator)(other.nullnode.tail)); }

template <class T>
void List<T>::splice_after (const_iterator position, List<T>&& other)
{ splice_after(position, other,
               other.cbefore_begin(), (const_iterator)(other.nullnode.tail)); }

template <class T>
void List<T>::splice_after (const_iterator position, List<T>&       other,
                            const_iterator start,    const_iterator finish)
{
    auto next               = std::move (position.current->next);
    position.current->next  = std::move (start.current->next);
    start.current->next     = std::move (finish.current->next);
    finish.current->next    = std::move (next);

    if (other.nullnode.tail == finish.current) {
        other.nullnode.tail = start.current;
    }
    if (this->nullnode.tail == position.current) {
        this->nullnode.tail = finish.current;
    }

}

template <class T>
void List<T>::sort ()
{
    sort([](const_reference a, const_reference b)
    { return a < b; } );
}

template <class T>
template <class UnaryPredicat>
bool List<T>::remove_if (UnaryPredicat p)
{
    bool res = false;
    for (auto it = cbefore_begin(); it.current != nullnode.tail;){

        if (p(it.current->next->value)) {
            erase_after(it);
            res = true;
        } else { ++it; }
    }
    return res;
}

template <class T>
template <class UnaryPredicat>
Iterator<T> List<T>::find (UnaryPredicat p)
{ return find_after(p, cbefore_begin()); }

template <class T>
template <class UnaryPredicat>
const Iterator<T> List<T>::find (UnaryPredicat p) const
{ return find_after(p, cbefore_begin()); }

template <class T>
template <class UnaryPredicat>
Iterator<T> List<T>::find_after (UnaryPredicat p, const_iterator begin)
{
    ++begin;
    for (iterator it = begin; it.current != (node*)(void*)&nullnode; ++it) {
        if (p(*it)) return it;
    }
    return before_begin();
}

template <class T>
template <class UnaryPredicat>
const Iterator<T> List<T>::find_after (UnaryPredicat p, 
                                       const_iterator begin) const
{
    ++begin;
    for (const_iterator it = begin; 
	     it.current != (node*)(void*)&nullnode; ++it){
        if (p(*it)) return it;
    }
    return cbefore_begin();
}

template <class T>
template <class BinaryPredicat>
void List<T>::sort (BinaryPredicat p)
{
    uint32_t size = this->getSize ();
    __sort__ (p, *this, size);
}

template <class T>
template<class BinaryPredicar>
void List<T>::merge (List<T>& other, BinaryPredicar p)
{
    enum class State { searching, checkingEnd, searchingEnd, adding };
    const_iterator end;
    auto position = this->cbefore_begin();
    auto current  = other.cbegin();
    State state   = State::searching;
    while (current.current != (node*)(void*)&other.nullnode) {

        switch (state) {

        case State::searching:
            if (position.current == this->nullnode.tail) {
                end   = other.nullnode.tail;
                state = State::adding;

            } else if (p (*current, position.current->next->value)) {
                end   = current;
                state = State::checkingEnd;
            } else {
                ++position;
            }
            break;

        case State::checkingEnd:
            if (p (other.nullnode.tail->value, 
			       position.current->next->value)) {
                end   = other.nullnode.tail;
                state = State::adding;
            } else {
                state = State::searchingEnd;
            }
            break;

        case State::searchingEnd:
            if (p (end.current->next->value, position.current->next->value)) {
                ++end;
            } else {
                state = State::adding;
            }
            break;

        case State::adding:
        {
            auto tmp               = const_iterator (end.current->next);
            end.current->next      = position.current->next;
            position.current->next = current.current;
            if (position.current == this->nullnode.tail) {
                nullnode.tail      = end.current;
            }
            current                = tmp;
            position               = const_iterator (end.current);
            state                  = State::searching;
            break;
        }
        default:
            throw "I DON'T NOW WAT's GOING ON";
        }
    }
    other.nullnode.head = other.nullnode.tail =
            (node*)(void*)&other.nullnode;
}

template <class T>
template <class BinaryPredicat>
void List<T>::__sort__ (BinaryPredicat p, List<T>& lst, const uint32_t & size)
{
    if (size > 1) {
        List<T> firstHalfLst, secondHalfLst;
        auto firstHalfEnd = lst.cbefore_begin ();
        uint32_t halfSize = size / 2;

        for (uint32_t i = 0; i < halfSize; ++i) {
            ++firstHalfEnd;
        }

        firstHalfLst.splice_after (firstHalfLst.cbefore_begin (), lst,
                                 lst.cbefore_begin (), firstHalfEnd);
        secondHalfLst.splice_after (secondHalfLst.cbefore_begin(), lst);

        __sort__ (p, firstHalfLst, halfSize);
        __sort__ (p, secondHalfLst, size - halfSize);

        lst.merge (firstHalfLst, p);
        lst.merge (secondHalfLst, p);
    }
}

template <class T>
void swap (List<T> a, List<T> b)
{ a.swap(b); }
