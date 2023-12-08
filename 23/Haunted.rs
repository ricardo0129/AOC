use std::fs;
use std::collections::BTreeMap;

struct Node {
    left: String,
    right: String,
}

impl Node {
    fn new(left: String, right: String) -> Self {
        Node {left: left, right: right}
    }
}
fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 {
        return a;
    }
    gcd(b, a%b)
}
fn lcm(a: i64, b: i64) -> i64 {
    a / gcd(a, b) * b
}

fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let lines: Vec<&str> = file.split('\n').collect();
    let path: String = lines[0].to_string();
    let mut tree: BTreeMap<String,Node> = BTreeMap::new(); 
    for j in 2..lines.len()-1 {
        let u = (&lines[j][0..3]).to_string();
        let l = (&lines[j][7..10]).to_string();
        let r = (&lines[j][12..15]).to_string();
        tree.insert(u, Node::new(l, r));
    }
    let mut state: String = "AAA".to_string();
    let mut i = 0;
    while state != "ZZZ" {
        let c: char = path.chars().nth(i % path.len()).unwrap();
        if c == 'L' {
            state = tree[&state].left.clone();
        }
        else {
            state = tree[&state].right.clone();
        }
        i += 1;
    }
    println!("{}", i);
}

fn reach_end(start: String, tree: &BTreeMap<String,Node>, path: &String) -> (Vec<i64>,i64,i64) {
    let mut curr: String = start.clone();
    let mut ends: Vec<i64> = Vec::new();
    let mut dist: BTreeMap<(String,i64),i64> = BTreeMap::new();
    let mut prev: String;
    dist.insert((curr.clone(), 0), 0);
    let mut i = 0;
    let mut iteration: i64 = 0;
    loop {
        let c: char = path.chars().nth(i % path.len()).unwrap();
        
        let last_char: char = curr.chars().nth(2).unwrap();
        if last_char == 'Z' {
            ends.push(iteration);
        }

        if c == 'L' {
            prev = curr.clone();
            curr = tree[&curr].left.clone();
            let key: (String,i64) = (curr.clone(), ((i+1) % path.len()) as i64);
            if dist.contains_key(&key) {
                break;
            }
            dist.insert(key, dist[&(prev.clone(), i as i64)] + 1);
        }
        else {
            prev = curr.clone();
            curr = tree[&curr].right.clone();
            let key: (String,i64) = (curr.clone(), ((i+1) % path.len()) as i64);
            if dist.contains_key(&key) {
                break;
            }
            dist.insert(key, dist[&(prev.clone(), i as i64)] + 1);
        }
        i = (i + 1) % path.len();
        iteration += 1;
    }
    let last = dist[&(prev.clone(),i as i64)];
    let first = dist[&(curr, ( (i+1)%path.len() ) as i64)];
    return (ends, last, first);
}

fn repeat(start: i64, repeat: i64, zpos: i64, last_node: i64, first_node: i64) -> (i64, i64) {
    let cycle_length = last_node - first_node + 1;
    let mut curr_pos = (start-first_node) % cycle_length;
    let mut iterations: i64 = 0;
    let final_node = zpos - first_node;
    while curr_pos != final_node {
        curr_pos = (curr_pos + repeat) % cycle_length;
        iterations += 1;
    }
    let new_repeat = lcm(repeat, cycle_length);
    (start + iterations * repeat,new_repeat)
}

fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let lines: Vec<&str> = file.split('\n').collect();
    let path: String = lines[0].to_string();
    let mut tree: BTreeMap<String,Node> = BTreeMap::new(); 
    for j in 2..lines.len()-1 {
        let u = (&lines[j][0..3]).to_string();
        let l = (&lines[j][7..10]).to_string();
        let r = (&lines[j][12..15]).to_string();
        tree.insert(u, Node::new(l, r));
    }
    let mut states: Vec<String> = Vec::new();

    for key in &tree {
        if key.0.chars().nth(2).unwrap() == 'A' {
            states.push(key.0.clone());            
        }
    }
    
    let mut a: Vec<(Vec<i64>,i64,i64)> = Vec::new();
    for s in &states {
        let x = reach_end(s.clone(), &tree, &path);
        a.push(x);
    }
    a.sort();
    let mut start: i64 = a[0].0[0];
    let mut rep : i64 = a[0].1 - a[0].2 + 1;
    for i in 1..a.len() {
        let res = repeat(start, rep , a[i].0[0], a[i].1, a[i].2);
        start = res.0;
        rep = res.1;
    }
    println!("{}", start);

}

fn main() {
    part1();
    part2();
}
