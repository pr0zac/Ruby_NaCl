require 'mkmf-rice'

hostname = `hostname`.split('.')[0]
arch = `uname -m`.strip == 'x86_64' ? 'amd64' : 'x86'

HEADER_DIRS = ["nacl/build/#{hostname}/include/#{arch}"]
LIB_DIRS = ["nacl/build/#{hostname}/lib/#{arch}"]

$objs = ["nacl/build/#{hostname}/lib/#{arch}/randombytes.o", "ruby_nacl.o"]

dir_config('ruby_nacl', HEADER_DIRS, LIB_DIRS)

unless find_header('crypto_box.h', *HEADER_DIRS)
  abort "crypto_box.h is missing."
end

unless find_library('nacl', nil, *LIB_DIRS)
  abort "libnacl is missing."
end

create_makefile('ruby_nacl')
