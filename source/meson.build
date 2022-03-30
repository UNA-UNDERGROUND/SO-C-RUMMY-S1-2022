
rummy_srcs = [
    'src/source.c',
    'src/hello.c',
    'src/util/memory/allocator.c',
]

rummy_deps = [ threads_dep ]


rummy_exe = executable('rummy',
                    rummy_srcs,
                    include_directories: [include_directories('include')],
                    dependencies: rummy_deps)

