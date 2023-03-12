mod dk_tree;

use crate::dk_tree::Node;

fn main() {
    let root = Node::new();
    root.add(Node::new());
    root.add(Node::new());
    let inner_child = Node::new();
    inner_child.add(Node::new());
    inner_child.add(Node::new());
    root.add(inner_child);
    let result = root.to_str();
    println!("{result:?}");
}
