require 'ruby_nacl'

sender = NaCl.new
receiver = NaCl.new

sender.set_remote_nonce(receiver.nonce)
receiver.set_remote_nonce(sender.nonce)

sender.set_remote_key(receiver.public_key)
receiver.set_remote_key(sender.public_key)

receiver.set_secret(sender.secret)

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

