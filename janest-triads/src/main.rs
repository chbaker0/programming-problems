use std::collections::BTreeSet;
use std::convert::TryInto;
use std::iter::repeat;
use std::iter::Iterator;
use std::vec::Vec;

fn triangle_size(n: u32) -> u32 {
    return n * (n + 1) / 2;
}

fn index_triangle(r: u32, i: u32) -> usize {
    assert!(1 <= r);
    assert!(1 <= i && i <= r);
    let num_above = triangle_size(r - 1);
    return (num_above + i - 1).try_into().expect("overflow");
}

fn bruteforce_impl(labels: Vec<u32>, r: u32, i: u32, next_label: u32) -> Option<Vec<u32>> {
    assert!(1 <= r);
    assert!(1 <= i);
    assert!(triangle_size(r) <= labels.len().try_into().unwrap());

    if i > r {
        return bruteforce_impl(labels, r + 1, 1, next_label);
    }

    // Only hit on the first call:
    if r == 1 {
        assert!(i == 1);
        let mut first_labels = labels;
        // The tip of the triangle and the 2 dots in the row below it must form
        // a triad, since the tip can't be matched with any other dots. Label
        // them 1.
        first_labels[index_triangle(1, 1)] = 1;
        first_labels[index_triangle(2, 1)] = 1;
        first_labels[index_triangle(2, 2)] = 1;

        return bruteforce_impl(first_labels, 3, 1, 2);
    }

    // For the last row, just check if all dots are grouped. If there are any
    // ungrouped ones, we fail.
    if triangle_size(r) == labels.len().try_into().unwrap() {
        assert!(i == 1);
        for i in 1..r + 1 {
            if labels[index_triangle(r, i)] == 0 {
                return None;
            }
        }
        return Some(labels);
    }

    // Loop invariant:
    // (1) all positions before row `r` offset `i` are grouped
    // (2) all existing groups are valid triads
    //
    // The loop works dot by dot, row by row down from the top. At every
    // position the loop may do one of the following:
    // (a) group the current dot, the dot to the right, and the dot below
    // (b) group the current dot, the bottom left, and the bottom right dots
    // (c) detect an impossible case and return failure

    let cur_label = labels[index_triangle(r, i)];
    let bottom_left_label = labels[index_triangle(r + 1, i)];

    if cur_label == 0 {
        if bottom_left_label == 0 {
            // Try grouping with the bottom left and right dots.
            let mut candidate = labels.clone();
            candidate[index_triangle(r, i)] = next_label;
            candidate[index_triangle(r + 1, i)] = next_label;
            candidate[index_triangle(r + 1, i + 1)] = next_label;
            let result = bruteforce_impl(candidate, r, i + 1, next_label + 1);
            if result.is_some() {
                return result;
            }
        }
        if i < r && labels[index_triangle(r, i + 1)] == 0 {
            // Try grouping with the dot to the right and the dot below us.
            let mut candidate = labels.clone();
            candidate[index_triangle(r, i)] = next_label;
            candidate[index_triangle(r, i + 1)] = next_label;
            candidate[index_triangle(r + 1, i + 1)] = next_label;
            let result = bruteforce_impl(candidate, r, i + 2, next_label + 1);
            if result.is_some() {
                return result;
            }
        }

        // If we haven't returned yet, there is no possible grouping.
        return None;
    }

    // If the current dot is labeled, we don't need to do anything.
    return bruteforce_impl(labels, r, i + 1, next_label);
}

#[allow(dead_code)]
fn bruteforce(n: u32) -> Option<Vec<u32>> {
    assert!(n > 0);
    let init = repeat(0)
        .take((n * (n + 1) / 2).try_into().unwrap())
        .collect();

    return bruteforce_impl(init, 1, 1, 1);
}

#[allow(dead_code)]
fn print_triangle(n: u32, labels: &Vec<u32>) {
    assert_eq!(triangle_size(n), labels.len().try_into().unwrap());

    for r in 1..n + 1 {
        for i in 1..r + 1 {
            print!("{:2} ", labels[index_triangle(r, i)]);
        }
        println!();
    }
}

fn bit_is_set(x: u64, i: usize) -> bool {
    assert!(i < 64);
    return x & (1 << i) > 0;
}

fn set_bit(x: u64, i: usize) -> u64 {
    assert!(i < 64);
    return x | (1 << i);
}

fn clear_bit(x: u64, i: usize) -> u64 {
    assert!(i < 64);
    return x & !(1 << i);
}

fn reverse_row(row_num: usize, row_desc: u64) -> u64 {
    return row_desc.reverse_bits() >> (64 - row_num);
}

fn enumerate_candidates_above_impl(
    row: usize,
    row_desc: u64,
    candidates: &mut Vec<u64>,
    cur_requirements: u64,
    offset: usize,
) {
    if offset == row {
        return candidates.push(cur_requirements);
    }

    if !bit_is_set(row_desc, offset) {
        // If we want this bit to be unset in this row, we make no changes to
        // the requirements on the above row since it will share no triads with
        // the above. All bits above are assumed set unless otherwise required.
        return enumerate_candidates_above_impl(
            row,
            row_desc,
            candidates,
            cur_requirements,
            offset + 1,
        );
    }

    if offset >= 1
        && bit_is_set(cur_requirements, offset - 1)
        && bit_is_set(cur_requirements, offset)
    {
        // Try grouping with the top two dots if it is available.
        let new_requirements = clear_bit(clear_bit(cur_requirements, offset - 1), offset);
        enumerate_candidates_above_impl(row, row_desc, candidates, new_requirements, offset + 1);
    }

    if offset < row - 1 && bit_is_set(row_desc, offset + 1) && bit_is_set(cur_requirements, offset)
    {
        // Try grouping with the right dot and shared dot above.
        let new_requirements = clear_bit(cur_requirements, offset);
        enumerate_candidates_above_impl(row, row_desc, candidates, new_requirements, offset + 2);
    }
}

fn enumerate_candidates_above(row: usize, row_desc: u64) -> Vec<u64> {
    assert!(row <= 64);
    let mut candidates = Vec::new();
    enumerate_candidates_above_impl(row, row_desc, &mut candidates, (1 << (row - 1)) - 1, 0);
    return candidates;
}

fn is_row_possible(row: usize, row_desc: u64, memo: &mut Vec<BTreeSet<u64>>) -> bool {
    assert!(row < 64, "{}", row);
    assert!(row_desc < 1 << row, "{} {}", row_desc, row);

    //    println!("{} {:0>2$b}", row, row_desc, row);
    if memo.len() < row {
        memo.resize(row, BTreeSet::new());
    }

    if memo[row - 1].contains(&row_desc) || memo[row - 1].contains(&reverse_row(row, row_desc)) {
        return true;
    } else if row == 1 {
        return row_desc == 1;
    } else if row == 2 {
        return row_desc == 0b11;
    }

    let candidates = enumerate_candidates_above(row, row_desc);
    for c in candidates {
        if is_row_possible(row - 1, c, memo) {
            memo[row - 1].insert(row_desc);
            return true;
        }
    }

    return false;
}

fn main() {
    let mut memo = Vec::new();

    for r in 3..40 {
        for x in 0..((1 << r) - 1) {
            is_row_possible(r, x, &mut memo);
        }
        println!("{}: {}", r, memo[r - 1].len());
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn indexing() {
        assert_eq!(index_triangle(1, 1), 0);
        assert_eq!(index_triangle(2, 1), 1);
        assert_eq!(index_triangle(2, 2), 2);
        assert_eq!(index_triangle(4, 3), 8);
    }
}
