use std::fs;
use std::collections::BTreeSet;


fn valid(i: i32, j: i32, grid: &Vec<String>) -> bool {
    i >= 0 && j >=0 && i < (grid.len() as i32) && j < (grid[0].len() as i32)
}

fn symbol(i: i32, j: i32, grid: &Vec<String>) -> bool {
    let dirs: Vec<(i32,i32)> = vec![(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]; for d in dirs {
        let i2 = i + d.0;
        let j2 = j + d.1;
        if valid(i2, j2, grid) {
            let c = grid[i2 as usize].chars().nth(j2 as usize).unwrap();
            if !c.is_numeric() && c != '.' {
                return true;
            }
        }
    }
    false
}

fn check(row:i32, left: i32, right: i32, grid: &Vec<String>) -> bool {
    if left > right {
        return false;
    }
    for i in left..(right+1) {
        if symbol(row, i, grid) {
            return true;
        }
    }
    false
}

fn parse(v: &Vec<i32>) -> i32 {
    v.iter().fold(0, |sum, val| sum * 10 + val)
}

fn cross(i: i32, j: i32, grid: &Vec<String>, updates: &mut BTreeSet<(i32,i32)>) {
    let dirs: Vec<(i32,i32)> = vec![(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]; for d in dirs {
        let i2 = i + d.0;
        let j2 = j + d.1;
        if valid(i2, j2, grid) {
            let c = grid[i2 as usize].chars().nth(j2 as usize).unwrap();
            if c == '*' {
                updates.insert((i2,j2));
            }
        }
    }
}

fn update(row: i32, left: i32, right: i32, grid: &Vec<String>, count: &mut Vec<Vec<i32>>, values: &mut Vec<Vec<i32>>, num: i32) {
    let mut updates: BTreeSet<(i32,i32)> = BTreeSet::new();
    if left <= right {
        for i in left..(right+1) {
            cross(row, i, grid, &mut updates); 
        }
    }
    for pos in &updates {
        count[pos.0 as usize][pos.1 as usize] += 1;
        values[pos.0 as usize][pos.1 as usize] *= num;
    }
}

fn part2() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut grid: Vec<String> = Vec::new();
    for line in file.split('\n') {
        grid.push(line.to_string());
    }
    grid.pop();
    let rows: i32 = grid.len() as i32;
    let cols: i32 = grid[0].len() as i32;
    let mut ans: i32 = 0;
    let mut counts: Vec<Vec<i32>> = vec![vec![0;cols as usize];rows as usize];
    let mut v: Vec<Vec<i32>> = vec![vec![1;cols as usize];rows as usize];
    for i in 0..rows {
        let mut values: Vec<i32> = Vec::new();
        for j in 0..cols {
            let c = grid[i as usize].chars().nth(j as usize).unwrap();
            if c.is_numeric() {
                let v: i32 = c as i32 - 0x30; 
                values.push(v);
            }     
            else {
                if check(i, j - values.len() as i32, j-1, &grid) {
                    let value: i32 = parse(&values); 
                    update(i, j - values.len() as i32, j-1, &grid, &mut counts, &mut v, value); 
                }
                values.clear();
            }
        }
        if check(i, cols - values.len() as i32, cols-1, &grid) {
            let value: i32 = parse(&values); 
            update(i, cols - values.len() as i32, cols-1, &grid, &mut counts, &mut v, value); 
        }
    }
    for i in 0..rows {
        for j in 0..cols {
            let c = grid[i as usize].chars().nth(j as usize).unwrap();
            if c == '*' && counts[i as usize][j as usize] == 2 {
                ans += v[i as usize][j as usize];
            }
        }
    }
    println!("{}", ans);
}

fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut grid: Vec<String> = Vec::new();
    for line in file.split('\n') {
        grid.push(line.to_string());
    }
    grid.pop();
    let rows: i32 = grid.len() as i32;
    let cols: i32 = grid[0].len() as i32;
    let mut ans: i32 = 0;
    for i in 0..rows {
        let mut values: Vec<i32> = Vec::new();
        for j in 0..cols {
            let c = grid[i as usize].chars().nth(j as usize).unwrap();
            if c.is_numeric() {
                let v: i32 = c as i32 - 0x30; 
                values.push(v);
            }     
            else {
                let value: i32 = parse(&values); 
                if check(i, j - values.len() as i32, j-1, &grid) {
                   ans += value;
                }
                values.clear();
            }
        }
        if check(i, cols - values.len() as i32, cols-1, &grid) {
           ans += parse(&values); 
        }
    }
    println!("{}", ans);
}

fn main() {
    part1();
    part2();
}
