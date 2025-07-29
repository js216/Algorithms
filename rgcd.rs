mod utils;

fn gcd(mut u: i32, mut v: i32) -> i32 {
    while u > 0 {
        if u < v {
            let t = u;
            u = v;
            v = t;
        }
        u = u - v;
    }
    v
}

fn main() {
    loop {
        let pair = utils::read_stdin(2);
        if pair.len() < 2 {
            break;
        }
        let (x, y) = (pair[0], pair[1]);
        let g = gcd(x, y);
        println!("{x} {y} {g}");
    }
}
