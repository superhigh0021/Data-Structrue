#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))

/******************************************************************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************************************************************/
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc) /*兄弟*/
#define uncle(x) (sibling((x)->parent)) /*叔叔*/



//define 返回的是引用，注意x后面的是 .  所以不是指针而是一个节点，值传递无法修改它的属性，必须要多此一举用define传引用
//从父亲节点调整的渠道
#define FromParentTo(x) \
    (IsRoot(x) ? this->_root : \
    (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
