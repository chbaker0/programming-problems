fn fifth(n: u32) -> u32 {
    (n*n)*(n*n)*n
}

fn main() {
    let mut sum = 0;

    for a in 1..10 {
        for b in 1..a+1 {
            for c in 0..b+1 {
                for d in 0..c+1 {
                    for e in 0..d+1 {
                        let digit_sum = fifth(a) + fifth(b) + fifth(c) + fifth(d) + fifth(e);
                        let num = e*10000 + d*1000 + c*100 + b*10 + a;
                        println!("{} {}", digit_sum, num);
                        if num == digit_sum {
                            sum += num;
                        }
                    }
                }
            }
        }
    }

    println!("{}", sum);
}
