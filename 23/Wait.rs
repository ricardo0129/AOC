use std::fs;

fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let lines: Vec<&str> = file.split('\n').collect();
    let mut time: Vec<&str> = lines[0].split_whitespace().collect();
    time.remove(0);
    let time: Vec<i64> = time.iter().map(|x| x.parse::<i64>().unwrap()).collect();
    let mut dist: Vec<&str> = lines[1].split_whitespace().collect();
    dist.remove(0);
    let dist: Vec<i64> = dist.iter().map(|x| x.parse::<i64>().unwrap()).collect();
    let mut ans: i64 = 1;
    for j in 0..time.len() {
        let mut c: i64 = 0;
        for k in 1..time[j] {
            let left: i64 = time[j] - k;
            if left * k > dist[j] {
                c += 1;
            }
        }
        ans = ans * c;
    }
    println!("{}", ans);
}

fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let lines: Vec<&str> = file.split('\n').collect();
    let mut time: Vec<&str> = lines[0].split_whitespace().collect();
    time.remove(0);
    let time: Vec<i64> = time.iter().map(|x| x.parse::<i64>().unwrap()).collect();
    let mut dist: Vec<&str> = lines[1].split_whitespace().collect();
    dist.remove(0);
    let dist: Vec<i64> = dist.iter().map(|x| x.parse::<i64>().unwrap()).collect();
    let mut t: String = String::new();
    let mut d: String = String::new();
    for j in 0..time.len() {
        t += &time[j].to_string();
        d += &dist[j].to_string();
    }
    let t: i64 = t.parse::<i64>().unwrap();
    let d: i64 = d.parse::<i64>().unwrap();
    let mut left: i64 = 1;
    let mut right: i64 = t;
    let mut lower : i64 = -1;
    while left <= right {
        let m = (right-left) / 2 + left;
        let remain = t - m;
        if remain * m > d {
            lower = m;
            right = m - 1;
        }
        else {
            left = m + 1;
        }
    }
    let mut left: i64 = 1;
    let mut right: i64 = t;
    let mut upper : i64 = -1;
    while left <= right {
        let m = (right-left) / 2 + left;
        let remain = t - m;
        if remain * m > d {
            upper = m;
            left = m + 1;
        }
        else {
            right = m - 1;
        }
    }
    println!("{}", upper-lower+1);
}

fn main() {
    part1();
    part2();
}
