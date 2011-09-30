require './ruby_nacl'

sender = NaCl.new
receiver = NaCl.new

message = "This is a test message"

sender.set_their_public_key(receiver.my_public_key)
receiver.set_their_public_key(sender.my_public_key)

sender.set_outgoing_nonce(receiver.incoming_nonce)
receiver.set_outgoing_nonce(sender.incoming_nonce)

encrypted_message = sender.encrypt(message)
decrypted_message = receiver.decrypt(encrypted_message)

if decrypted_message == message
    puts "Test 1 successful!"
else
    puts "Test 1 failed! Message from sender to receiver was not decrypted correctly."
    exit
end

message = "This is also a test message"
encrypted_message = receiver.encrypt(message)
decrypted_message = sender.decrypt(encrypted_message)

if decrypted_message == message
    puts "Test 2 successful!"
else
    puts "Test 2 failed! Message from receiver to sender was not decrypted correctly."
    exit
end

