#include "ExpressionTree.h"
#include <string>


/**
@brief Initializes inside variables

*/
template<typename DataType>
ExprTree<DataType>::ExprTree()
{
  ExprTreeNode *newNode = new ExprTreeNode();
  root = newNode;
  newNode->left = NULL;
  newNode->right = NULL;
}


/**
default Constructor
*/
template<typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode()
{

}

/**
@brief Copy Constructor
*/
template<typename DataType>
ExprTree<DataType>::ExprTree(const ExprTree& other)
{

      (*this) = other;


}

/**
@Brief constructor for the ExprTreeNode class
@param char elem, ExprTreeNode left, ExprTreeNode right
*/
template<typename DataType>
ExprTree<DataType>::ExprTreeNode::ExprTreeNode(char elem, ExprTreeNode *leftPtr,
                                                ExprTreeNode *rightPtr)
{
  dataItem = elem;
  left = leftPtr;
  right = rightPtr;
}

/**
@Brief equates the values of the two objects (deep copy)
@param const ExprTree& other
*/
template<typename DataType>
ExprTree<DataType>& ExprTree<DataType>::operator=(const ExprTree& other)
{
  clear();

  root = operator_helper(*(other.root));

}


/**
@brief copies values of one ExprTree to another
@param const ExprTreeNode& other
*/
template<typename DataType>
typename ExprTree<DataType>::ExprTreeNode* ExprTree<DataType>::operator_helper(const ExprTreeNode& other)
{

  if(&other == NULL)
  {
    return NULL;
  }

  ExprTreeNode* another = new ExprTreeNode(other.dataItem, NULL, NULL);

  another->left = operator_helper((*other.left));
  another->right = operator_helper((*other.right));

  return another;
}
/**
@brief this is the Destructor
*/
template<typename DataType>
ExprTree<DataType>::~ExprTree()
{
  clear();
}

/**
@brief This builds the tree of data values
*/
template<typename DataType>
void ExprTree<DataType>::build()
{
  build_helper(*&root);
}

/**
@brief This helper function does all operations for build()
@param ExprTreeNode *& cursor (root of tree)
*/
template<typename DataType>
void ExprTree<DataType>::build_helper(ExprTreeNode *&cursor)
{
  char input = cin.get();



  if(input == '+' || input == '-' || input == '/' || input == '*')
  {
    cursor->dataItem = input;
    cursor->left = new ExprTreeNode();
    cursor->right = new ExprTreeNode();
    build_helper(cursor->left);
    build_helper(cursor->right);

  }
  else
  {
    cursor->dataItem = input;
  }


  return;

}

/**
@brief prints out the expression that the tree represents
*/
template<typename DataType>
void ExprTree<DataType>::expression () const
{
  expression_helper(root);
}

/**
@brief This function does all the operations for expression()
@param const ExprTreeNode *cursor (root of the calling objects)
*/
template<typename DataType>
void ExprTree<DataType>::expression_helper(const ExprTreeNode *cursor) const
{
  if(cursor->dataItem == '+' || cursor->dataItem == '-' || cursor->dataItem == '*'
     || cursor->dataItem == '/')
     {
       cout << "(";
       expression_helper(cursor->left);
       cout << cursor->dataItem;
       expression_helper(cursor->right);
       cout << ")";

     }
     else
     {
       cout << cursor->dataItem;
       return;
     }
}

/**
@brief this evaluates the value to which the expression represents
*/
template<typename DataType>
DataType ExprTree<DataType>::evaluate () const throw (logic_error)
{
  if(root == NULL)
  {
    throw logic_error("evaluate() tree empty");
  }

  ExprTreeNode *cursor = root;

  DataType result = evaluate_helper(*&cursor);

  return result;




}
/**
@brief  This function does all operations for evaluate()
@param const ExprTreeNode *cursor (pointer to root)
*/
template<typename DataType>
DataType ExprTree<DataType>::evaluate_helper(const ExprTreeNode *cursor) const
{

  switch(cursor->dataItem)
  {
    case '+':
      return (evaluate_helper(cursor->left) + evaluate_helper(cursor->right));
      break;
    case '-':
      return (evaluate_helper(cursor->left) - evaluate_helper(cursor->right));
      break;
    case '*':
      return (evaluate_helper(cursor->left) * evaluate_helper(cursor->right));
      break;
    case '/':
      return (evaluate_helper(cursor->left) / evaluate_helper(cursor->right));
      break;
    default:
      return (cursor->dataItem - '0');
      break;
  }

}

/**
@brief this clears the tree
*/
template<typename DataType>
void ExprTree<DataType>::clear()
{
  //clear_helper(*&root);
  root = NULL;
}

/**
@brief This function does all operations for clear()
@param ExprTreeNode *&cursor, which is a pointer to root
*/
template<typename DataType>
void ExprTree<DataType>::clear_helper(ExprTreeNode *&cursor)
{
  if(cursor != NULL)
  {
    clear_helper(cursor->left);
    clear_helper(cursor->right);
  }


  delete cursor;
  cursor = NULL;

}
/**
@brief commutes the tree (will not necessarily preserve evaluation values)
*/
template<typename DataType>
void ExprTree<DataType>::commute()
{

  commute_helper(root);
}

/**
@brief This function does all operations for commute()
@param ExprTreeNode*& cursor, which is a pointer to null
*/
template<typename DataType>
void ExprTree<DataType>::commute_helper(ExprTreeNode*& cursor)
{
  if(cursor == NULL)
  {
    return;
  }
  ExprTreeNode *newNode = cursor->right;
  cursor->right = cursor->left;
  cursor->left = newNode;

  commute_helper(cursor->left);
  commute_helper(cursor->right);



  return;
}
/**
@brief Evaluates whether two trees are equivalent or not
@param const ExprTree& source, which is the tree to be compared against
*/
template<typename DataType>
bool ExprTree<DataType>::isEquivalent(const ExprTree& source) const
{
  int one = 0;
  int two = 0;

  one = source.evaluate();
  two = evaluate();

  cout << "ONE: " << one;
  cout << "TWO: " << two;

  if(one != two)
  {
    return false;
  }
  else
  {
    return true;
  }
}

/**
@brief this shows the structure of the tree
*/
template <typename DataType>
void ExprTree<DataType>:: showStructure () const

// Outputs an expression tree. The tree is output rotated counter-
// clockwise 90 degrees from its conventional orientation using a
// "reverse" inorder traversal. This operation is intended for testing
// and debugging purposes only.

{
    if ( isEmpty() )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

template <typename DataType>
bool ExprTree<DataType>::isEmpty() const
{
  if(root == NULL)
    return true;
  else
    return false;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename DataType>
void ExprTree<DataType>:: showHelper ( ExprTreeNode *p, int level ) const

// Recursive helper for the showStructure() function. Outputs the
// subtree whose root node is pointed to by p. Parameter level is the
// level of this node within the expression tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )   // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem;        // Output dataItem
        if ( ( p->left != 0 ) &&          // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);         // Output left subtree
     }
}
