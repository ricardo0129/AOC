use std::fs;
use std::cmp::min;
use std::cmp::max;

fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut lines: Vec<&str> = file.split('\n').collect();
    //lines.pop();
    let mut seeds: Vec<&str> = lines[0].split(' ').collect();
    seeds.remove(0);
    let mut seeds: Vec<i64> = seeds.iter().map(|x| x.parse::<i64>().unwrap()).collect();

    let mut mapping: Vec<(i64,i64,i64)> = Vec::new();
    for i in 2..lines.len() {
        let line = lines[i];
        if line.len() == 0 {
            for j in 0..seeds.len() {
                for k in 0..mapping.len() {
                    if mapping[k].0 <= seeds[j] && seeds[j] <= (mapping[k].0 + mapping[k].2-1) {
                        seeds[j] = (seeds[j]-mapping[k].0) + mapping[k].1;
                        break;
                    }
                }
            }
            mapping.clear();
            continue;
        }
        else {
            let mut p: Vec<&str> = line.split(' ').collect();
            if !p[0].chars().nth(0).unwrap().is_numeric() {
                continue;
            }
            let numbs: Vec<i64> = p.iter().map(|x| x.parse::<i64>().unwrap()).collect();
            mapping.push((numbs[1], numbs[0], numbs[2]));
        }
    }
    println!("{}", seeds.iter().min().unwrap());
}

fn solve(i: usize, interval: &(i64, i64), mapping: &Vec<(i64, i64, i64)>, next: &mut Vec<(i64, i64)>) {
    if interval.0 > interval.1 {
        return;
    }
    if i == mapping.len() {
        next.push(*interval);
        return;
    }
    let left: i64 = max(interval.0, mapping[i].0);
    let right: i64 = min(interval.1, mapping[i].0 + mapping[i].2 - 1);
    if left > right {
        solve(i+1, interval, mapping, next);
        return;
    }
    assert!(left<=right);
    next.push((left-mapping[i].0+mapping[i].1, right-mapping[i].0+mapping[i].1));
    solve(i+1, &(interval.0, left-1), mapping, next);
    solve(i+1, &(right+1, interval.1), mapping, next);
}
fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut lines: Vec<&str> = file.split('\n').collect();
    let mut seeds: Vec<&str> = lines[0].split(' ').collect();
    seeds.remove(0);
    let mut seeds: Vec<i64> = seeds.iter().map(|x| x.parse::<i64>().unwrap()).collect();
    let mut pairs: Vec<(i64, i64)> = Vec::new();
    let mut sum1: i64 = 0;
    for i in 0..seeds.len()/2 {
        pairs.push((seeds[i*2], seeds[i*2] + seeds[i*2+1] - 1));
        sum1 += pairs[i].1 - pairs[i].0 + 1;
    }
    //print!("LAST:{}END",lines[lines.len()-1]);
    let mut mapping: Vec<(i64,i64,i64)> = Vec::new();
    for i in 2..lines.len() {
        let line = lines[i];
        if line.len() == 0 {
            let mut next: Vec<(i64,i64)> = Vec::new();
            for j in 0..pairs.len() {
                solve(0,&pairs[j],&mapping,&mut next);
            }
            pairs = next;
            for i in 0..pairs.len() {
                //print!("({},{}) ", pairs[i].0, pairs[i].1);
            }
            let mut sum2: i64 = 0;
            for i in 0..pairs.len() {
                sum2 += pairs[i].1 - pairs[i].0 + 1;
            }
            mapping.clear();
            continue;
        }
        else {
            let mut p: Vec<&str> = line.split(' ').collect();
            if !p[0].chars().nth(0).unwrap().is_numeric() {
                continue;
            }
            let numbs: Vec<i64> = p.iter().map(|x| x.parse::<i64>().unwrap()).collect();
            mapping.push((numbs[1], numbs[0], numbs[2]));
        }
    }
    let mut ans: i64 = pairs[0].0;
    pairs.sort();
    for i in 0..pairs.len() {
        ans = min(ans, pairs[i].0);
    }
    println!("{}", ans);
}

fn main() {
    part1();
    part2();
}
