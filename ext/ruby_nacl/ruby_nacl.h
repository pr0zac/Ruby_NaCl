#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "randombytes.h"
#include "crypto_box.h"

using namespace Rice;

class NaCl
{
public:
    NaCl();
    String incoming_nonce();
    void set_outgoing_nonce(String nonce);
    String my_public_key();
    String my_secret_key();
    void set_their_public_key(String pk);
    String decrypt(String enc_msg);
    String encrypt(String data);

private:
    void generate_inc_nonce();

    std::string my_pk;
    std::string my_sk;
    std::string their_pk;
    std::string inc_nonce;
    std::string out_nonce;
};

