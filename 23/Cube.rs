use std::fs;
use std::cmp;

fn test() {
    let file = fs::read_to_string("./in").unwrap();
    for line in file.split('\n') {
        for word in line.split(" ") {
            println!("{}", word);
        }

    }
}
fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut ans: i32 = 0;
    let mut j: i32 = 0;
    for line in file.split('\n') {
        let s: Vec<_> = line.split(' ').collect();
        let mut i: usize = 2;
        let mut valid: bool = true;
        while i < s.len() {
            let st = s[i+1];
            let mut vr = st; //&st[0..st.len()-1];
            if !vr.chars().nth(vr.len()-1).unwrap().is_alphanumeric() {
                vr = &st[0..st.len()-1]; 
            }
            let value = s[i].parse::<i32>().unwrap();
            if vr == "blue" {
                valid = valid && (value <= 14); 
            }
            else if vr == "red" {
                valid = valid && (value <= 12); 
            }
            else if vr == "green" {
                valid = valid && (value <= 13); 
            } 
            i += 2;
        }
        j += 1;
        if valid && line.len() > 0{
            ans += j;
        }
    }
    println!("{}", ans);
}

fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut ans: i32 = 0;
    for line in file.split('\n') {
        let s: Vec<_> = line.split(' ').collect();
        let mut i: usize = 2;
        let mut res: Vec<i32> = vec!(0,0,0);
        while i < s.len() {
            let st = s[i+1];
            let mut vr = st; //&st[0..st.len()-1];
            if !vr.chars().nth(vr.len()-1).unwrap().is_alphanumeric() {
                vr = &st[0..st.len()-1]; 
            }
            let value = s[i].parse::<i32>().unwrap();
            if vr == "blue" {
                res[0] = cmp::max(res[0], value);
            }
            else if vr == "red" {
                res[1] = cmp::max(res[1], value);
            }
            else if vr == "green" {
                res[2] = cmp::max(res[2], value);
            } 
            i += 2;
        }
        ans += res[0] * res[1] * res[2];
    }
    println!("{}", ans);
}

fn main() {
    test();
    part1();
    part2();
}
