use std::process::exit;
use is_root::is_root;

fn cake_bake(layers: i32, candles_arg: i32, candle_height: i32, cake_width: i32) {

    let mut candles = candles_arg;

    let cake_recipe = "\nTo make a simple cake, you will need some flour, sugar, eggs, and butter.\n1. Mix the flour and sugar together in a large bowl.\n2. In another bowl, beat the eggs and then mix them with melted butter.\n3. Combine the egg mixture with the flour mixture and stir until smooth.\n4. Pour the batter into a greased baking pan.\n5. Bake in a preheated oven until the cake is golden and a toothpick inserted into the center comes out clean.\n6. Let it cool before serving. Enjoy your cake!\n\n";
    let even_layer = "#/".repeat((cake_width / 2) as usize);
    let odd_layer = "/#".repeat((cake_width / 2) as usize);
    let mut cake = String::new();

    let spaces = candles - 1;
    let total_spacing = cake_width - candles;
    let space_between_candles = if spaces > 0 { total_spacing / spaces } else { 0 };

    let candle_top = "*";
    let candle_stick = "|";

    // Add candle tops
    for i in 0..cake_width as i32{
        if i % (space_between_candles + 1) == 0 && candles > 0 {
            cake.push_str(candle_top);
            candles -= 1; 
        } else {
            cake += " ";
        }
    }
    // Add candle sticks
    cake.push_str("\n");

    for _i in 0..candle_height as i32{
        for j in 0..cake_width as i32 {
            if j % (space_between_candles + 1) == 0 {
                cake.push_str(candle_stick);
                candles -= 1; 
            } else {
                cake += " ";
            }
        }
        cake.push_str("\n");
    }

    // Add cake layers
    for i in 0..layers{
        if i % 2 == 0 {
            cake.push_str(&even_layer);
        } else {
            cake.push_str(&odd_layer);
        }
        cake.push_str("\n");
    }

    println!("\n{}\n\n{}", cake_recipe, cake);
}   

fn main() {
    // Make sure the user is root
    if !is_root() {
        println!("You must be root to run this program.");
        exit(1);
    }
    println!("{}\n\n",users::get_current_uid());


    // Get args and pass to cake_bake
    

    // Default values
    let mut layers = 3;
    let mut candles = 4;
    let mut candle_height = 3;
    let mut cake_width = 16;


    // Parse aruments
    let mut args: Vec<String> = std::env::args().collect();
    args.remove(0);
    
    for mut i in 0..args.len() {
        let arg = args[i].to_string();
        let pre = &arg[0..1];

        if pre == "-"{
            let suff = &arg[1..];
            match suff {
                "l" => {
                    layers = args[i+1].parse().unwrap();
                },
                "c" => {
                    candles = args[i+1].parse().unwrap();
                },
                "h" => {
                    candle_height = args[i+1].parse().unwrap();
                },
                "w" => {
                    cake_width = args[i+1].parse().unwrap();
                },
                _ => {
                    // Handle unknown argument
                    println!("Unknown argument: {}", suff);
                    println!("Usage: cake_bake [-l layers] [-c candles] [-h candle_height] [-w cake_width]");
                    exit(1);
                }
            }
            i += 1;
        }
    }
    cake_bake(layers, candles, candle_height, cake_width)
}
