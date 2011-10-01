require 'mkmf-rice'

hostname = `hostname`.split('.')[0]
arch = `uname -m`.strip == 'x86_64' ? 'amd64' : 'x86'

HEADER_DIRS = ["NaCl/build/#{hostname}/include/#{arch}"]
LIB_DIRS = ["NaCl/build/#{hostname}/lib/#{arch}"]

$objs = ["NaCl/build/#{hostname}/lib/#{arch}/randombytes.o", "ruby_nacl.o"]

dir_config('ruby_nacl', HEADER_DIRS, LIB_DIRS)

while !find_library('nacl', nil, *LIB_DIRS) || !find_header('crypto_box.h', *HEADER_DIRS) || !File.exists?($objs[0])
  puts "Building NaCl library before creating Makefile..."
  `cd nacl; rm -rf build; ./do`
end

create_makefile('ruby_nacl')
