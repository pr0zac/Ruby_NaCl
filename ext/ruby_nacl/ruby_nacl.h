#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "crypto_box.h"
#include "crypto_secretbox.h"

using namespace Rice;

class NaCl
{
public:
    NaCl();

    // Functions for managing nonces
    String nonce();
    void set_remote_nonce(String nonce);
    void gen_new_nonce();

    // Functions for managing keys
    String public_key();
    String secret_key();
    void set_remote_key(String pk);
    void gen_new_keys();
    
    // Functions for managing shared secret
    String secret();
    void set_secret(String new_secret);
    void gen_new_secret();
    
    // Functions for public-key encryption
    String public_decrypt(String enc_msg);
    String public_encrypt(String msg);

    // Functions for shared-secret encryption 
    String secret_decrypt(String enc_msg);
    String secret_encrypt(String msg);

private:
    std::string my_nonce; // Local encryption nonce
    std::string remote_nonce; // Remote encryption nonce
    std::string my_pk; // Local public key
    std::string my_sk; // Local secret key
    std::string remote_pk; // Remote public key
    std::string my_secret; // Shared secret
};

