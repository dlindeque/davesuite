// dl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "cmdlineargs.h"
#include "..\dllib\dlencoding.h"
#include "..\dllib\basic_encoder.h"
#include "..\dllib\davesubst.h"
#include "..\dllib\aes.h"
#include "..\dllib\crypto.h"

void print_usage() {
    std::cout << "USAGE" << std::endl;
    std::cout << "dl.exe /mode:encrypt /encode_map:<mapfn> /pwd1:<pwd1> /pwd2:<pwd2> /out:<out filename> /in:<source filename>" << std::endl;
    std::cout << "  Encrypt the contents of <source filename>, writing to <out filename> using the map and passwords specified." << std::endl;
    std::cout << "  dl.exe /mode:encrypt /encode_map:\"c:\\test\\mapfile.txt\" /pwd1:\"Password 1\" /pwd2:\"Password 2\" /out:\"c:\\test\\out.txt\" /in:\"mymsg.txt\"" << std::endl;
    std::cout << "dl.exe /mode:decrypt /pwd1:<pwd1> /pwd2:<pwd2> /in:<source filename>" << std::endl;
    std::cout << "  Decrypts the contents of <source filename>, writing to console (for security reasons) using the passwords specified." << std::endl;
    std::cout << "  dl.exe /mode:decrypt /pwd1:\"Password 1\" /pwd2:\"Password 2\" /in:\"received.txt\"" << std::endl;
    std::cout << "dl.exe /mode:generate_map /words:<words filename> /out:<map filename>" << std::endl;
    std::cout << "  Generates a map file using the words in the words file specified." << std::endl;
    std::cout << "  dl.exe /mode:generate_map /words:\"c:\\test\\words.txt\" /out:\"c:\\test\\mapfile.txt\"" << std::endl;
    std::cout << "dl.exe /mode:validate_map /encode_map:<mapfn>" << std::endl;
    std::cout << "  Validates the map file." << std::endl;
    std::cout << "  dl.exe /mode:validate_map /encode_map:\"c:\\test\\mapfile.txt\"" << std::endl;
}

