use rand::prelude::*;
use std::fs::File;
use std::io;
use std::io::prelude::*;

fn main() -> io::Result<()> {
    let mut f = File::create("datasets/test/foo.txt")?;
    let secret_number = rand::thread_rng().gen_range(1..=100);
    f.write_all(b"{secret_number}")?; // needs to be b"" to convert the string slice (&str) to byte
                                      // slice, which isn't required to be valid UTF8. this string
                                      // type is used in OS operations
    Ok(())
}

// fn main() -> io::Result<()> {
//     let mut f = File::open("foo.txt")?;
//     let mut buffer = [0; 10];
//
//     // read up to 10 bytes
//     let n = f.read(&mut buffer)?;
//
//     println!("The bytes: {:?}", &buffer[..n]);
//     Ok(())
// }
