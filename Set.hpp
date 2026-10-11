#ifndef Set_HPP
#define Set_HPP

#include <iostream>
#include <vector>

template <typename Key, typename Compare = std::less<Key>>
class Set {
    private:

        struct Node {
            Key val;
            Color color;
            Node* left;
            Node* right;
            Node* parent;

            Node(Key val = Key()) : val{val}, left{nullptr}, right{nullptr}, parent{nullptr}, color{Color::Red} {}
        };
         
         
       class Iter {
            private:
                Node* curr;
                Set* set;
            public:
                friend class Set;
                Iter(Node* node, Set* t) : curr(node), set{t} {}

                bool operator==(const Iter& other) const { return set == other.set && curr == other.curr; }
                bool operator!=(const Iter& other) const { return !(*this == other); }

                Iter& operator++() {
                    if (curr == set->NIL) return *this;
                    if (curr->right != set->NIL) {
                        curr = curr->right;
                        while (curr->left != set->NIL) curr = curr->left;
                    } else {
                        Node* p = curr->parent;
                        while (p != set->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                Iter operator++(int) {
                    Iter tmp = *this;
                    ++(*this);
                    return tmp;
                }

                Iter& operator--() {
                    if (curr == set->NIL) {
                        curr = set->getMax(set->root);
                        return *this;
                    }

                    if (curr->left != set->NIL) {
                        curr = curr->left;
                        while (curr->right != set->NIL) curr = curr->right;
                    } else {
                        Node* p = curr->parent;
                        while (p != set->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                Iter operator--(int) {
                    Iter tmp(*this);
                    --(*this);
                    return tmp;
                }

                Key& operator*() const { return curr->val; }
                Key* operator->() const { return &(curr->val); }
        };

        class constIter {
            private:
                const Node* curr; 
                const Set* set;
            public:
                friend class Set;
                constIter(const Node* node, const Set* t) : curr(node), set{t} {}
                constIter(const constIter& other) : curr(other.curr), set{other.set} {}

                bool operator==(const constIter& other) const { return set == other.set && curr == other.curr; }
                bool operator!=(const constIter& other) const { return !(*this == other); }

               constIter& operator++() {
                    if (curr == set->NIL) return *this;
                    if (curr->right != set->NIL) {
                        curr = curr->right;
                        while (curr->left != set->NIL) curr = curr->left;
                    } else {
                        const Node* p = curr->parent;
                        while (p != set->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p;
                    }
                    return *this;
                }

                constIter operator++(int) {
                    constIter tmp(*this);
                    ++(*this);
                    return tmp;
                }

                constIter& operator--() {
                    if (curr == set->NIL) {
                        curr = set->getMax(set->root);
                        return *this;
                    }

                    if (curr->left != set->NIL) {
                        curr = curr->left;
                        while (curr->right != set->NIL) curr = curr->right;
                    } else {
                        const Node* p = curr->parent;
                        while (p != set->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                constIter operator--(int) {
                    constIter tmp(*this);
                    --(*this);
                    return tmp;
                }

                const Key& operator*() const { return curr->val; }
                const Key* operator->() const { return &(curr->val); }
        };

        class reverseIter {
            private:
                Node* curr;
                Set* set;
            public:
                friend class Set;
                reverseIter(Node* node, Set* t) : curr(node), set{t} {}

                bool operator==(const reverseIter& other) const { return set == other.set && curr == other.curr; }
                bool operator!=(const reverseIter& other) const { return !(*this == other); }

                reverseIter& operator++() {
                    if (curr == set->NIL) {
                        curr = set->getMax(set->root);
                        return *this;
                    }

                    if (curr->left != set->NIL) {
                        curr = curr->left;
                        while (curr->right != set->NIL) curr = curr->right;
                    } else {
                        Node* p = curr->parent;
                        while (p != set->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                reverseIter operator++(int) {
                    reverseIter tmp = *this;
                    ++(*this);
                    return tmp;
                }

                reverseIter& operator--() {
                    if (curr == set->NIL) return *this;
                    if (curr->right != set->NIL) {
                        curr = curr->right;
                        while (curr->left != set->NIL) curr = curr->left;
                    } else {
                        Node* p = curr->parent;
                        while (p != set->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p;
                    }
                    return *this;
                }

                reverseIter operator--(int) {
                    reverseIter tmp(*this);
                    --(*this);
                    return tmp;
                }

                Key& operator*() const { return curr->val; }
                Key* operator->() const { return &(curr->val); }
        };

        class constreverseIter {
            private:
                const Node* curr;
                const Set* set;
            public:
                friend class Set;
                constreverseIter(const Node* node, const Set* t) : curr(node), set{t} {}

                bool operator==(const constreverseIter& other) const { return set == other.set && curr == other.curr; }
                bool operator!=(const constreverseIter& other) const { return !(*this == other); }

                constreverseIter& operator++() {
                    if (curr == set->NIL) {
                        curr = set->getMax(set->root);
                        return *this;
                    }

                    if (curr->left != set->NIL) {
                        curr = curr->left;
                        while (curr->right != set->NIL) curr = curr->right;
                    } else {
                        const Node* p = curr->parent;
                        while (p != set->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                constreverseIter operator++(int) {
                    constreverseIter tmp = *this;
                    ++(*this);
                    return tmp;
                }

                constreverseIter& operator--() {
                    if (curr == set->NIL) return *this;
                    if (curr->right != set->NIL) {
                        curr = curr->right;
                        while (curr->left != set->NIL) curr = curr->left;
                    } else {
                        const Node* p = curr->parent;
                        while (p != set->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p;
                    }
                    return *this;
                }

                constreverseIter operator--(int) {
                    constreverseIter tmp(*this);
                    --(*this);
                    return tmp;
                }

                const Key& operator*() const { return curr->val; }
                const Key* operator->() const { return &(curr->val); }
        };

        Iter begin() { return Iter(getMin(root), this); }
        Iter end()   { return Iter(NIL, this); }

        constIter begin() const { return constIter(getMin(root), this); }
        constIter end()   const { return constIter(NIL, this); }

        constIter cbegin() const { return constIter(getMin(root), this); }
        constIter cend()   const { return constIter(NIL, this); }

        reverseIter rbegin() { return reverseIter(NIL, this); }
        constreverseIter rbegin() const { return crbegin(); }
        constreverseIter crbegin() const { return constreverseIter(NIL, this); }

        reverseIter rend() { return reverseIter(getMin(root), this); }
        constreverseIter rend() const { return crend(); }
        constreverseIter crend() const { return constreverseIter(getMin(root), this); }
    
        Node* root;
        Node* NIL;
        Compare comp;

        void clear (Node* node);
        void clear();
        Node* copy (Node* node, Node* newParent, Node* n);
    public:
        Set();
        template<class InputIt>
        Set(InputIt first, InputIt last, const Compare& compare = Compare());
        Set(std::initializer_list<Key> init, const Compare& compare = Compare());
        Set(const Set& other) {
            comp = other.comp;
            NIL = new Node(Key());
            NIL->left = NIL;
            NIL->right = NIL;
            NIL->parent = NIL;
            NIL->color = Color::Black; 
            root = copy(other.root, NIL, other.NIL); 
        }
        Set(Set&& other) : Set() { swap(other); }

        
        Set& operator=(const Set& other);
        Set& operator=(Set&& other);
        Set& operator=( std::initializer_list<Key> ilist );

        ~Set() { clear(root); delete NIL; }

        bool empty() const { return root == NIL; }
        size_t size() const { return size(root); }
        size_t size(Node* root) const {
            if (root == NIL) return 0;
            return 1 + size(root->left) + size(root->right);
        }

        void rotate_left(Node* x);
        void rotate_right(Node* y);

        void insert(Key k);
        void insertFixUp(Node* node);

        const Node* search(const Node* node, Key key) const;

        Node* getMin(Node* node);
        Node* getMax(Node* node);
        const Node* getMin(const Node* node) const {
            while (node != NIL && node->left != NIL) node = node->left;
            return node;
        }

        Node* getPredecessor(Node* node);
        Node* getSuccessor(Node* node);

        void transplant(Node* u, Node* v);
        void remove(Key key);
        void deleteNode(Node* z);
        void deleteFixUp(Node* x);

        void swap(Set& other) { 
            std::swap(root, other.root); 
            std::swap(NIL, other.NIL);
            std::swap(comp, other.comp);
        }

        size_t count(const Key& key) const { return contains(key); }
        bool contains(const Key& key) const { return search(root, key) != NIL; }
        
        Iter lower_bound( const Key& key );
        constIter lower_bound( const Key& key ) const;
        Iter upper_bound( const Key& key );
        constIter upper_bound( const Key& key ) const;
        std::pair<Iter, Iter> equal_range( const Key& key );
        std::pair<constIter, constIter> equal_range( const Key& key ) const;

        Node* extract(Node* z);
};

template <typename Key, typename Compare>
Set<Key, Compare>::Set() {
    NIL = new Node(Key());
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;
}

template <typename Key, typename Compare>
template<class InputIt>
Set<Key, Compare>:: Set(InputIt first, InputIt last, const Compare& compare) {
    NIL = new Node(Key());
    comp = compare;
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;

    for (auto it = first; it != last; ++it) insert(*it);
}

template <typename Key, typename Compare>
Set<Key, Compare>::Set(std::initializer_list<Key> init, const Compare& compare) {
    NIL = new Node(Key());
    comp = compare;
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;

    for (auto x : init) insert(x);
}

template <typename Key, typename Compare>
void Set<Key, Compare>::clear(Node* node) {
    if (node != NIL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Compare>
void Set<Key, Compare>::clear() {
    clear(root);
    root = NIL;
}

template <typename Key, typename Compare>
Set<Key, Compare>::Node* Set<Key, Compare>::copy (Node* node, Node* newParent, Node* n) {
    if (node == n) return NIL;

    Node* newNode = new Node(node->val);
    newNode->color = node->color;
    newNode->parent = newParent;

    newNode->left = copy(node->left, newNode, n);
    newNode->right = copy(node->right, newNode, n);
            
    return newNode;
}


template <typename Key, typename Compare>
Set<Key, Compare>& Set<Key, Compare>::operator=(const Set& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root, NIL, other.NIL);
        comp = other.comp;
    }
    return *this;
} 

template <typename Key, typename Compare>
Set<Key, Compare>& Set<Key, Compare>::operator=(Set&& other) {
    if (this != &other) {
        clear(root);
        delete NIL;

        root = other.root;
        NIL = other.NIL;
        comp = other.comp;
        
        other.NIL = new Node(Key());
        other.NIL->left = other.NIL;
        other.NIL->right = other.NIL;
        other.NIL->parent = other.NIL;
        other.NIL->color = Color::Black;
        other.root = other.NIL;
    }
    return *this;
}


template <typename Key, typename Compare>
Set<Key, Compare>& Set<Key, Compare>::operator=(std::initializer_list<Key> ilist) {
    Set tmp(ilist);
    swap(tmp);
    return *this;
}


template <typename Key, typename Compare>
void Set<Key, Compare>::rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL) y->left->parent = x;
    
    y->parent = x->parent;
    if (y->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

template <typename Key, typename Compare>
void Set<Key, Compare>::rotate_right(Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NIL) x->right->parent = y;
    
    x->parent = y->parent;
    if (x->parent == NIL) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

template <typename Key, typename Compare>
void Set<Key, Compare>::insert(Key key) {
    Node* z = new Node(key);
    z->left = NIL;
    z->right = NIL;
    z->parent = NIL;

    Node* p = NIL;
    Node* curr = root;

    while (curr != NIL) {
        p = curr;
        if (comp(key,curr->val)) curr = curr->left; 
        else if (comp(curr->val, key)) curr = curr->right;
        else return;
    }
    
    z->parent = p;
    if (p == NIL) root = z;
    else if (comp(key,p->val)) p->left = z;
    else p->right = z;

    insertFixUp(z);
}

template <typename Key, typename Compare>
void Set<Key, Compare>::insertFixUp(Node* z) {
    while (z->parent->color == Color::Red) {
        if (z->parent == z->parent->parent->right) {
            Node* y = z->parent->parent->left;
            if (y->color == Color::Red) {
                y->color = Color::Black;
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;
                z = z->parent->parent;
            } else {
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;

                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(z);
                }
                rotate_left(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->right;
            if (y->color == Color::Red) {
                y->color = Color::Black;
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;
                z = z->parent->parent;
            } else {
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;

                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(z);
                }
                rotate_right(z->parent->parent);
            }   
        }
    }
}

template <typename Key, typename Compare>
const typename Set<Key, Compare>::Node* Set<Key, Compare>::search(const Node* node, Key key) const {
    while (node != NIL && !(!comp(node->val, key) && !comp(key, node->val))) {
        if (comp(key,node->val)) node = node->left;
        else if (comp(node->val, key)) node = node->right;
    }
    return node;
}

template <typename Key, typename Compare>
typename Set<Key, Compare>::Node* Set<Key, Compare>::getMin(Node* node) {
    while (node != NIL && node->left != NIL) node = node->left;
    return node; 
}

template <typename Key, typename Compare>
typename Set<Key, Compare>::Node* Set<Key, Compare>::getMax(Node* node) {
    while (node != NIL && node->right != NIL) node = node->right;
    return node; 
}

template <typename Key, typename Compare>
typename Set<Key, Compare>::Node* Set<Key, Compare>::getPredecessor(Node* node) {
    if (node->left != NIL) return getMax(node->left);

    Node* p = node->parent;

    while (p != NIL && p->left == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename Key, typename Compare>
typename Set<Key, Compare>::Node* Set<Key, Compare>::getSuccessor(Node* node) {
    if (node->right != NIL) return getMin(node->right);

    Node* p = node->parent;

    while (p != NIL && p->right == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename Key, typename Compare>
void Set<Key, Compare>::transplant(Node* u, Node* v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
}

template <typename Key, typename Compare>
void Set<Key, Compare>::remove(Key key) {
    Node* z = search(root, key);
    if (z != NIL) deleteNode(z);
}

template <typename Key, typename Compare>
void Set<Key, Compare>::deleteNode(Node* z) {
    Node* y = z;
    Node* x = z;
    Color original = z->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = getMin(z->right);
        original = y->color;
        x = y->right;

        if (y->parent == z) x->parent = y;  
        else { 
            transplant(y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
 
        transplant(z, y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (original == Color::Black) deleteFixUp(x);
}

template <typename Key, typename Compare>
Set<Key, Compare>::Node* Set<Key, Compare>::extract(Node* z) {
    Node* y = z;
    Node* x = z;
    Color original = z->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = getMin(z->right);
        original = y->color;
        x = y->right;

        if (y->parent == z) x->parent = y;  
        else { 
            transplant(y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
 
        transplant(z, y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }

    if (original == Color::Black) deleteFixUp(x);
    return z;
}

template <typename Key, typename Compare>
void Set<Key, Compare>::deleteFixUp(Node* x) {
    while (x != root && x->color == Color::Black) {
        if (x == x->parent->left) { 
            Node* w = x->parent->right;

            if (w->color == Color::Red) {
                w->color = Color::Black;
                x->parent->color = Color::Red;
                rotate_left(x->parent);
                w = x->parent->right;
            }
            else if (w->right->color == Color::Black && w->left->color == Color::Black) {
                w->color = Color::Red;
                x = x->parent;
            }
            else {
                if (w->right->color == Color::Black) {
                    w->color = Color::Red;
                    w->left->color = Color::Black;
                    rotate_right(w);
                    w = x->parent->right;
                }
                w->color = w->parent->color;
                w->parent->color = Color::Black;
                w->right->color = Color::Black;
                rotate_left(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;

            if (w->color == Color::Red) {
                w->color = Color::Black;
                x->parent->color = Color::Red;
                rotate_right(x->parent);
                w = x->parent->left;
            }
            else if (w->right->color == Color::Black && w->left->color == Color::Black) {
                w->color = Color::Red;
                x = x->parent;
            }
            else {
                if (w->left->color == Color::Black) {
                    w->color = Color::Red;
                    w->right->color = Color::Black;
                    rotate_left(w);
                    w = x->parent->left;
                }
                w->color = w->parent->color;
                w->parent->color = Color::Black;
                w->left->color = Color::Black;
                rotate_right(x->parent);
                x = root;
            }
        }
    }
    x->color = Color::Black;
}


template <typename Key, typename Compare>
typename Set<Key, Compare>::Iter Set<Key, Compare>::lower_bound(const Key& key) {
    Node* res = NIL;
    Node* curr = root;

    while (curr != NIL) {
        if (!comp(curr->val, key)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return Iter(res, this);
}

template <typename Key, typename Compare>
typename Set<Key, Compare>::constIter Set<Key, Compare>::lower_bound(const Key& key) const {
    const Node* res = NIL;
    const Node* curr = root;

    while (curr != NIL) {
        if (!comp(curr->val, key)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return constIter(res, this);
}


template <typename Key, typename Compare>
typename Set<Key, Compare>::Iter Set<Key, Compare>::upper_bound(const Key& key) {
    Node* res = NIL;
    Node* curr = root;

    while (curr != NIL) {
        if (comp(key, curr->val)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return Iter(res, this);
}

template <typename Key, typename Compare>
typename Set<Key, Compare>::constIter Set<Key, Compare>::upper_bound(const Key& key) const {
    const Node* res = NIL;
    const Node* curr = root;

    while (curr != NIL) {
        if (comp(key, curr->val)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return constIter(res, this);
}

template <typename Key, typename Compare>
std::pair<typename Set<Key, Compare>::Iter, typename Set<Key, Compare>::Iter> Set<Key, Compare>::equal_range( const Key& key ) {
    return {lower_bound(key), upper_bound(key)};
}

template <typename Key, typename Compare>
std::pair<typename Set<Key, Compare>::constIter, typename Set<Key, Compare>::constIter> Set<Key, Compare>::equal_range( const Key& key ) const {
    return {lower_bound(key), upper_bound(key)};
}

template<class Key, class Compare>
bool operator==( const Set<Key, Compare>& lhs, const Set<Key, Compare>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    
    Compare comp;
    auto it1 = lhs.begin(); 
    auto it2 = rhs.begin();

    for(; it1 !=  lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (!(!comp(*it1, *it2) && !comp(*it2, *it1))) return false;
    } 
    return true;
}

template<class Key, class Compare>
bool operator!=( const Set<Key, Compare>& lhs, const Set<Key, Compare>& rhs) {
    return !(lhs == rhs);
}
 
template<class Key, class Compare>
bool operator<( const Set<Key, Compare>& lhs, const Set<Key, Compare>& rhs) {
    Compare comp;
    auto it1 = lhs.begin(); 
    auto it2 = rhs.begin();

    for(; it1 !=  lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (comp(*it1, *it2)) return true;
        else if (comp(*it2, *it1)) return false;
    } 

    return it1 == lhs.end() && it2 != rhs.end();
}
    
template<class Key, class Compare>
bool operator<=( const Set<Key, Compare>& lhs, const Set<Key, Compare>& rhs) {
    return !(rhs < lhs);
}
    
template<class Key, class Compare>
bool operator>( const Set<Key, Compare>& lhs, const Set<Key, Compare>& rhs) {
    return rhs < lhs;
}
    
template<class Key, class Compare>
bool operator>=( const Set<Key, Compare>& lhs, const Set<Key, Compare>& rhs) {
    return !(lhs < rhs);
}

#endif
