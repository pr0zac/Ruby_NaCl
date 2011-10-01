#include "ruby_nacl.h"

NaCl::NaCl()
{
    gen_new_nonce();
    gen_new_keys();
    gen_new_secret();
}

String NaCl::nonce()
{
    return to_ruby<std::string>(my_nonce);
}

void NaCl::set_remote_nonce(String nonce)
{
    remote_nonce = from_ruby<std::string>(nonce);
}

void NaCl::gen_new_nonce()
{
    char nonce_array[crypto_box_NONCEBYTES+1];
    for (int i = 0; i < crypto_box_NONCEBYTES; ++i)
    {
        nonce_array[i] = (rand() % 254) + 1;
    }
    nonce_array[crypto_box_NONCEBYTES] = 0;
    my_nonce = nonce_array;
}

String NaCl::public_key()
{
    return to_ruby<std::string>(my_pk);
}

String NaCl::secret_key()
{
    return to_ruby<std::string>(my_sk);
}

void NaCl::set_remote_key(String pk)
{
    remote_pk = from_ruby<std::string>(pk);
}

void NaCl::gen_new_keys()
{
    my_pk = crypto_box_keypair(&my_sk);
}

String NaCl::secret()
{
    return to_ruby<std::string>(my_secret);
}

void NaCl::set_secret(String new_secret)
{
    my_secret = from_ruby<std::string>(new_secret);
}

void NaCl::gen_new_secret()
{
    char secret_array[crypto_secretbox_KEYBYTES+1];
    for (int i = 0; i < crypto_secretbox_KEYBYTES; ++i)
    {
        secret_array[i] = (rand() % 254) + 1;
    }
    secret_array[crypto_secretbox_KEYBYTES] = 0;
    my_secret = secret_array;
}

String NaCl::public_decrypt(String enc_msg)
{
    try
    {
        std::string encrypted_message = from_ruby<std::string>(enc_msg);
        std::string message = crypto_box_open(encrypted_message, my_nonce, remote_pk, my_sk);
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
        std::string encrypted_message = crypto_box(message, remote_nonce, remote_pk, my_sk);
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
        std::string message = crypto_secretbox_open(encrypted_message, my_nonce, my_secret);
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
        std::string encrypted_message = crypto_secretbox(message, remote_nonce, my_secret);
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
                              .define_method("nonce", &NaCl::nonce)
                              .define_method("set_remote_nonce", &NaCl::set_remote_nonce)
                              .define_method("gen_new_nonce", &NaCl::gen_new_nonce)
                              .define_method("public_key", &NaCl::public_key)
                              .define_method("secret_key", &NaCl::secret_key)
                              .define_method("set_remote_key", &NaCl::set_remote_key)
                              .define_method("gen_new_keys", &NaCl::gen_new_keys)
                              .define_method("secret", &NaCl::secret)
                              .define_method("set_secret", &NaCl::set_secret)
                              .define_method("gen_new_secret", &NaCl::gen_new_secret)
                              .define_method("public_decrypt", &NaCl::public_decrypt)
                              .define_method("public_encrypt", &NaCl::public_encrypt)
                              .define_method("secret_decrypt", &NaCl::secret_decrypt)
                              .define_method("secret_encrypt", &NaCl::secret_encrypt);
}
