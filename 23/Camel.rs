use std::fs;
use std::cmp::Ordering;
use std::cmp::max;
use std::collections::BTreeMap;

fn rank(cards: &String) -> i32 {
    let mut freq: BTreeMap<char, i32> = BTreeMap::new();
    let mut highest: i32 = 0;
    for c in cards.chars() {
        if freq.contains_key(&c) {
            freq.insert(c, freq[&c] + 1);
        }
        else {
            freq.insert(c, 1);
        }
        highest = max(highest, freq[&c]);
    }
    if highest == 5 {
        return 7;
    }
    if highest == 4 {
        return 6;
    }
    if freq.len() == 2 {
        return 5;
    }
    if highest == 3 {
        return 4;
    }
    if freq.len() == 5 {
        return 1;
    }
    if freq.len() == 4 {
        return 2;
    }
    if freq.len() == 3 {
        return 3;
    }
    0
}

fn rank2(cards: &String) -> i32 {
    let mut freq: BTreeMap<char, i32> = BTreeMap::new();
    let mut highest: i32 = 0;
    let mut jokers: i32 = 0;
    for c in cards.chars() {
        if c == 'J' {
            jokers += 1;
            continue;
        }
        if freq.contains_key(&c) {
            freq.insert(c, freq[&c] + 1);
        }
        else {
            freq.insert(c, 1);
        }
        highest = max(highest, freq[&c]);
    }
    if highest + jokers == 5 {
        return 7;
    }
    else if highest + jokers == 4 {
        return 6;
    }
    else if freq.len() == 2 {
        return 5;
    }
    else if highest + jokers == 3 {
        return 4;
    }
    else if freq.len() == 3 {
        return 3;
    }
    else if highest + jokers == 2 {
        return 2;
    }
    return 1;
}


fn f(a: &String, b: &String) -> Ordering {
    let val: BTreeMap<char,i32> = BTreeMap::from([
    ('A',1),('K',2),('Q',3),('J',4),('T',5),
    ('9',6),('8',7),('7',8),('6',9),('5',10),
    ('4',11),('3',12),('2',13)]);
    for i in 0..a.len() {
        let c1 = a.chars().nth(i).unwrap();
        let c2 = b.chars().nth(i).unwrap();
        if val[&c1] < val[&c2] {
            return Ordering::Greater;
        }
        else if val[&c1] > val[&c2] {
            return Ordering::Less;
        }
    }
    return Ordering::Equal;
}
fn f2(a: &String, b: &String) -> Ordering {
    let val: BTreeMap<char,i32> = BTreeMap::from([
    ('A',1),('K',2),('Q',3),('T',5),
    ('9',6),('8',7),('7',8),('6',9),('5',10),
    ('4',11),('3',12),('2',13),('J',14)]);
    for i in 0..a.len() {
        let c1 = a.chars().nth(i).unwrap();
        let c2 = b.chars().nth(i).unwrap();
        if val[&c1] < val[&c2] {
            return Ordering::Greater;
        }
        else if val[&c1] > val[&c2] {
            return Ordering::Less;
        }
    }
    return Ordering::Equal;
}

fn compare(a: &String, b: &String) -> Ordering {
    if rank(a) < rank(b) {
        return Ordering::Less;
    }
    else if rank(a) > rank(b) {
        return Ordering::Greater;
    }
    else {
        return f(a, b);
    }
}

fn compare2(a: &String, b: &String) -> Ordering {
    if rank2(a) < rank2(b) {
        return Ordering::Less;
    }
    else if rank2(a) > rank2(b) {
        return Ordering::Greater;
    }
    else {
        return f2(a, b);
    }
}
fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut ans: i32 = 0;
    let mut hands: Vec<(String, i32)> = Vec::new();
    for line in file.split('\n') {
        if line.len() == 0 {
            continue;
        }
        let v: Vec<&str> = line.split(' ').collect(); 
        let key: i32 = v[1].parse::<i32>().unwrap();
        hands.push((v[0].to_string(), key));
    }
    hands.sort_by(|a, b| 
            compare(&a.0, &b.0)
                  );
    for i in 0..hands.len() {
        ans += (( (i+1) as i32) * hands[i].1) as i32;
    }
    println!("{}", ans);
}

fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut ans: i64 = 0;
    let mut hands: Vec<(String, i32)> = Vec::new();
    for line in file.split('\n') {
        if line.len() == 0 {
            continue;
        }
        let v: Vec<&str> = line.split(' ').collect(); 
        let key: i32 = v[1].parse::<i32>().unwrap();
        hands.push((v[0].to_string(), key));
    }
    hands.sort_by(|a, b| 
            compare2(&a.0, &b.0)
                  );
    for i in 0..hands.len() {
        ans += (( (i+1) as i64) * hands[i].1 as i64) as i64;
    }
    println!("{}", ans);
}

fn main() {
    part1();
    part2();
}
