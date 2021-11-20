template<typename E>
class List {
private:
    void operator=(const List&) {} // Protect assingment
    List(const List&) {}            // Protect copy constructor
public:
    List() {}           // Default constructor
    virtual ~List() {} // Base destructor

    // Clear contents from the list, to make it empty.
    virtual void clear() = 0;

    // Insert an element at the current location.
    // item: The element to be inserted
    virtual void insert(const E& item) = 0;

    // Append an element at the end of the list.
    // item: The element to be appended.
    virtual void append(const E& item) = 0;

    // Remove and return the current element.
    // Return: the element that was removed.
    virtual E remove() = 0;

    // Set the current position to the start of the list
    virtual void moveToStart() = 0;

    // Set the current position to the end of the list
    virtual void moveToEnd() = 0;

    // Move the current position one step left. No change if already at beginning.
    virtual void prev() = 0;

    // Move the current position one step right. No change if already at end.
    virtual void next() = 0;

    // Return: The number of elements in the list.
    virtual int length() const = 0;

    // Return: The position of the current element.
    virtual int currPos() const = 0;

    // Set current position.
    // pos: The position to make current.
    virtual void moveToPos(int pos) = 0;

    //Return: The current element.
    virtual const E& getValue() const = 0;
};


// Singly linked list node
template<typename E>
class Link {
public:
    E element;    // Value for this node
    Link* next; // Pointer to next node in list
    // Constructors
    Link(const E& elemval, Link* nextval = NULL) {
        element = elemval;
        next = nextval;
    }

    Link(Link* nextval = NULL) {
        next = nextval;
    }
};

// Linked list implementation
template<typename E>
class LList : public List<E> {
private:
    Link<E>* head; // Pointer to list header
    Link<E>* tail; // Pointer to last element
    Link<E>* curr; // Access to current element
    int cnt;       // Size of list

    // Initialization helper method
    void init() {
        curr = tail = head = new Link<E>;
        cnt = 0;
    }

    // Return link nodes to free store
    void removeall() {
        while (head != NULL) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

public:
    // Constructor
    LList(int size = 0) { init(); }

    // Destructor
    ~LList() { removeall(); }

    // Print list contents
    void print() const;

    // Clear lilst
    void clear() {
        removeall();
        init();
    }

    // Insert "it" at current position
    void insert(const E& it) {
        curr->next = new Link<E>(it, curr->next);
        if (tail == curr)
            tail = curr->next; // New tail
        cnt++;
    }

    // Append "it" to list
    void append(const E& it) {
        tail = tail->next = new Link<E>(it, NULL);
        cnt++;
    }

    // Remove and return current element
    E remove() {
        //_assert((curr->next == NULL), "No element");
        E it = curr->next->element;     // Remember value
        Link<E>* ltemp = curr->next; // Remember link node
        if (tail == curr->next)
            tail = curr;               // Reset tail
        curr->next = curr->next->next; // Remove from list
        delete ltemp;                   // Reclaim space
        cnt--;                           // Decrement the count
        return it;
    }

    // Place curr at list start
    void moveToStart() {
        curr = head;
    }

    // Place curr at list end
    void moveToEnd() {
        curr = tail;
    }

    // Move curr one step right; no change if already at end
    void next() {
        if (curr != tail)
            curr = curr->next;
    }

    // Return length
    int length() const { return cnt; }

    // Return the position of the current element
    int currPos(int pos) {
        Link<E>* temp = head;
        int i;
        for (i = 0; curr != temp; i++) temp = temp->next;
        return i;
    }

    // Move down list to "pos" position
    void moveToPos(int pos) {
        //        _assert((pos >= 0 && pos <= cnt), "Position out of range");
        curr = head;
        for (int i = 0; i < pos; i++)
            curr = curr->next;
    }

    // Return current element
    E& getValue() const {
        //        _assert((curr->next == NULL), "No value");
        return curr->next->element;
    }
};