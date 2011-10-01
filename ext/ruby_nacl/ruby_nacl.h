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
    String incoming_nonce();
    void set_outgoing_nonce(String nonce);
    void gen_new_incoming_nonce();

    // Functions for managing keys
    String my_public_key();
    String my_secret_key();
    void set_their_public_key(String pk);
    void gen_new_keys();
    
    // Functions for managing shared secret
    String shared_secret();
    void set_shared_secret(String new_secret);
    void gen_new_shared_secret();
    
    // Functions for public-key encryption
    String public_decrypt(String enc_msg);
    String public_encrypt(String msg);

    // Functions for shared-secret encryption 
    String secret_decrypt(String enc_msg);
    String secret_encrypt(String msg);

private:
    std::string inc_nonce; // Local encryption nonce
    std::string out_nonce; // Remote encryption nonce
    std::string my_pk; // Local public key
    std::string my_sk; // Local secret key
    std::string their_pk; // Remote public key
    std::string secret; // Shared secret
};

