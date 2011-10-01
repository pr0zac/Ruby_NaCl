require 'ruby_nacl'

sender = NaCl.new
receiver = NaCl.new

sender.set_outgoing_nonce(receiver.incoming_nonce)
receiver.set_outgoing_nonce(sender.incoming_nonce)

sender.set_their_public_key(receiver.my_public_key)
receiver.set_their_public_key(sender.my_public_key)

receiver.set_shared_secret(sender.shared_secret)

message = "This is a test message"
encrypted_message = sender.public_encrypt(message)
decrypted_message = receiver.public_decrypt(encrypted_message)

if decrypted_message == message
    puts "Test 1 successful!"
else
    puts "Test 1 failed! Public-key encrypted message from sender to receiver was not decrypted correctly."
    exit
end

message = "This is also a test message"
encrypted_message = receiver.public_encrypt(message)
decrypted_message = sender.public_decrypt(encrypted_message)

if decrypted_message == message
    puts "Test 2 successful!"
else
    puts "Test 2 failed! Public-key encrypted message from receiver to sender was not decrypted correctly."
    exit
end

message = "This too is a test message"
encrypted_message = sender.secret_encrypt(message)
decrypted_message = receiver.secret_decrypt(encrypted_message)

if decrypted_message == message
    puts "Test 3 successful!"
else
    puts "Test 3 failed! Shared-secret encrypted message from sender to receiver was not decrypted correctly."
    exit
end

message = "This may actually not be a test message"
encrypted_message = receiver.secret_encrypt(message)
decrypted_message = sender.secret_decrypt(encrypted_message)

if decrypted_message == message
    puts "Test 4 successful!"
else
    puts "Test 4 failed! Shared-secret encrypted message from receiver to sender was not decrypted correctly."
    exit
end

