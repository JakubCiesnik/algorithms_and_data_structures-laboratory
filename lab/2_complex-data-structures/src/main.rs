#[derive(Debug)]
struct Node {
    info: i32,
    next: Option<Box<Node>>,
}

impl Node {
    fn insert_sorted(list: Option<Box<Node>>, a: i32) -> Option<Box<Node>> {
        let mut new_node = Box::new(Node {
            info: a,
            next: None,
        });

        match list {
            None => Some(new_node),
            Some(mut head) => {
                if a < head.info {
                    Some(Box::new(Node {
                        info: a,
                        next: Some(head),
                    }))
                } else {
                    let mut current = &mut head;

                    while let Some(ref mut next_node) = current.next {
                        if next_node.info >= a {
                            break;
                        }
                        current = next_node;
                    }

                    new_node.next = current.next.take();
                    current.next = Some(new_node);

                    Some(head)
                }
            }
        }
    }

    fn print_list(list: &Option<Box<Node>>) {
        let mut current = list.as_ref();
        while let Some(node) = current {
            print!("{} -> ", node.info);
            current = node.next.as_ref();
        }
        println!("None");
    }
}

fn main() {
    let mut list: Option<Box<Node>> = None;

    // Example inserts
    list = Node::insert_sorted(list, 5);
    list = Node::insert_sorted(list, 3);
    list = Node::insert_sorted(list, 8);
    list = Node::insert_sorted(list, 1);
    list = Node::insert_sorted(list, 6);

    Node::print_list(&list);
}
