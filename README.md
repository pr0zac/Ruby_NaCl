## About Ruby_NaCl ##

Ruby_NaCl is a Ruby gem that provides a wrapper around DJB's awesome NaCl library.



## What is NaCl? ##

[NaCl (pronounced "salt")](http://http://nacl.cr.yp.to/) is a new easy-to-use high-speed software library for network communication, encryption, decryption, signatures, etc written by Daniel J. Bernstein.



## Install the gem ##

1. git clone git@github.com:CaffeinatedMind/Ruby_NaCl.git
2. cd Ruby_NaCl
3. gem build ruby_nacl.gemspec
4. gem install ruby_nacl-0.1.0.gem



## "Hello, World" example ##

```ruby
require 'ruby_nacl'

sender = NaCl.new
receiver = NaCl.new

sender.set_remote_nonce(receiver.nonce)
receiver.set_remote_nonce(sender.nonce)

sender.set_remote_key(receiver.public_key)
receiver.set_remote_key(sender.public_key)

receiver.set_secret(sender.secret)

message = "Hello world!"
encrypted_message = sender.public_encrypt(message)
decrypted_message = receiver.public_decrypt(encrypted_message)
puts decrypted_message
```


## License ##

Ruby_NaCl is licensed under the [Ruby License](http://www.ruby-lang.org/en/LICENSE.txt).

