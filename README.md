# Language
A programming language school project

# Code example

    fn nothing() {}

    fn square(a: float) -> float {
        return a * a
    }

    let u: float = .5

    // this is comment

    fn main() -> float {
        nothing()
        let a
        {
            a = square(2.) // this is inline comment
        }
        let mut b = square(1.)
        b = 1. + b * a
        return b * u
    }

The <i>main</i> return value is printed as the result

# Building
Clone the repo, then run
    
    cmake -DCMAKE_BUILD_TYPE=[debug/release] -B build/
    cmake --build build/

# Executing
Run

    ./build/src/language [filename]

for more info run

    ./build/src/language --help

