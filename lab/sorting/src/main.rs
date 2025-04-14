use rand::prelude::*;
// use rand::rng;
use rand_chacha::ChaCha8Rng;
use std::cmp::Reverse;
use std::fs::create_dir_all;
use std::fs::File;
use std::io;
use std::io::prelude::*;
use std::io::BufWriter;
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
    const DATA_PATH: &str = r"./dataset";
    const SCALAR: u16 = 4000;
    const ELEMENT_COUNT: u8 = 15;
    const SEED: u64 = 346780;

    let mut rand_nums = [SEED as u32; ELEMENT_COUNT as usize * SCALAR as usize];
    let mut rng = ChaCha8Rng::seed_from_u64(SEED);

    for i in 1..=ELEMENT_COUNT {
        let mut filepath = PathBuf::from(DATA_PATH); // possibly have to fix due to borrow checker
        let arr_len = SCALAR as usize * i as usize;
        let slice = &mut rand_nums[0..arr_len];
        let mut set = "constant";
        let _ = create_dir_all(format!("{DATA_PATH}/{set}"));
        filepath.push(set);
        {
            filepath = filepath.clone();
            filepath.push(format!("{i}"));
            let display = filepath.display();
            let mut file = match File::create(filepath.as_path()) {
                Err(why) => panic!("couldn't create {}: {}", display, why),
                Ok(file) => file,
            };
            slice
                .iter()
                .try_for_each(|&num| writeln!(file, "{}", num))?;
            filepath.pop();
        }
        filepath.pop();
        // slice.iter_mut().for_each(|x| *x = rng.random());
        // let mut set = "random";
        // let _ = create_dir_all(format!("{DATA_PATH}/{set}"));
        // filepath.push(set);
        // {
        //     filepath = filepath.clone();
        //     filepath.push(format!("{i}"));
        //     let display = filepath.display();
        //     let mut file = match File::create(filepath.as_path()) {
        //         Err(why) => panic!("couldn't create {}: {}", display, why),
        //         Ok(file) => file,
        //     };
        //     slice
        //         .iter()
        //         .try_for_each(|&num| writeln!(file, "{}", num))?;
        //     filepath.pop();
        // }
        // filepath.pop();
        // set = "A_shaped";
        // let _ = create_dir_all(format!("{DATA_PATH}/{set}"));
        // filepath.push(set);
        // {
        //     // A shaped
        //     filepath = filepath.clone();
        //     filepath.push(format!("{i}"));
        //     let display = filepath.display();
        //     let mut file = match File::create(filepath.as_path()) {
        //         Err(why) => panic!("couldn't create {}: {}", display, why),
        //         Ok(file) => file,
        //     };
        //     slice[..arr_len / 2].sort_unstable();
        //     slice[arr_len / 2..].sort_unstable_by_key(|w| Reverse(*w));
        //     slice
        //         .iter()
        //         .try_for_each(|&num| writeln!(file, "{}", num))?;
        //     filepath.pop();
        // } // V shaped
        // filepath.pop();
        // set = "V_shaped";
        // let _ = create_dir_all(format!("{DATA_PATH}/{set}"));
        // filepath.push(set);
        // {
        //     filepath = filepath.clone();
        //     filepath.push(format!("{i}"));
        //     let display = filepath.display();
        //     let mut file = match File::create(filepath.as_path()) {
        //         Err(why) => panic!("couldn't create {}: {}", display, why),
        //         Ok(file) => file,
        //     };
        //     slice[..arr_len / 2].sort_unstable_by_key(|w| Reverse(*w));
        //     slice[arr_len / 2..].sort_unstable();
        //     slice
        //         .iter()
        //         .try_for_each(|&num| writeln!(file, "{}", num))?;
        //     filepath.pop();
        // }
        // filepath.pop();
        // set = "ascending";
        // let _ = create_dir_all(format!("{DATA_PATH}/{set}"));
        // filepath.push(set);
        // {
        //     filepath = filepath.clone();
        //     filepath.push(format!("{i}"));
        //     let display = filepath.display();
        //     let mut file = match File::create(filepath.as_path()) {
        //         Err(why) => panic!("couldn't create {}: {}", display, why),
        //         Ok(file) => file,
        //     };
        //     slice.sort();
        //     slice
        //         .iter()
        //         .try_for_each(|&num| writeln!(file, "{}", num))?;
        //     filepath.pop();
        // }
        // filepath.pop();
        // set = "descending";
        // let _ = create_dir_all(format!("{DATA_PATH}/{set}"));
        // filepath.push(set);
        // {
        //     filepath = filepath.clone();
        //     filepath.push(format!("{i}"));
        //     let display = filepath.display();
        //     let mut file = match File::create(filepath.as_path()) {
        //         Err(why) => panic!("couldn't create {}: {}", display, why),
        //         Ok(file) => file,
        //     };
        //     slice.sort_by_key(|w| Reverse(*w));
        //     slice
        //         .iter()
        //         .try_for_each(|&num| writeln!(file, "{}", num))?;
        //     filepath.pop();
        // }
        // filepath.pop();
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
