require 'mkmf-rice'

HEADER_DIRS = ['/Users/pr0zac/Development/ruby_nacl/ext/ruby_nacl/nacl-20110221/build/Peterbilt/include/amd64']
LIB_DIRS = ['/Users/pr0zac/Development/ruby_nacl/ext/ruby_nacl/nacl-20110221/build/Peterbilt/lib/amd64']

$objs = ['/Users/pr0zac/Development/ruby_nacl/ext/ruby_nacl/nacl-20110221/build/Peterbilt/lib/amd64/randombytes.o', 'ruby_nacl.o']

dir_config('ruby_nacl', HEADER_DIRS, LIB_DIRS)

unless find_header('crypto_box.h', *HEADER_DIRS)
  abort "crypto_box.h is missing."
end

unless find_library('nacl', nil, *LIB_DIRS)
  abort "libnacl is missing."
end

create_makefile('ruby_nacl')
