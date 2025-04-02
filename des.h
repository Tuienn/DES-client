#ifndef DES_H
#define DES_H

#include <string>
#include <vector>

// Function prototypes
std::string hex_to_bin(const std::string& hex);
std::string bin_to_hex(const std::string& bin);
std::string bin_to_dec(const std::string& bin);
std::string dec_to_bin(const std::string& dec);
std::string XOR(const std::string& s1, const std::string& s2);
std::string apply_s_box(const std::string& bit_stream);
std::string apply_P(const std::string& bit_stream);
std::string apply_IP(const std::string& plaintext);
std::string apply_IIP(const std::string& bit_stream);
std::string apply_EP(const std::string& right);
std::string apply_PC1(const std::string& key);
std::string perform_DES(const std::string& key_hex = "", const std::string& fileName = "");
std::string round_function(const std::string& left32, const std::string& right32, const std::vector<std::string>& subkeys);
std::string read_data(const std::string& fileName);
void write_data(const std::string& fileName, const std::string& data);
std::vector<std::string> generate_subkeys(const std::string& key);
std::string text_to_bin(const std::string& text);
std::string bin_to_text(const std::string& bin);

#endif // DES_H
