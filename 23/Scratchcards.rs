use std::fs;
use std::collections::BTreeSet;


fn check(st: &str) -> bool {
    if st.len() == 0 {
        return false;
    }
    for j in 0..st.len() {
        let c = st.chars().nth(j).unwrap();
        if !c.is_numeric() {
            return false;
        }
    }
    true
}

fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut ans: i32 = 0;
    for line in file.split('\n') {
        let v: Vec<&str> = line.split(' ').collect();
        let mut left: bool = true;
        let mut set: BTreeSet<i32> = BTreeSet::new();
        let mut good: i32 = 0;
        for j in 0..v.len() {
            if v[j] == "|" {
                left = false;
            }
            if !check(v[j]) {
                continue;
            }
            let value: i32 = v[j].to_string().parse().unwrap();
            if left {
                set.insert(value);
            }
            else {
                if set.contains(&value) {
                    good += 1;
                }
            }
        }
        if good != 0 {
            ans += 1<<(good-1);
        }
    }
    println!("{}", ans);
}

fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut lines: Vec<&str> = file.split('\n').collect();
    lines.pop();
    let mut ans: i32 = 0;
    let mut counts: Vec<i32> = vec![1;lines.len()];
    let mut k: i32 = 0;
    for line in lines {
        let v: Vec<&str> = line.split(' ').collect();
        let mut left: bool = true;
        let mut set: BTreeSet<i32> = BTreeSet::new();
        let mut good: i32 = 0;
        for j in 0..v.len() {
            if v[j] == "|" {
                left = false;
            }
            if !check(v[j]) {
                continue;
            }
            let value: i32 = v[j].to_string().parse().unwrap();
            if left {
                set.insert(value);
            }
            else {
                if set.contains(&value) {
                    good += 1;
                }
            }
        }
        if good != 0 {
            for i in (k+1)..(k+1+good) {
                counts[i as usize] += counts[k as usize];
            }
        }
        ans += counts[k as usize];
        k+=1;
    }
    println!("{}", ans);
}

fn main() {
    part1();
    part2();
}
