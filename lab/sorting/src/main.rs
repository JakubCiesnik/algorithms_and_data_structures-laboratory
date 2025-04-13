use rand::prelude::*;
use rand::rng;
use rand_chacha::ChaCha8Rng;
use std::cmp::Reverse;
use std::fs::File;
use std::io;
use std::io::prelude::*;
use std::path::PathBuf;
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
    const DATA_PATH: &str = r"./dataset/test";
    const SCALAR: u16 = 20;
    const ELEMENT_COUNT: u8 = 20;
    const SEED: u64 = 346780;

    let mut rand_nums = [0u32; ELEMENT_COUNT as usize * SCALAR as usize];
    let mut rng = ChaCha8Rng::seed_from_u64(SEED);

    for i in 1..=ELEMENT_COUNT {
        let mut filepath = PathBuf::from(DATA_PATH); // possibly have to fix due to borrow checker
        filepath.push(format!("random{i}"));
        let display = filepath.display();

        let arr_len = SCALAR as usize * i as usize;
        let slice = &mut rand_nums[0..arr_len];
        slice.iter_mut().for_each(|x| *x = rng.random());

        let mut file = match File::create(filepath.as_path()) {
            Err(why) => panic!("couldn't create {}: {}", display, why),
            Ok(file) => file,
        };
        slice[..ELEMENT_COUNT as usize * i as usize / 2].sort_unstable();
        slice[ELEMENT_COUNT as usize * i as usize / 2..].sort_unstable_by_key(|w| Reverse(*w));
        slice
            .iter()
            .try_for_each(|&num| writeln!(file, "{}", num))?;

        // slice_a.sort_unstable_by_key(|w| Reverse(*w));
        // slice_b.sort_unstable_by_key(|w| Reverse(*w));
        // match file.write_all(slice) {
        //     Err(why) => panic!("couldn't write to {}: {}", display, why),
        //     Ok(_) => println!("successfully wrote to {}", display),
        // }
    }

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
