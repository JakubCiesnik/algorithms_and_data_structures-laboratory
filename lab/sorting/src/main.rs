use rand::prelude::*;
use rand::rng;
use std::fs::File;
use std::io;
// use std::io::prelude::*;

// fn writetofile() -> io::Result<()> {
//     Ok(())
// }
//
// fn parseinputdata() -> io::Result<()> {
//     Ok(())
// }
//
// fn generatedata() {}

fn main() -> io::Result<()> {
    // let mut f = File::create("datasets/test/foo.txt")?;
    const N: usize = 3200;
    let arr1: [u32; N] = rng().random();
    println!("{:?}", &arr1[..N]);

    // f.write_all(b"{secret_number}")?;
    // needs to be b"" to convert the string slice (&str) to byte
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
