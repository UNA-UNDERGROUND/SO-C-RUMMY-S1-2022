
rummy_srcs = [
    'src/game/card.c',
    'src/game/combination.c',
    'src/game/deck.c',
    'src/game/game.c',
    'src/game/hand.c',
    'src/game/player.c',
    'src/render/main_menu.c',
    'src/render/render.c',
    'src/util/memory/allocator.c',
    'src/util/memory/common.c',
    'src/util/memory/vector.c',
    'src/util/random.c',
    'src/source.c',
]

rummy_deps = [ threads_dep ]


rummy_exe = executable('rummy',
                    rummy_srcs,
                    include_directories: [include_directories('include')],
                    dependencies: rummy_deps)

