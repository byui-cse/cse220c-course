/*
* list.h
*
*  Created by Lee Barney on 7/13/20.
*  Copyright © 2020 Lee Barney.
*  Permission is hereby granted, free of charge, to any person obtaining a
*  copy of this software and associated documentation files (the "Software"),
*  to deal in the Software without restriction, including without limitation the
*  rights to use, copy, modify, merge, publish, distribute, sublicense,
*  and/or sell copies of the Software, and to permit persons to whom the
*  Software is furnished to do so, subject to the following conditions:

*  The above copyright notice and this permission notice shall be
*  included in all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*/

#ifndef list_h
#define list_h

#include <functional>

using std::shared_ptr;
using std::weak_ptr;

/*
* declaration of custom namespace, class template name, properties,
* constructors, operators, and member functions.
*/
namespace naive {

template<typename T>
/// This is a partial, naive implementation of a list-type container.
class List{
private:
    /*
     * Node is a private inner class so nothing other than an instance
     * of list can instantiate one. Node's properties are public so
     * instances of list can manipulate and access them directly.
    */
    class Node{
    public:
        T value;
        weak_ptr<Node> parent;
        shared_ptr<Node> left_child;
        shared_ptr<Node> right_child;
        //Node constructors
        Node(T a_value);
        Node(T a_value, shared_ptr<Node> a_parent);
    };//end of Node class
    shared_ptr<Node> root_node;
public:
    List();
    void push_back(T aValue);
    List<T> map(std::function<T(T& a_value)>mapping_function);
    /*
     * There are many more instance functions a fully functional list would need.
     * Take CSE232, Designing Data Structures, to learn more!!
     */
};//end of List class
}//end of custom namespace


using naive::List;

/*
 * List instance function implementations
 */

template<typename T>
/// Instantiates an empty List.
///
/// Complexity - O(*n*)
List<T>::List(){}

template<typename T>
/// Adds a value to the end of the list. The implementation was selected to illustrate how to move through a sequence of linked nodes. There are designs for List that allow push_back to be implemented more efficiently than this naive design.
/// @param a_value the value to add to the list
///
/// - Complexity: O(*n*)
void List<T>::push_back(T a_value){
    shared_ptr<Node>current_node = root_node;
    shared_ptr<Node>node_to_add = shared_ptr<Node>(new Node(a_value));
   
    if(nullptr == current_node){
        root_node = node_to_add;
        return;
    }
    while (nullptr != current_node->right_child) {
        current_node = current_node->right_child;
    }
    current_node->right_child = node_to_add;
    node_to_add->parent = current_node;
}


template<typename T>
/// A non-destructive mapping instance methods.It applies the lambda function to
/// each value in the existing list and adds it to a list that is returned.
///
/// @param mapping_function the function to be applied to each value in the list
///
/// - Returns: a list that has as each of its values a modified version of each
/// value of this list
/// - Complexity: O(*n*) assuming that mapping_function has a complexity of O(*1*)
List<T> List<T>::map(std::function<T(T& a_value)>mapping_function){
    shared_ptr<Node>currentNode = root_node;
    //if this list is empty, its mapped version should be empty also
     if(nullptr == currentNode){
         return List<T>();//empty list
     }
    List<T> mapped_list;
     while (nullptr != currentNode) {
         T node_value = currentNode.get()->value;
         T mapped_value = mapping_function(node_value);
         mapped_list.push_back(mapped_value);
         currentNode = currentNode->right_child;
     }
    //return a copy of the list
    return mapped_list;
}

/*
 * Node instance function implementations
 */
template<typename T>
/// Value based constructor for a Node. For this constructor, the parent, left child, and right child nodes are
/// all null
/// @param a_value the value to be stored in the node
///
/// - Complexity: O(*1*)
List<T>::Node::Node(T a_value):value{a_value}{}


template<typename T>
/// Value and parent based constructor for a Node. For this constructor, the left and right child nodes are null
///
/// @param a_value the value to be stored in the node
/// @param a_parent a constant reference to the parent node of the node being constructed
///
/// - Complexity: O(*1*)
List<T>::Node::Node(T a_value, shared_ptr<Node> a_parent):value{a_value},parent{a_parent}{}

#endif /* list_h */
