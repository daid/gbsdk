; Usage: asset label_name, "filename"
MACRO asset
\1::
    INCBIN STRCAT("_build/assets/", \2)
.end::
ENDM
