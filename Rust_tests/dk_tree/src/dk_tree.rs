use std::cell::RefCell;
use std::rc::{Rc, Weak};

// Note: do not derive Clone to make this move-only.
pub struct Node(Rc<RefCell<Node_>>);

pub struct WeakNode(Weak<RefCell<Node_>>);

struct Node_ {
    parent: Option<WeakNode>,
    children: Vec<Node>,
}

impl Node {
    pub fn new() -> Self {
        Node(Rc::new(RefCell::new(Node_ {
            parent: None,
            children: Vec::new(),
        })))
    }
    pub fn add(&self, node: Node) {
        // No need to remove from old parent; move semantics mean that must have
        // already been done.
        node.0.borrow_mut().parent = Some(WeakNode(Rc::downgrade(&self.0)));
        self.0.borrow_mut().children.push(node);
    }
    // just to have something visually printed
    pub fn to_str(&self) -> String {
        let mut result_string = "[".to_string();
        for child in self.0.borrow().children.iter() {
            result_string.push_str(&format!("{},", child.to_str()));
        }
        result_string += "]";
        result_string
    }
}
