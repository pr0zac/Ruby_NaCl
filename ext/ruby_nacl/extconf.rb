require 'mkmf-rice'

hostname = `hostname`.split('.')[0]
arch = `uname -m`.strip == 'x86_64' ? 'amd64' : 'x86'

HEADER_DIRS = ["NaCl/build/#{hostname}/include/#{arch}"]
LIB_DIRS = ["NaCl/build/#{hostname}/lib/#{arch}"]
$objs = ["NaCl/build/#{hostname}/lib/#{arch}/randombytes.o", "ruby_nacl.o"]

if !File.exists?(HEADER_DIRS[0]) || !File.exists?(LIB_DIRS[0]) || !File.exists?($objs[0])
  puts "Building NaCl library before creating Makefile..."
  `cd NaCl; ./do`
end

dir_config('ruby_nacl', HEADER_DIRS, LIB_DIRS)

while !find_library('nacl', nil, *LIB_DIRS) || !find_header('crypto_box.h', *HEADER_DIRS)
  `cd NaCl; ./do`
end

create_makefile('ruby_nacl')
