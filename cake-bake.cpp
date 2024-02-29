#include <iostream>
#include <string>
#include <string_view>
#include <cmath>
#include <cstddef> //called implicitly for std::size_t


std::string operator*(const std::string_view s, std::size_t n) {
    std::string result;
    result.reserve(s.length()*n);
    for(size_t i = 0; i < n; ++i) {
        result += s;
    }
    return result;
}

std::string cake_bake(int layers = 3, int candles = 6, int candle_height = 2, int cake_width = 40) {
    std::string cakeRecipe = 
    "\nTo make a simple cake, you will need some flour, sugar, eggs, and butter.\n"
    "1. Mix the flour and sugar together in a large bowl.\n"
    "2. In another bowl, beat the eggs and then mix them with melted butter.\n"
    "3. Combine the egg mixture with the flour mixture and stir until smooth.\n"
    "4. Pour the batter into a greased baking pan.\n"
    "5. Bake in a preheated oven until the cake is golden and a toothpick inserted into the center comes out clean.\n"
    "6. Let it cool before serving. Enjoy your cake!\n\n";

    std::string layer1 = std::string_view("#/")*static_cast<std::size_t>(std::floor(cake_width/2));
    std::string layer2 = std::string_view("/#")*static_cast<std::size_t>(std::floor(cake_width/2));


    std::string cake = "";
    int cake_length = layer1.length();
    char candle_top = '*';
    std::string candle_layer = "|";
    
    // Adjust the calculation for equal spacing of candles, ensuring one at start and end
    int spaces = candles - 1; // Spaces between candles
    int total_spacing = cake_width - candles; // Total space to distribute between candles
    int space_between_candles = spaces > 0 ? total_spacing / spaces : 0; // Avoid division by zero


    // Add candle tops with equal spacing
    for (int i = 0; i < cake_width; i++) {
        if (i % (space_between_candles + 1) == 0 && candles > 0) {
            cake += candle_top;
            candles--; // Decrement candles after placing each to ensure correct placement
        } else {
            cake += " ";
        }
    }
    cake += "\n";

    // Add candle layers
    for (int j = 0; j < candle_height; j++) {
        for (int i = 0; i < cake_width; i++) {
            if (i % (space_between_candles + 1) == 0 && candles > 0) { // Use the initial candle count for reference if needed
                cake += candle_layer;
            } else {
                cake += " ";
            }
        }
        cake += "\n";
    }



    //Add layers
    for(int i = 0; i < layers*2; i++){
        if (i % 2 == 0){
            cake += layer1 + "\n";
        } else {
            cake += layer2 + "\n";
        }
    }

    std::cout << cakeRecipe << '\n';
    return cake;
}


int main(int argc, char const *argv[]) {
    int layers = 3;
    int candles = 6;
    int candle_height = 2;
    int cake_width = 40;

    for(int i = 0; i < argc; i++){ 
        char front = std::string(argv[i])[0];
        if (front == '-'){
            char option = std::string(argv[i])[1];
            switch(option){
                case 'l':
                    layers = std::stoi(argv[i+1]);
                    break;
                case 'c':
                    candles = std::stoi(argv[i+1]);
                    break;
                case 'h':
                    candle_height = std::stoi(argv[i+1]);
                    break;
                case 'w':
                    cake_width = std::stoi(argv[i+1]);
                    break;
            }
            i++;
        }
    }
    std::cout << cake_bake(layers, candles, candle_height, cake_width) << '\n';
    return 0;
}
