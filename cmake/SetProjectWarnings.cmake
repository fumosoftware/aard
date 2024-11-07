
function(
        set_project_warnings
        project_name
        )

    set(CLANG_OPTIONS
            -Wall
            -Wextra
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
            -Wimplicit-fallthrough
            -Werror #warnings as errors
    )

    set(GCC_OPTIONS
            ${CLANG_OPTIONS}
            -Wmisleading-indentation
            -Wduplicated-cond
            -Wduplicated-branches
            -Wlogical-op
            -Wuseless-cast
            -Wsuggest-override
    )


    target_compile_options(${project_name}
            PRIVATE
            ${GCC_OPTIONS}
    )

endfunction(set_project_warnings)