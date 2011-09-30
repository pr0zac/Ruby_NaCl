#include "rice/Class.hpp"
#include "rice/String.hpp"
#include "rice/Array.hpp"

#include "randombytes.h"
#include "crypto_box.h"

using namespace Rice;

Object ruby_nacl_test(Object /* self */)
{
    std::string pk;
    std::string sk;
    
    pk = crypto_box_keypair(&sk);
    
    Array keys;
    keys.push(to_ruby(pk));
    keys.push(to_ruby(sk));
    
    return keys;
}

extern "C"
void Init_ruby_nacl()
{
    Class rb_cNaCl = define_class("NaCl").define_method("test", &ruby_nacl_test);
}
