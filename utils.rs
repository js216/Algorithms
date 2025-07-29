use std::io::BufRead;

pub fn read_stdin(n: usize) -> Vec<i32> {
    let stdin = std::io::stdin();
    let mut numbers = Vec::new();

    for line in stdin.lock().lines() {
        let line = line.expect("Failed to read line");
        for token in line.split_whitespace() {
            if let Ok(num) = token.parse::<i32>() {
                numbers.push(num);
                if numbers.len() == n {
                    return numbers;
                }
            } else {
                eprintln!("Ignoring invalid input: {}", token);
            }
        }
    }

    numbers
}
