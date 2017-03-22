SET(md4c-use-class-static-sources
    main.cpp
    markdown.cpp
    ../md4c/md4c.c
)

ADD_EXECUTABLE(md4c-use-class-static ${md4c-use-class-static-sources})
