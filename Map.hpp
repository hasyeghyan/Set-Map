#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

template <typename Key, typename T, typename Compare = std::less<Key>>
class Map {
    public:
        using value_type = std::pair<const Key, T>; 
    private:        
        class value_compare {
            private:
                Compare comp;

            public:
                value_compare(Compare comp) : comp{comp} {}
                bool operator()(const value_type& l, const value_type& r) {
                    return comp(l.first, r.first);
                }
        };

        enum Color{Black, Red};

        struct Node {
            value_type val;
            Color color;
            Node* left;
            Node* right;
            Node* parent;

            Node(value_type val = value_type()) : val{val}, left{nullptr}, right{nullptr}, parent{nullptr}, color{Color::Red} {}
        };
         
         
       class Iter {
            private:
                Node* curr;
                Map* map;
            public:
                friend class Map;
                Iter(Node* node, Map* t) : curr(node), map{t} {}

                bool operator==(const Iter& other) const { return map == other.map && curr == other.curr; }
                bool operator!=(const Iter& other) const { return !(*this == other); }

                Iter& operator++() {
                    if (curr == map->NIL) return *this;
                    if (curr->right != map->NIL) {
                        curr = curr->right;
                        while (curr->left != map->NIL) curr = curr->left;
                    } else {
                        Node* p = curr->parent;
                        while (p != map->NIL && curr == p->right) {
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
                    if (curr == map->NIL) {
                        curr = map->getMax(map->root);
                        return *this;
                    }

                    if (curr->left != map->NIL) {
                        curr = curr->left;
                        while (curr->right != map->NIL) curr = curr->right;
                    } else {
                        Node* p = curr->parent;
                        while (p != map->NIL && curr == p->left) {
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

                value_type& operator*() const { return curr->val; }
                value_type* operator->() const { return &(curr->val); }
        };

        class constIter {
            private:
                const Node* curr; 
                const Map* map;
            public:
                friend class Map;
                constIter(const Node* node, const Map* t) : curr(node), map{t} {}
                constIter(const constIter& other) : curr(other.curr), map{other.map} {}

                bool operator==(const constIter& other) const { return map == other.map && curr == other.curr; }
                bool operator!=(const constIter& other) const { return !(*this == other); }

               constIter& operator++() {
                    if (curr == map->NIL) return *this;
                    if (curr->right != map->NIL) {
                        curr = curr->right;
                        while (curr->left != map->NIL) curr = curr->left;
                    } else {
                        const Node* p = curr->parent;
                        while (p != map->NIL && curr == p->right) {
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
                    if (curr == map->NIL) {
                        curr = map->getMax(map->root);
                        return *this;
                    }

                    if (curr->left != map->NIL) {
                        curr = curr->left;
                        while (curr->right != map->NIL) curr = curr->right;
                    } else {
                        const Node* p = curr->parent;
                        while (p != map->NIL && curr == p->left) {
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

                const value_type& operator*() const { return curr->val; }
                const value_type* operator->() const { return &(curr->val); }
        };

        class reverseIter {
            private:
                Node* curr;
                Map* map;
            public:
                friend class Map;
                reverseIter(Node* node, Map* t) : curr(node), Map{t} {}

                bool operator==(const reverseIter& other) const { return map == other.map && curr == other.curr; }
                bool operator!=(const reverseIter& other) const { return !(*this == other); }

                reverseIter& operator++() {
                    if (curr == map->NIL) {
                        curr = map->getMax(map->root);
                        return *this;
                    }

                    if (curr->left != map->NIL) {
                        curr = curr->left;
                        while (curr->right != map->NIL) curr = curr->right;
                    } else {
                        Node* p = curr->parent;
                        while (p != map->NIL && curr == p->left) {
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
                    if (curr == map->NIL) return *this;
                    if (curr->right != map->NIL) {
                        curr = curr->right;
                        while (curr->left != map->NIL) curr = curr->left;
                    } else {
                        Node* p = curr->parent;
                        while (p != map->NIL && curr == p->right) {
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

                value_type& operator*() const { return curr->val; }
                value_type* operator->() const { return &(curr->val); }
        };

        class constreverseIter {
            private:
                const Node* curr;
                const Map* map;
            public:
                friend class Map;
                constreverseIter(const Node* node, const Map* t) : curr(node), map{t} {}

                bool operator==(const constreverseIter& other) const { return map == other.map && curr == other.curr; }
                bool operator!=(const constreverseIter& other) const { return !(*this == other); }

                constreverseIter& operator++() {
                    if (curr == map->NIL) {
                        curr = map->getMax(map->root);
                        return *this;
                    }

                    if (curr->left != map->NIL) {
                        curr = curr->left;
                        while (curr->right != map->NIL) curr = curr->right;
                    } else {
                        const Node* p = curr->parent;
                        while (p != map->NIL && curr == p->left) {
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
                    if (curr == map->NIL) return *this;
                    if (curr->right != map->NIL) {
                        curr = curr->right;
                        while (curr->left != map->NIL) curr = curr->left;
                    } else {
                        const Node* p = curr->parent;
                        while (p != map->NIL && curr == p->right) {
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

                const value_type& operator*() const { return curr->val; }
                const value_type* operator->() const { return &(curr->val); }
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

        Map();
        template<class InputIt>
        Map(InputIt first, InputIt last, const Compare& compare = Compare());
        Map(std::initializer_list<value_type> init, const Compare& compare = Compare());
        Map(const Map& other) {
            comp = other.comp;
            NIL = new Node();
            NIL->left = NIL;
            NIL->right = NIL;
            NIL->parent = NIL;
            NIL->color = Color::Black; 
            root = copy(other.root, NIL, other.NIL); 
        }
        Map(Map&& other) : Map() { swap(other); }

        
        Map& operator=(const Map& other);
        Map& operator=(Map&& other);
        Map& operator=( std::initializer_list<value_type> ilist );

        ~Map() { clear(root); delete NIL; }

        bool empty() const { return root == NIL; }
        size_t size() const { return size(root); }
        size_t size(Node* root) const {
            if (root == NIL) return 0;
            return 1 + size(root->left) + size(root->right);
        }

        void rotate_left(Node* x);
        void rotate_right(Node* y);

        Node* insert(value_type k);
        void insertFixUp(Node* node);

        const Node* search(const Node* node, const Key& key) const;
        Node* search(const Node* node, const Key& key);


        Node* getMin(Node* node);
        Node* getMax(Node* node);
        const Node* getMin(const Node* node) const {
            while (node != NIL && node->left != NIL) node = node->left;
            return node;
        }

        Node* getPredecessor(Node* node);
        Node* getSuccessor(Node* node);

        void transplant(Node* u, Node* v);
        void remove(value_type key);
        void deleteNode(Node* z);
        void deleteFixUp(Node* x);

        void swap(Map& other) { 
            std::swap(root, other.root); 
            std::swap(NIL, other.NIL);
            std::swap(comp, other.comp);
        }

        size_t count(const value_type& key) const { return contains(key); }
        bool contains(const value_type& key) const { return search(root, key) != NIL; }
        
        Iter lower_bound( const value_type& key);
        constIter lower_bound( const value_type& key ) const;
        Iter upper_bound( const value_type& key );
        constIter upper_bound( const value_type& key ) const;
        std::pair<Iter, Iter> equal_range( const value_type& key );
        std::pair<constIter, constIter> equal_range( const value_type& key ) const;

        T& at(const Key& key);
        const T& at(const Key& key) const;

        T& operator[](const Key& key);
        Compare key_comp() const { return comp; }
        value_compare value_comp() const { return value_compare(comp); }

        Node* extract(Node* z);
};

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map() {
    NIL = new Node();
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;
}

template <typename Key, typename T, typename Compare>
template<class InputIt>
Map<Key, T, Compare>:: Map(InputIt first, InputIt last, const Compare& compare) {
    NIL = new Node();
    comp = compare;
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;

    for (auto it = first; it != last; ++it) insert(*it);
}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Map(std::initializer_list<value_type> init, const Compare& compare) {
    NIL = new Node();
    comp = compare;
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;

    for (auto x : init) insert(x);
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::clear(Node* node) {
    if (node != NIL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::clear() {
    clear(root);
    root = NIL;
}

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Node* Map<Key, T, Compare>::copy (Node* node, Node* newParent, Node* n) {
    if (node == n) return NIL;

    Node* newNode = new Node(node->val);
    newNode->color = node->color;
    newNode->parent = newParent;

    newNode->left = copy(node->left, newNode, n);
    newNode->right = copy(node->right, newNode, n);
            
    return newNode;
}


template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(const Map& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root, NIL, other.NIL);
        comp = other.comp;
    }
    return *this;
} 

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(Map&& other) {
    if (this != &other) {
        clear(root);
        delete NIL;

        root = other.root;
        NIL = other.NIL;
        comp = other.comp;
        
        other.NIL = new Node();
        other.NIL->left = other.NIL;
        other.NIL->right = other.NIL;
        other.NIL->parent = other.NIL;
        other.NIL->color = Color::Black;
        other.root = other.NIL;
    }
    return *this;
}


template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(std::initializer_list<value_type> ilist) {
    Map tmp(ilist);
    swap(tmp);
    return *this;
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::rotate_left(Node* x) {
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

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::rotate_right(Node* y) {
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

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Node* Map<Key, T, Compare>::insert(value_type key) {
    Node* z = new Node(key);
    z->left = NIL;
    z->right = NIL;
    z->parent = NIL;

    Node* p = NIL;
    Node* curr = root;

    while (curr != NIL) {
        p = curr;
        if (comp(key,curr->val.first)) curr = curr->left; 
        else if (comp(curr->val.first, key)) curr = curr->right;
        else return curr;
    }
    
    z->parent = p;
    if (p == NIL) root = z;
    else if (comp(key,p->val.first)) p->left = z;
    else p->right = z;

    insertFixUp(z);
    return z;
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::insertFixUp(Node* z) {
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

template <typename Key, typename T, typename Compare>
const typename Map<Key, T, Compare>::Node* Map<Key, T, Compare>::search(const Node* node, const Key& key) const {
    while (node != NIL && (comp(node->val.first, key) || comp(key, node->val.first))) {
        if (comp(key,node->val.first)) node = node->left;
        else if (comp(node->val.first, key)) node = node->right;
    }
    return node;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Node* Map<Key, T, Compare>::search(const Node* node, const Key& key) {
    while (node != NIL && (comp(node->val.first, key) || comp(key, node->val.first))) {
        if (comp(key,node->val.first)) node = node->left;
        else if (comp(node->val.first, key)) node = node->right;
    }
    return node;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Node* Map<Key, T, Compare>::getMin(Node* node) {
    while (node != NIL && node->left != NIL) node = node->left;
    return node; 
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Node* Map<Key, T, Compare>::getMax(Node* node) {
    while (node != NIL && node->right != NIL) node = node->right;
    return node; 
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Node* Map<Key, T, Compare>::getPredecessor(Node* node) {
    if (node->left != NIL) return getMax(node->left);

    Node* p = node->parent;

    while (p != NIL && p->left == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Node* Map<Key, T, Compare>::getSuccessor(Node* node) {
    if (node->right != NIL) return getMin(node->right);

    Node* p = node->parent;

    while (p != NIL && p->right == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::transplant(Node* u, Node* v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::remove(value_type key) {
    Node* z = search(root, key);
    if (z != NIL) deleteNode(z);
}

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::deleteNode(Node* z) {
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

template <typename Key, typename T, typename Compare>
Map<Key, T, Compare>::Node* Map<Key, T, Compare>::extract(Node* z) {
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

template <typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::deleteFixUp(Node* x) {
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

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Iter Map<Key, T, Compare>::lower_bound(const value_type& key) {
    Node* res = NIL;
    Node* curr = root;

    while (curr != NIL) {
        if (!comp(curr->val.first, key)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return Iter(res, this);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::constIter Map<Key, T, Compare>::lower_bound(const value_type& key) const {
    const Node* res = NIL;
    const Node* curr = root;

    while (curr != NIL) {
        if (!comp(curr->val.first, key)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return constIter(res, this);
}


template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::Iter Map<Key, T, Compare>::upper_bound(const value_type& key) {
    Node* res = NIL;
    Node* curr = root;

    while (curr != NIL) {
        if (comp(key, curr->val.first)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return Iter(res, this);
}

template <typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::constIter Map<Key, T, Compare>::upper_bound(const value_type& key) const {
    const Node* res = NIL;
    const Node* curr = root;

    while (curr != NIL) {
        if (comp(key, curr->val.first)) {
            res = curr;
            curr = curr->left;
        } else curr = curr->right;
    }
    return constIter(res, this);
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::Iter, typename Map<Key, T, Compare>::Iter> Map<Key, T, Compare>::equal_range( const value_type& key ) {
    return {lower_bound(key), upper_bound(key)};
}

template <typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::constIter, typename Map<Key, T, Compare>::constIter> Map<Key, T, Compare>::equal_range( const value_type& key ) const {
    return {lower_bound(key), upper_bound(key)};
}

template<typename Key, typename T, typename Compare>
bool operator==( const Map<Key, T, Compare>& lhs, const Map<Key, T, Compare>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    
    auto cmp = lhs.value_compare;
    auto it1 = lhs.begin(); 
    auto it2 = rhs.begin();

    for(; it1 !=  lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (cmp(*it1, *it2) || cmp(*it2, *it1)) return false;
    } 
    return true;
}

template<typename Key, typename T, typename Compare>
bool operator!=( const Map<Key, T, Compare>& lhs, const Map<Key, T, Compare>& rhs) {
    return !(lhs == rhs);
}
 
template<typename Key, typename T, typename Compare>
bool operator<( const Map<Key, T, Compare>& lhs, const Map<Key, T, Compare>& rhs) {
    auto cmp = lhs.value_compare;
    auto it1 = lhs.begin(); 
    auto it2 = rhs.begin();

    for(; it1 !=  lhs.end() && it2 != rhs.end(); ++it1, ++it2) {
        if (cmp(*it1, *it2)) return true;
        else if (cmp(*it2, *it1)) return false;
    } 

    return it1 == lhs.end() && it2 != rhs.end();
}
    
template<typename Key, typename T, typename Compare>
bool operator<=( const Map<Key, T, Compare>& lhs, const Map<Key, T, Compare>& rhs) {
    return !(rhs < lhs);
}
    
template<typename Key, typename T, typename Compare>
bool operator>( const Map<Key, T, Compare>& lhs, const Map<Key, T, Compare>& rhs) {
    return rhs < lhs;
}
    
template<typename Key, typename T, typename Compare>
bool operator>=( const Map<Key, T, Compare>& lhs, const Map<Key, T, Compare>& rhs) {
    return !(lhs < rhs);
}

template<typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::at(const Key& key) {
    Node* curr = search(root, key);
    if (curr != NIL) return curr->val.second;
}

template<typename Key, typename T, typename Compare>
const T& Map<Key, T, Compare>::at(const Key& key) const {
    const Node* curr = search(root, key);
    if (curr != NIL) return curr->val.second;
}

template<typename Key, typename T, typename Compare>
T& Map<Key, T, Compare>::operator[](const Key& key) {
    Node* curr = search(root, key);
    if (curr == NIL) { 
        value_type p = {key, T()};
        curr = insert(p);
    }
    return curr->val.second;
}

#endif