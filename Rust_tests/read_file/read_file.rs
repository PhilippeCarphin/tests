use std::fs::File;
use std::io::prelude::*;
use std::env;

fn main() -> std::io::Result<()> {

    let argv: Vec<String> = env::args().collect();
    // let mut filename = argv.remove(1);
    let mut file = File::open(argv[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    println!("{}", contents);
    // assert_eq!(contents, "Hello, world!");
    Ok(())
}
