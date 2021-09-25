use std::collections::BTreeMap;

const A: u64 = 0;
const E: u64 = 1;
const F: u64 = 2;
const R: u64 = 3;

const LETTERS: [u64; 4] = [A, E, F, R];

const FREE: u64 = (F << 6) | (R << 4) | (E << 2) | E;
const FARE: u64 = (F << 6) | (A << 4) | (R << 2) | E;
const AREA: u64 = (A << 6) | (R << 4) | (E << 2) | A;
const REEF: u64 = (R << 6) | (E << 4) | (E << 2) | F;

const KEYWORDS: [u64; 4] = [FREE, FARE, AREA, REEF];

fn main() {
    let mut words = BTreeMap::new();
    words.insert((0, 0), 1);
    for length in 1..31 {
        let mut next = BTreeMap::new();
        for ((mask, suffix), count) in words.into_iter() {
            for &letter in LETTERS.iter() {
                let next_word = (suffix << 2) | letter;
                let next_suffix = next_word & ((1 << 8) - 1);

                match KEYWORDS
                    .iter()
                    .enumerate()
                    .find(|&(_, &keyword)| keyword == next_suffix)
                    .map(|(i, _)| i)
                {
                    Some(new_word_id) if length >= 4 => {
                        if mask & (1 << new_word_id) == 0 {
                            let next_mask = mask | (1 << new_word_id);
                            *next.entry((next_mask, next_suffix)).or_insert(0) += count;
                        }
                    }
                    _ => {
                        *next.entry((mask, next_suffix)).or_insert(0) += count;
                    }
                }
            }
        }

        let ans = next
            .iter()
            .filter(|&(&(mask, _), _)| mask == (1 << 4) - 1)
            .map(|(_, &count)| count)
            .sum::<usize>();
        words = next;
        eprintln!("length={} ans={}", length, ans);
    }
    //    naive(11);
}

fn decode_suffix(suffix: u64) -> String {
    let c = ['A', 'E', 'F', 'R'];
    let mut s = String::new();
    s.push(c[((suffix as usize) >> 6) & ((1 << 2) - 1)]);
    s.push(c[((suffix as usize) >> 4) & ((1 << 2) - 1)]);
    s.push(c[((suffix as usize) >> 2) & ((1 << 2) - 1)]);
    s.push(c[(suffix as usize) & ((1 << 2) - 1)]);
    s
}

fn naive(length: usize) {
    let mut words = vec![String::new()];
    for i in 0..length {
        let mut next = vec![];
        let mut ans = vec![];
        for mut word in words.into_iter() {
            for &c in ['F', 'E', 'R', 'A'].iter() {
                word.push(c);

                let mut fare = 0;
                let mut free = 0;
                let mut area = 0;
                let mut reef = 0;
                if word.len() >= 4 {
                    for i in 0..(word.len() - 3) {
                        if &word[i..(i + 4)] == "FARE" {
                            fare += 1;
                        }
                        if &word[i..(i + 4)] == "AREA" {
                            area += 1;
                        }
                        if &word[i..(i + 4)] == "FREE" {
                            free += 1;
                        }
                        if &word[i..(i + 4)] == "REEF" {
                            reef += 1;
                        }
                    }
                }

                if fare <= 1 && free <= 1 && area <= 1 && reef <= 1 {
                    next.push(word.clone());
                }
                if fare == 1 && free == 1 && area == 1 && reef == 1 {
                    ans.push(word.clone());
                }

                word.pop();
            }
        }
        words = next;
        if i == length - 1 {
            for word in ans.into_iter() {
                println!("{}", &word[(length - 4)..length]);
            }
        }
    }
}