#include "des.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <unordered_map>
#include <bitset>

// Define the constants
const int IP[64] = { /* Add the actual values here */ };
const int IIP[64] = { /* Add the actual values here */ };
const int EP[48] = { /* Add the actual values here */ };
const int P[32] = { /* Add the actual values here */ };
const int s_box[8][4][16] = { /* Add the actual values here */ };
const int shift_table[16] = { /* Add the actual values here */ };
const int PC_1[56] = { /* Add the actual values here */ };
const int PC_2[48] = { /* Add the actual values here */ };

// Function implementations
std::string hex_to_bin(const std::string& hex) {
    std::string bin = "";
    std::unordered_map<char, std::string> mp = {
        {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
        {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
        {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
        {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"},
        {'a', "1010"}, {'b', "1011"}, {'c', "1100"}, {'d', "1101"},
        {'e', "1110"}, {'f', "1111"}
    };

    for (char c : hex) {
        if (mp.find(c) != mp.end()) {
            bin += mp[c];
        } else {
            std::cerr << "Invalid hex character: " << c << std::endl;
            exit(1);
        }
    }

    return bin;
}

std::string bin_to_hex(const std::string& bin) {
    assert(bin.length() % 64 == 0);
    std::string hex = "";
    std::unordered_map<std::string, std::string> mp = {
        {"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"},
        {"0100", "4"}, {"0101", "5"}, {"0110", "6"}, {"0111", "7"},
        {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"},
        {"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"}
    };

    for (size_t i = 0; i < bin.length(); i += 4) {
        std::string chunk = bin.substr(i, 4);
        hex += mp[chunk];
    }

    return hex;
}

std::string bin_to_dec(const std::string& bin) {
    std::string dec = "";
    std::unordered_map<std::string, std::string> mp;
    mp["00"] = "0";
    mp["01"] = "1";
    mp["10"] = "2";
    mp["11"] = "3";
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "10";
    mp["1011"] = "11";
    mp["1100"] = "12";
    mp["1101"] = "13";
    mp["1110"] = "14";
    mp["1111"] = "15";
    dec = mp[bin];
    return dec;
}

std::string dec_to_bin(const std::string& dec) {
    std::string bin = "";
    std::unordered_map<std::string, std::string> mp;
    mp["0"] = "0000";
    mp["1"] = "0001";
    mp["2"] = "0010";
    mp["3"] = "0011";
    mp["4"] = "0100";
    mp["5"] = "0101";
    mp["6"] = "0110";
    mp["7"] = "0111";
    mp["8"] = "1000";
    mp["9"] = "1001";
    mp["10"] = "1010";
    mp["11"] = "1011";
    mp["12"] = "1100";
    mp["13"] = "1101";
    mp["14"] = "1110";
    mp["15"] = "1111";
    bin = mp[dec];
    return bin;
}

std::string XOR(const std::string& s1, const std::string& s2) {
    assert(s1.length() == s2.length());
    std::string new_string = "";
    for (unsigned int i = 0; i < s1.length(); i++) {
        if (s1[i] == s2[i])
            new_string += "0";
        else
            new_string += "1";
    }
    return new_string;
}

std::string apply_s_box(const std::string& bit_stream) {
    assert(bit_stream.length() == 48);
    std::string new_text, text_segment, row_val, left, right, col_val = "";
    int select_box, selected_val, row_val_dec, col_val_dec = 0;
    for (unsigned int i = 0; i < 48; i += 6) {
        left = bit_stream.substr(i, 1);
        right = bit_stream.substr(i + 5, 1);
        row_val = left + right;
        row_val_dec = stoi(bin_to_dec(row_val));
        col_val = bit_stream.substr(i + 1, 4);
        col_val_dec = stoi(bin_to_dec(col_val));
        select_box = i / 6;
        selected_val = s_box[select_box][row_val_dec][col_val_dec];
        text_segment = dec_to_bin(std::to_string(selected_val));
        new_text += text_segment;
    }
    return new_text;
}

std::string apply_P(const std::string& bit_stream) {
    std::string new_text = "";
    for (unsigned int i = 0; i < 32; i++)
        new_text += bit_stream[P[i] - 1];
    return new_text;
}

std::string apply_IP(const std::string& plaintext) {
    std::string new_text = "";
    for (unsigned int i = 0; i < 64; i++) {
        new_text += plaintext[IP[i] - 1];
    }
    return new_text;
}

std::string apply_IIP(const std::string& bit_stream) {
    std::string new_text = "";
    for (unsigned int i = 0; i < 64; i++)
        new_text += bit_stream[IIP[i] - 1];
    return new_text;
}

std::string apply_EP(const std::string& right) {
    std::string new_text = "";
    for (unsigned int i = 0; i < 48; i++) {
        new_text += right[EP[i] - 1];
    }
    return new_text;
}

std::string apply_PC1(const std::string& key) {
    std::string new_key = "";
    for (unsigned int i = 0; i < 56; i++) {
        new_key += key[PC_1[i] - 1];
    }
    return new_key;
}

std::vector<std::string> generate_subkeys(const std::string& key) {
    std::vector<std::string> subkeys;
    std::string left, right, newLeft, newRight, temp_key, new_key = "";
    for (unsigned int i = 0; i < 16; i++) {
        if (i == 0) {
            left = key.substr(0, 28);
            right = key.substr(28, 28);
        } else {
            left = temp_key.substr(0, 28);
            right = temp_key.substr(28, 28);
        }
        if (shift_table[i] == 1) {
            newLeft = left.substr(1, 27) + left.substr(0, 1);
            newRight = right.substr(1, 27) + right.substr(0, 1);
        } else {
            newLeft = left.substr(2, 26) + left.substr(0, 2);
            newRight = right.substr(2, 26) + right.substr(0, 2);
        }
        temp_key = newLeft + newRight;
        new_key = "";
        for (int j = 0; j < 48; j++) {
            new_key += temp_key[PC_2[j] - 1];
        }
        subkeys.push_back(new_key);
    }
    return subkeys;
}

std::string text_to_bin(const std::string& text) {
    std::string bin = "";
    for (char c : text) {
        bin += std::bitset<8>(static_cast<unsigned char>(c)).to_string();
    }
    return bin;
}

std::string bin_to_text(const std::string& bin) {
    std::string text = "";
    size_t len = bin.length();
    while (len >= 8 && bin.substr(len - 8, 8) == "00000000") {
        len -= 8;
    }
    for (size_t i = 0; i < len; i += 8) {
        std::bitset<8> bits(bin.substr(i, 8));
        text += static_cast<char>(bits.to_ulong());
    }
    return text;
}

std::string read_data(const std::string& fileName) {
    std::ifstream fileIn(fileName);
    if (!fileIn.is_open()) {
        std::cerr << "Failed to open input file. Exiting...\n";
        exit(1);
    }
    std::string content((std::istreambuf_iterator<char>(fileIn)), std::istreambuf_iterator<char>());
    return content;
}

void write_data(const std::string& fileName, const std::string& data) {
    std::ofstream fileOut(fileName);
    if (!fileOut.is_open()) {
        std::cerr << "Failed to open output file. Exiting...\n";
        exit(1);
    }
    fileOut << data;
}

void perform_DES() {
    std::string fileName, key_hex, choice;
    std::cout << "Enter E for encryption or D for decryption: ";
    std::getline(std::cin, choice);
    std::cout << "Input the key in hexadecimal (16 hex characters): ";
    std::getline(std::cin, key_hex);
    std::cout << "Input the file name (e.g. data.txt): ";
    std::getline(std::cin, fileName);

    std::string input_data = read_data(fileName);
    std::string input_bin = (choice == "E") ? text_to_bin(input_data) : hex_to_bin(input_data);

    while (input_bin.length() % 64 != 0) {
        input_bin += "0";
    }

    std::string key_bin = hex_to_bin(key_hex);
    key_bin = apply_PC1(key_bin);
    std::vector<std::string> subkeys = generate_subkeys(key_bin);
    if (choice == "D") {
        std::reverse(subkeys.begin(), subkeys.end());
    }

    std::string output_bin = "";
    for (size_t i = 0; i < input_bin.length(); i += 64) {
        std::string block = input_bin.substr(i, 64);
        block = apply_IP(block);
        std::string left = block.substr(0, 32);
        std::string right = block.substr(32, 32);
        std::string result = round_function(left, right, subkeys);
        result = result.substr(32, 32) + result.substr(0, 32);
        result = apply_IIP(result);
        output_bin += result;
    }

    std::string output_data = (choice == "E") ? bin_to_hex(output_bin) : bin_to_text(output_bin);
    std::string outFile = (choice == "E") ? fileName + ".enc"
                                          : fileName.substr(0, fileName.find_last_of('.'));
    write_data(outFile, output_data);
    std::cout << "Output written to: " << outFile << std::endl;
}

std::string round_function(const std::string& left32, const std::string& right32, const std::vector<std::string>& subkeys) {
    std::string EP, EP_XOR_K, s_box, permute, left, previousLeft, right, encrypted = "";
    for (unsigned int i = 0; i < subkeys.size(); i++) {
        if (i == 0) {
            left = left32;
            right = right32;
        }
        EP = apply_EP(right);
        EP_XOR_K = XOR(EP, subkeys[i]);
        s_box = apply_s_box(EP_XOR_K);
        permute = apply_P(s_box);
        previousLeft = left;
        left = right;
        right = XOR(previousLeft, permute);
    }
    encrypted = left + right;
    return encrypted;
}
