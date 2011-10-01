#include "ruby_nacl.h"

NaCl::NaCl()
{
    gen_new_incoming_nonce();
    gen_new_keys();
    gen_new_shared_secret();
}

String NaCl::incoming_nonce()
{
    return to_ruby<std::string>(inc_nonce);
}

void NaCl::set_outgoing_nonce(String nonce)
{
    out_nonce = from_ruby<std::string>(nonce);
}

void NaCl::gen_new_incoming_nonce()
{
    char nonce_array[crypto_box_NONCEBYTES+1];
    for (int i = 0; i < crypto_box_NONCEBYTES; ++i)
    {
        nonce_array[i] = (rand() % 254) + 1;
    }
    nonce_array[crypto_box_NONCEBYTES] = 0;
    inc_nonce = nonce_array;
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

void NaCl::gen_new_keys()
{
    my_pk = crypto_box_keypair(&my_sk);
}

String NaCl::shared_secret()
{
    return to_ruby<std::string>(secret);
}

void NaCl::set_shared_secret(String new_secret)
{
    secret = from_ruby<std::string>(new_secret);
}

void NaCl::gen_new_shared_secret()
{
    char secret_array[crypto_secretbox_KEYBYTES+1];
    for (int i = 0; i < crypto_secretbox_KEYBYTES; ++i)
    {
        secret_array[i] = (rand() % 254) + 1;
    }
    secret_array[crypto_secretbox_KEYBYTES] = 0;
    secret = secret_array;
}

String NaCl::public_decrypt(String enc_msg)
{
    try
    {
        std::string encrypted_message = from_ruby<std::string>(enc_msg);
        std::string message = crypto_box_open(encrypted_message, inc_nonce, their_pk, my_sk);
        return to_ruby<std::string>(message);
    }
    catch (int e)
    {
        return to_ruby<std::string>("");
    }
}

String NaCl::public_encrypt(String msg)
{
    try
    {
        std::string message = from_ruby<std::string>(msg);
        std::string encrypted_message = crypto_box(message, out_nonce, their_pk, my_sk);
        return to_ruby<std::string>(encrypted_message);
    }
    catch (int e)
    {
        return to_ruby<std::string>("");
    }
}

String NaCl::secret_decrypt(String enc_msg)
{
    try
    {
        std::string encrypted_message = from_ruby<std::string>(enc_msg);
        std::string message = crypto_secretbox_open(encrypted_message, inc_nonce, secret);
        return to_ruby<std::string>(message);
    }
    catch (int e)
    {
        return to_ruby<std::string>("");
    }
}

String NaCl::secret_encrypt(String msg)
{
    try
    {
        std::string message = from_ruby<std::string>(msg);
        std::string encrypted_message = crypto_secretbox(message, out_nonce, secret);
        return to_ruby<std::string>(encrypted_message);
    }
    catch (int e)
    {
        return to_ruby<std::string>("");
    }
}

extern "C"
void Init_ruby_nacl()
{
    Data_Type<NaCl> rb_cNaCl = define_class<NaCl>("NaCl")
                              .define_constructor(Constructor<NaCl>())
                              .define_method("incoming_nonce", &NaCl::incoming_nonce)
                              .define_method("set_outgoing_nonce", &NaCl::set_outgoing_nonce)
                              .define_method("gen_new_incoming_nonce", &NaCl::gen_new_incoming_nonce)
                              .define_method("my_public_key", &NaCl::my_public_key)
                              .define_method("my_secret_key", &NaCl::my_secret_key)
                              .define_method("set_their_public_key", &NaCl::set_their_public_key)
                              .define_method("gen_new_keys", &NaCl::gen_new_keys)
                              .define_method("shared_secret", &NaCl::shared_secret)
                              .define_method("set_shared_secret", &NaCl::set_shared_secret)
                              .define_method("gen_new_shared_secret", &NaCl::gen_new_shared_secret)
                              .define_method("public_decrypt", &NaCl::public_decrypt)
                              .define_method("public_encrypt", &NaCl::public_encrypt)
                              .define_method("secret_decrypt", &NaCl::secret_decrypt)
                              .define_method("secret_encrypt", &NaCl::secret_encrypt);
}
