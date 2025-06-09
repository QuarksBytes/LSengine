use colour::*;

fn _foo() {
    let err: Result<(), u8> = Err(1);
    yellow_ln!("Failed on {}", 9);
    print!("Error details: ");
    dark_red_ln_bold!("{:?}", err);
}

fn main() {
    grey!("grey");
    grey_ln!("grey");
    grey_ln_bold!("bold grey");
    dark_grey_ln!("dark grey");
    dark_grey_ln_bold!("bold dark grey");
    red_ln!("red");
    red_ln_bold!("bold red");
    dark_red_ln!("dark red");
    dark_red_ln_bold!("bold dark red");
    green_ln!("green");
    green_ln_bold!("bold green");
    dark_green_ln!("dark green");
    dark_green_ln_bold!("bold dark green");
    yellow_ln!("yellow");
    yellow_ln_bold!("bold yellow");
    dark_yellow_ln!("dark yellow");
    dark_yellow_ln_bold!("bold dark yellow");
    blue_ln!("blue");
    blue_ln_bold!("bold blue");
    dark_blue_ln!("dark blue");
    dark_blue_ln_bold!("bold dark blue");
    magenta_ln!("magenta");
    magenta_ln_bold!("bold magenta");
    dark_magenta_ln!("dark magenta");
    dark_magenta_ln_bold!("bold dark magenta");
    cyan_ln!("cyan");
    cyan_ln_bold!("bold cyan");
    dark_cyan_ln!("dark cyan");
    dark_cyan_ln_bold!("bold dark cyan");
    black_ln!("black");
    black_ln_bold!("bold black");
    white_ln!("white");
    white_ln_bold!("bold white");
    println!("default colour");
    println_bold!("bold default colour");
}