inline auto get_file_contents(const std::string &fn, bool &ok) -> std::string {
    std::ifstream in(fn.c_str(), std::ios::in | std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize((size_t)in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        if (contents.length() > 3 && contents[0] == '\xEF' && contents[1] == '\xBB' && contents[2] == '\xBF') {
            contents.erase(0, 3);
        }
        return contents;
    }
    else {
        std::cout << "Failure opening " << fn << " for input." << std::endl;
        ok = false;
        return "";
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "Dave Encoding Utility" << std::endl << std::endl;

    dave::cmdargmap args;
    dave::load_args(argc, argv, L"mode", args);
    dave::load_args(argc, argv, L"pwd1", args);
    dave::load_args(argc, argv, L"pwd2", args);
    dave::load_args(argc, argv, L"out", args);
    dave::load_args(argc, argv, L"in", args);
    dave::load_args(argc, argv, L"encode_map", args);
    dave::load_args(argc, argv, L"words", args);

    bool ok = true;
    auto mode = dave::get_single_mandatory_arg(args, "mode", ok);
    if (!ok) {
        print_usage();
        return 1;
    }

    if (_stricmp(mode.c_str(), "encrypt") == 0) {
        auto encode_map = dave::get_single_mandatory_arg(args, "encode_map", ok);
        auto pwd1 = dave::get_single_mandatory_arg(args, "pwd1", ok);
        auto pwd2 = dave::get_single_mandatory_arg(args, "pwd2", ok);
        auto out = dave::get_single_mandatory_arg(args, "out", ok);
        auto in = dave::get_single_mandatory_arg(args, "in", ok);
        if (ok) {
            // plain -> basic_encoder -> davesubst -> aes -> dlencode
            std::cout << "Encrypting your message.." << std::endl;
            std::cout << "Encode map = " << encode_map << std::endl;
            std::cout << "Reading " << in << std::endl;
            std::cout << "Writing " << out << std::endl;
            std::ofstream os(out);
            dave::dlencoder_map map(encode_map);
            std::string text = get_file_contents(in, ok);

            if (os && ok && map.is_valid()) {
                dave::basic_encoder benc;
                auto buf1 = benc.encode(text);
                dave::davesubst_encrypt::key_type key1;
                dave::davesubst_encrypt::key_factory_type()(pwd1, key1);
                dave::encryptor<dave::davesubst_encrypt> enc1(dave::davesubst_encrypt(), key1);
                auto buf2 = enc1(buf1);
                dave::aes_encrypt::key_type key2;
                dave::aes_encrypt::key_factory_type()(pwd2, key2);
                dave::encryptor<dave::aes_encrypt> enc2(dave::aes_encrypt(), key2);
                auto buf3 = enc2(buf2);

                dave::dlencoder enc(std::move(map));

                enc(buf3, os);
            }
        }
    }
    else if (_stricmp(mode.c_str(), "decrypt") == 0) {
        auto pwd1 = dave::get_single_mandatory_arg(args, "pwd1", ok);
        auto pwd2 = dave::get_single_mandatory_arg(args, "pwd2", ok);
        auto in = dave::get_single_mandatory_arg(args, "in", ok);
        if (ok) {
            // cyher -> dlencode -> aes -> davesubst -> basic_encoder
            std::cout << "Decrypting your message.." << std::endl;
            std::cout << "Reading " << in << std::endl;
            std::string text = get_file_contents(in, ok);

            std::ifstream is(in);

            if (ok && is) {

                dave::dldecoder dec;
                auto buf3 = dec(is);

                dave::aes_decrypt::key_type key2;
                dave::aes_decrypt::key_factory_type()(pwd2, key2);
                dave::decryptor<dave::aes_decrypt> dec2(dave::aes_decrypt(), key2);
                auto buf2 = dec2(buf3);

                dave::davesubst_decrypt::key_type key1;
                dave::davesubst_decrypt::key_factory_type()(pwd1, key1);
                dave::decryptor<dave::davesubst_decrypt> dec1(dave::davesubst_decrypt(), key1);
                auto buf1 = dec1(buf2);

                dave::basic_encoder benc;
                std::cout << std::endl << "---------------------------------------------------------------" << std::endl << benc.decode(buf1) << std::endl << "---------------------------------------------------------------" << std::endl;
            }
        }
    }
    else if (_stricmp(mode.c_str(), "generate_map") == 0) {
        auto words = dave::get_single_mandatory_arg(args, "words", ok);
        auto out = dave::get_single_mandatory_arg(args, "out", ok);
        if (ok) {
            std::cout << "Gerating an encoding map.." << std::endl;
            std::cout << "Words file ='" << words << "'." << std::endl;
            std::cout << "Writing to '" << out << "'." << std::endl;
            auto map = dave::dlencoder_map::build_encoding_map(words);
            std::cout << "Validating the generated map..." << std::endl;
            if (!map.is_valid()) {
                std::cout << "The words file specified does not generate a valid map. Please specify more words." << std::endl;
            }
            else {
                std::cout << "Valid! Saving the map file..." << std::endl;
                if (!map.save(out)) {
                    std::cout << "Failure saving the map file" << std::endl;
                }
                else {
                    std::cout << "Map file generated" << std::endl;
                }
            }
        }
    }
    else if (_stricmp(mode.c_str(), "validate_map") == 0) {
        auto encode_map = dave::get_single_mandatory_arg(args, "encode_map", ok);
        if (ok) {
            std::cout << "Validating an encoding map.." << std::endl;
            std::cout << "Map file = '" << encode_map << "'." << std::endl;
            std::cout << "Reading the map file.." << std::endl;
            dave::dlencoder_map map(encode_map);
            std::cout << "Validating.." << std::endl;
            if (!map.is_valid()) {
                std::cout << "The map file is not a valid encoding map." << std::endl;
            }
            else {
                std::cout << "Valid." << std::endl;
            }
        }
    }
    else {
        std::cout << "Invalid value for 'mode' specified." << std::endl;
        print_usage();
        return 1;
    }
    
    return 0;
}

