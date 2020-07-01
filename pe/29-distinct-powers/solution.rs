use std::collections::BTreeSet;
use std::vec::Vec;

fn sieve(max: usize) -> Vec<usize> {
    let mut primes = Vec::new();

    let mut marks = Vec::new();
    marks.resize(max+1, false);
    marks[0] = true;
    marks[1] = true;

    for p in 2..max+1 {
        if marks[p] {
            continue;
        }

        primes.push(p);
        for m in (p*p..max+1).step_by(p) {
            marks[m] = true;
        }
    }

    primes
}

fn factorize(mut n: usize, primes: &[usize]) -> Vec<(usize, usize)> {
    let mut result = Vec::new();

    for p in primes {
        if n < 2 {
            return result;
        }

        let mut e = 0;
        while n % p == 0 {
            e += 1;
            n /= p;
        }

        if e > 0 {
            result.push((*p, e));
        }
    }

    result
}

fn main() {
    let primes = sieve(100);

    let mut seen = BTreeSet::new();

    for a in 2..101 {
        let a_factors = factorize(a, &primes);

        for b in 2..101 {
            let mut ab_factors = a_factors.clone();
            for (_, e) in &mut ab_factors {
                *e *= b;
            }
            seen.insert(ab_factors);
        }
    }

    println!("{}", seen.len());
}
