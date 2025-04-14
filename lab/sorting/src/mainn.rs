// use rand::prelude::*;
// // use rand::rng;
// use rand_chacha::ChaCha8Rng;
// use std::cmp::Reverse;
// use std::fs::create_dir_all;
// use std::fs::File;
// use std::io;
// use std::io::prelude::*;
// use std::io::BufWriter;
// use std::io::Lines;
// use std::path::Path;
// use std::path::PathBuf;
// // use std::io::prelude::*;
//
// // fn writetofile() -> io::Result<()> {
// //     Ok(())
// // }
// //
// // fn parseinputdata() -> io::Result<()> {
// //     Ok(())
// // }
// //
// // fn generatedata() {}
//
// fn main() -> io::Result<()> {
//     // let mut f = File::create("datasets/test/foo.txt")?;
//     const PATH: Path = Path::new(r"../dataset/random/1");
//     let v = Vec<u32> = Vec::new();
//     file!Lines
//
//
//     Ok(())
// }

use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;
use std::time::Instant;

/// Reads integers from a file, one per line.
fn read_numbers_from_file(filename: &str) -> io::Result<Vec<i32>> {
    let path = Path::new(filename);
    let file = File::open(path)?;
    let buffered = io::BufReader::new(file);

    let mut numbers = Vec::new();
    for line in buffered.lines() {
        let line = line?;
        if let Ok(num) = line.trim().parse::<i32>() {
            numbers.push(num);
        }
    }
    Ok(numbers)
}

/// In-place quicksort implementation.
fn quicksort(arr: &mut [i32]) {
    if arr.len() <= 1 {
        return;
    }
    let pivot_index = partition(arr);
    let (left, right) = arr.split_at_mut(pivot_index);
    quicksort(left);
    quicksort(&mut right[1..]);
}

/// Partition helper function.
fn partition(arr: &mut [i32]) -> usize {
    let len = arr.len();
    let pivot_index = len - 1;
    let pivot = arr[pivot_index];
    let mut i = 0;

    for j in 0..pivot_index {
        if arr[j] <= pivot {
            arr.swap(i, j);
            i += 1;
        }
    }
    arr.swap(i, pivot_index);
    i
}

fn main() {
    let filename = "data.txt";
    println!("Reading data from: {}", filename);

    match read_numbers_from_file(filename) {
        Ok(mut data) => {
            println!("Read {} numbers.", data.len());

            let start = Instant::now();
            quicksort(&mut data);
            let duration = start.elapsed();

            println!("Sorted data: {:?}", data);
            println!("Sorting took: {:?}", duration);
        }
        Err(e) => {
            eprintln!("Error reading file: {}", e);
        }
    }
}

// Zaimplementuj algorytm Quicksort w wersji rekurencyjnej z różnymi sposobami wyboru klucza:
// skrajnie prawego, środkowego co do położenia, losowego.
// Utwórz wykres porównujący efektywność działania algorytmu w zależności od wyboru klucza dla A-kszytałtnego ciągu wejściowego.
