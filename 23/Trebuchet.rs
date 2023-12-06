use std::fs;

fn part1() {
    let file =  fs::read_to_string("./in").expect("Err");
    let mut ans: u32 = 0;
    for line in file.split('\n') {
        for j in 0..line.len() {
            let c: char = line.chars().nth(j).unwrap();
            if c.is_numeric() {
                let val: u32 = c.to_digit(10).unwrap();
                ans += val * 10;
                break;
            }
        }

        for j in 0..line.len() {
            let c: char = line.chars().nth(line.len()-1-j).unwrap();
            if c.is_numeric() {
                let val: u32 = c.to_digit(10).unwrap();
                ans += val;
                break;
            }
        }
    }
    println!("{}", ans);
}

fn check(st: String, patt: String, idx: u32) -> bool {
    if (st.len() - (idx as usize) + 1) <= patt.len() {
        return false;
    }
    let subtr = &st[(idx as usize)..((idx as usize)+patt.len())];
    return subtr == patt;
}
fn part2() {
    let file = fs::read_to_string("./in").expect("Err");
    let mut ans: u32 = 0;
    let number_list: Vec<&str> = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"].to_vec();
    let values: Vec<u32> = [1,2,3,4,5,6,7,8,9].to_vec();


    for line in file.split('\n') {
        let mut found: bool = false;
        for j in 0..line.len() {
            let c: char = line.chars().nth(j).unwrap();
            if c.is_numeric() {
                let val: u32 = c.to_digit(10).unwrap();
                ans += val * 10;
                break;
            }
            else {
                for k in 0..9 {
                    if check(line.to_string(), number_list[k].to_string(), j as u32) {
                        let val: u32 = values[k];
                        ans += val * 10;
                        found = true;
                        break;
                    }
                }
                if found {
                    break;
                }
            }
        }
        found = false;
        for j in 0..line.len() {
            let c: char = line.chars().nth(line.len()-1-j).unwrap();
            if c.is_numeric() {
                let val: u32 = c.to_digit(10).unwrap();
                ans += val;
                break;
            }
            else {
                for k in 0..9 {
                    if check(line.to_string(), number_list[k].to_string(), (line.len() - j) as u32 - 1 ) {
                        let val: u32 = values[k];
                        ans += val;
                        found = true;
                        break;
                    }
                }
                if found {
                    break;
                }
            }
        }
    }
    println!("{}", ans);
}

fn main() {
    part1();
    part2();
}
