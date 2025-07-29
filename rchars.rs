// 4. Write a function int convert () that reads a decimal number one character (digit) at a time,
// terminated by a blank, and returns the value of that number.

mod utils;

fn main() {
    let mut x = 0;
    loop {
        let num = utils::read_stdin(1);
        if num.len() == 1 {
            x *= 10;
            x += num[0];
        } else {
            println!("{x}");
            return;
        }
    }
}
