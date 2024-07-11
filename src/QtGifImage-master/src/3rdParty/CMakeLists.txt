project(3rdParty)

set(SOURCE_LIB
    giflib/egif_lib.c
    giflib/gif_font.c
    giflib/gifalloc.c
    giflib/gif_hash.c
    giflib/dgif_lib.c
    giflib/gif_err.c
    giflib/quantize.c
)

add_library(3rdParty STATIC ${SOURCE_LIB})
