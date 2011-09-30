#include "ruby_nacl.h"

NaCl::NaCl()
{
    my_pk = crypto_box_keypair(&my_sk);
    generate_inc_nonce();
}

String NaCl::incoming_nonce()
{
    return to_ruby<std::string>(inc_nonce);
}

void NaCl::set_outgoing_nonce(String nonce)
{
    out_nonce = from_ruby<std::string>(nonce);
}

String NaCl::my_public_key()
{
    return to_ruby<std::string>(my_pk);
}

String NaCl::my_secret_key()
{
    return to_ruby<std::string>(my_sk);
}

void NaCl::set_their_public_key(String pk)
{
    their_pk = from_ruby<std::string>(pk);
}

String NaCl::decrypt(String enc_msg)
{
    std::string encrypted_message = from_ruby<std::string>(enc_msg);
    std::string message = crypto_box_open(encrypted_message, inc_nonce, their_pk, my_sk);
    
    out_nonce = message.substr(0, crypto_box_NONCEBYTES);
    std::string data = message.substr(crypto_box_NONCEBYTES, message.size());
    return to_ruby<std::string>(data);
}

String NaCl::encrypt(String data)
{
    generate_inc_nonce();
    std::string message = inc_nonce;
    message += from_ruby<std::string>(data);

    std::string encrypted_message = crypto_box(message, out_nonce, their_pk, my_sk);
    return to_ruby<std::string>(encrypted_message);
}

void NaCl::generate_inc_nonce()
{
    char nonce_array[crypto_box_NONCEBYTES+1];
    for (int i = 0; i < crypto_box_NONCEBYTES; ++i)
    {
        nonce_array[i] = (rand() % 254) + 1;
    }
    nonce_array[crypto_box_NONCEBYTES] = 0;

    inc_nonce = nonce_array;
}

extern "C"
void Init_ruby_nacl()
{
    Data_Type<NaCl> rb_cNaCl = define_class<NaCl>("NaCl")
                              .define_constructor(Constructor<NaCl>())
                              .define_method("incoming_nonce", &NaCl::incoming_nonce)
                              .define_method("set_outgoing_nonce", &NaCl::set_outgoing_nonce)
                              .define_method("my_public_key", &NaCl::my_public_key)
                              .define_method("my_secret_key", &NaCl::my_secret_key)
                              .define_method("set_their_public_key", &NaCl::set_their_public_key)
                              .define_method("decrypt", &NaCl::decrypt)
                              .define_method("encrypt", &NaCl::encrypt);
}
